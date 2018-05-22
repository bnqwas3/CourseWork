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
		x->push_back(double(i) * 100 / 17);
	}
}


int main()
{
	ifstream fin3("matrixTemp1Coordinate.txt");
	InputMatrix input(fin3);

	SparseMatrix* coo = new Coordinate(input.getN(), input.getNonZeros());
	SparseMatrix* csc = new CompressedSparseColumn(input.getN(), input.getNonZeros());
	SparseMatrix* hyb = new Hybrid(input.getN(), input.getNonZeros());
	SparseMatrix* dia = new Diagonal(input.getN(), input.getNonZeros());

	coo->setMatrix(input.getReal(), input.getJR(), input.getJC());
	csc->setMatrix(input.getReal(), input.getJR(), input.getJC());
	hyb->setMatrix(input.getReal(), input.getJR(), input.getJC());
	dia->setMatrix(input.getReal(), input.getJR(), input.getJC());

	vector<double> x;
	fillX(&x, input.getN());
	coo->dotVector(x);
	csc->dotVector(x);
	hyb->dotVector(x);
	dia->dotVector(x);

	coo->print();
	csc->print();
	hyb->print();
	dia->print();

    return 0;
}

