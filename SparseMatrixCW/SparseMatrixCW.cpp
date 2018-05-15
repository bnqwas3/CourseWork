#include "stdafx.h"
#include <fstream>
#include <iostream>
#include "SparseMatrix.h"
#include "CompressedSparseRow.h"
#include "CompressedSparseColumn.h"
#include "ELLpack.h"
#include "Hybrid.h"

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


int main()
{
	ifstream fin;
	ifstream fin2;
	fin.open("matrixTemp1.txt");
	fin2.open("matrixTemp2.txt");
	double** matrix = readMatrixFromFile(fin);
	double** matrix2 = readMatrixFromFile(fin2);
	fin.close();
	fin2.close();
	int n = 5;
	int elements = 12;
	printMatrixFull(matrix);


	SparseMatrix* coo = new Coordinate(n, elements);
	SparseMatrix* csr = new CompressedSparseRow(n, elements);
	SparseMatrix* csc = new CompressedSparseColumn(n, elements);
	SparseMatrix* ell = new ELLpack(n, elements);
	SparseMatrix* hyb = new Hybrid(n, elements);

	coo->setMatrix(matrix);
	csr->setMatrix(matrix);
	csc->setMatrix(matrix);
	ell->setMatrix(matrix2);
	hyb->setMatrix(matrix2);

	coo->print();
	csr->print();
	csc->print();
	printMatrixFull(matrix2);
	ell->print();
	hyb->print();


	vector<double> x;
	x.push_back(5);
	x.push_back(2);
	x.push_back(3);
	x.push_back(7);
	x.push_back(11);

	coo->dotVector(x);
	coo->printB();
	csc->dotVector(x);
	csc->printB();

    return 0;
}

