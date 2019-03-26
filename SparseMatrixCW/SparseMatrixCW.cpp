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

void fillX(vector<double>* x, int n) {
	for (int i = 0; i < n; i++) {
		//x->push_back(double(i) * 100 / 17);
		x->push_back(double(i+1) * 2);
	}
}


int main()
{
	ifstream fin3("pcgtestMatrix.mtx");
	InputMatrix input(fin3);

	SparseMatrix* coo = new Coordinate(input.getN(), input.getNonZeros());
	SparseMatrix* csc = new CompressedSparseColumn(input.getN(), input.getNonZeros());
	SparseMatrix* hyb = new Hybrid(input.getN(), input.getNonZeros());
	SparseMatrix* dia = new Diagonal(input.getN(), input.getNonZeros());

	coo->setMatrix(input.getReal(), input.getJR(), input.getJC());
	cout << "1" << endl;
	csc->setMatrix(input.getReal(), input.getJR(), input.getJC());
	cout << "2" << endl;
	hyb->setMatrix(input.getReal(), input.getJR(), input.getJC());
	cout << "3" << endl;
	dia->setMatrix(input.getReal(), input.getJR(), input.getJC());
	cout << "4" << endl;

	vector<double> x;
	fillX(&x, input.getN());

	coo->dotVector(x);
	csc->dotVector(x);
	hyb->dotVector(x);
	dia->dotVector(x);

	csc->dotVectorLeft(x);
	coo->dotVectorLeft(x);
	hyb->dotVectorLeft(x);
	dia->dotVectorLeft(x);

	coo->print();
	csc->print();
	hyb->print();
	dia->print();

	coo->printB();
	csc->printB();
	hyb->printB();
	dia->printB();

	PCG a(coo, input.getInverseDiagonal());
	PCG b(csc, input.getInverseDiagonal());
	PCG c(hyb, input.getInverseDiagonal());
	PCG d(dia, input.getInverseDiagonal());

    return 0;
}

