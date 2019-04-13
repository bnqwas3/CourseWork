#include "stdafx.h"
#include <fstream>
#include <iostream>
#include "SparseMatrix.h"
#include "CompressedSparseRow.h"
#include "CompressedSparseColumn.h"
#include "ELLpack.h"
#include "Hybrid.h"
#include "InputMatrix.h"
#include "Diagonal.h"
#include "PCG.h"

const int MATRIX_RANK = 5;

void printMatrixFull(double** matrix) {
	cout << "Full matrix: " << endl;
	for (int i = 0; i < MATRIX_RANK; i++) {
		for (int j = 0; j < MATRIX_RANK; j++) {
			cout << matrix[i][j] << '\t';
		}
		cout << endl;
	}
	cout << endl;
}
double** copyMatrix(double matrix[][MATRIX_RANK]) {
	double** matrixDynamic = new double*[MATRIX_RANK];
	for (int i = 0; i < MATRIX_RANK; i++) {
		matrixDynamic[i] = new double[MATRIX_RANK];
		for (int j = 0; j < MATRIX_RANK; j++) {
			matrixDynamic[i][j] = matrix[i][j];
		}
	}
	return matrixDynamic;
}

double** readMatrixFromFile(ifstream& in) {
	int n;
	int m;
	in >> n >> m;
	double** matrix = new double*[n];
	for (int i = 0; i < n; i++) {
		matrix[i] = new double[m];
		for (int j = 0; j < m; j++) {
			in >> matrix[i][j];
		}
	}
	return matrix;
}

void fillX(vector<double>* x, int n) {//used to find b in Ax = b;
	for (int i = 0; i < n; i++) {
		x->push_back(double(i) * 100 / 17);
	}
}

void initializeVectors(vector<double>& _b, vector<double>& _x, int size) { 
	//used to solve Ax = b; with initial x (1,1,...,1) and b(2,4,...2n+1) using PCG method;
	for (int i = 1; i <= size; i++) {
		_b.push_back(i*2);
		_x.push_back(1);
	}
}


int main()
{
	ifstream fin3("matrices/bcsstk09_full.mtx");
	InputMatrix input(fin3);

	SparseMatrix* coo = new Coordinate(input.getN(), input.getNonZeros());
	SparseMatrix* csc = new CompressedSparseColumn(input.getN(), input.getNonZeros());
	SparseMatrix* hyb = new Hybrid(input.getN(), input.getNonZeros());
	SparseMatrix* dia = new Diagonal(input.getN(), input.getNonZeros());
	SparseMatrix* ell = new ELLpack(input.getN(), input.getNonZeros());

	coo->setMatrix(input.getReal(), input.getJR(), input.getJC());
	csc->setMatrix(input.getReal(), input.getJR(), input.getJC());
	hyb->setMatrix(input.getReal(), input.getJR(), input.getJC());
	dia->setMatrix(input.getReal(), input.getJR(), input.getJC());
	ell->setMatrix(input.getReal(), input.getJR(), input.getJC());

	vector<double> x;
	fillX(&x, input.getN());

	coo->dotVector(x);
	csc->dotVector(x);
	dia->dotVector(x);
	hyb->dotVector(x);
	ell->dotVector(x);

	coo->dotVectorLeft(x);
	csc->dotVectorLeft(x);
	dia->dotVectorLeft(x);
	hyb->dotVectorLeft(x);
	ell->dotVectorLeft(x);

	coo->print();
	csc->print();
	dia->print();
	hyb->print();
	ell->print();
	vector<double> _b;
	vector<double> _x;
	initializeVectors(_b, _x, input.getN());
	double epsilon = 0.1;
	cout << "error = " << epsilon << endl;
	cout << "Preconditioned Conjugate Gradient method \nfor COO, CSC,HYB adn DIA formats " << endl;

	cout << "coordinate method" << endl;
	PCG a(coo, input.getInverseDiagonal(), epsilon, _b, _x);
	a.printXi(45);
	cout << endl;

	cout << "compressed sparse column: " << endl;
	PCG b(csc, input.getInverseDiagonal(), epsilon, _b, _x);
	b.printXi(45);
	cout << endl;

	cout << "hybrid: " << endl;
	PCG c(hyb, input.getInverseDiagonal(), epsilon, _b, _x);
	c.printXi(45);
	cout << endl;

	cout << "diagonal: " << endl;
	PCG d(dia, input.getInverseDiagonal(), epsilon, _b, _x);
	d.printXi(45);
	cout << endl;

	cout << "ELL-pack" << endl;
	PCG e(ell, input.getInverseDiagonal(), epsilon, _b, _x);
	d.printXi(45);
	cout << endl;
	

    return 0;
}

