#include "stdafx.h"
#include<vector>
#include<fstream>
#include<iostream>
#include"SparseMatrix.h"
using namespace std;

SparseMatrix::SparseMatrix() {
	n = 0;
	elements = 0;
}
SparseMatrix::SparseMatrix(int n, int elements) {
	this->n = n;
	this->elements = elements;
	b.reserve(n);
	for (int i = 0; i < n; i++) {
		b.push_back(0);
	}
}
SparseMatrix::~SparseMatrix() {}
void::SparseMatrix::printB() {
	cout << "vector B: " << endl;
	for (auto i : b) {
		cout << i << ' ';
	}
	cout << endl;
}
void SparseMatrix::dotVector(vector<double> x) {}
void SparseMatrix::setMatrix(vector<double> AA, vector<int> JR, vector<int> JC) {}
void SparseMatrix::setMatrix(double** matrix) {}
void SparseMatrix::print() {
	cout << "time: " << time << " nano seconds" << endl;
}