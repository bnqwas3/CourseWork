#include "stdafx.h"
#include <iostream>
#include"SparseMatrix.h"
#include"CompressedSparseRow.h"
#include"CompressedSparseColumn.h"
#include"ELLpack.h"
#include"Hybrid.h"

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
		{ 3,4,0,5,0 },
		{ 6,0,7,8,9 },
		{ 0,0,10,11,0 },
		{ 0,0,0,0,12 }
	};

	double matrixTemp2[MATRIX_RANK][MATRIX_RANK] = {
		{ 1,0,2,0,0 },
		{ 3,4,0,5,0 },
		{ 0,6,7,0,8 },
		{ 0,0,9,10,0 },
		{ 0,0,0,11,12 }
	};
	int n = MATRIX_RANK;
	int elements = 12;
	int diags = 3;
	
	double** matrix = copyMatrix(matrixTemp);
	double** matrix2 = copyMatrix(matrixTemp2);

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

    return 0;
}

