#include "stdafx.h"
#include<vector>
#include<fstream>
#include"SparseMatrix.h"
using namespace std;

SparseMatrix::SparseMatrix() {
	n = 0;
	elements = 0;
}
SparseMatrix::SparseMatrix(int n, int elements) {
	this->n = n;
	this->elements = elements;
}
SparseMatrix::~SparseMatrix() {}

void SparseMatrix::setMatrix(vector<double> AA, vector<int> JR, vector<int> JC) {}
void SparseMatrix::setMatrix(double** matrix) {}
void SparseMatrix::print() {}