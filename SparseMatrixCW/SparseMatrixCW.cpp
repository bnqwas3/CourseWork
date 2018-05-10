#include "stdafx.h"
#include <iostream>
#include"SparseMatrix.h"
#include"CompressedSparseRow.h"
#include"CompressedSparseColumn.h"

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


int main()
{
	double matrixTemp[MATRIX_RANK][MATRIX_RANK] = {
		{ 1,0,0,2,0 },
		{ 3,4,0,5.4,0 },
		{ 6,0,7,8,9 },
		{ 0,0,10,11,0 },
		{ 0,0,0,0,12 }
	};
	int n = MATRIX_RANK;
	int elements = 12;
	int diags = 3;
	double** matrix = copyMatrix(matrixTemp);
	printMatrixFull(matrix);



	SparseMatrix* csr = new CompressedSparseRow(n, elements);
	SparseMatrix* coo = new Coordinate(n, elements);
	SparseMatrix* csc = new CompressedSparseColumn(n, elements);

	coo->setMatrix(matrix);
	csr->setMatrix(matrix);
	csc->setMatrix(matrix);

	coo->print();
	csr->print();
	csc->print();

    return 0;
}

