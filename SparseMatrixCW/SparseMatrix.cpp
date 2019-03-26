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
vector<double> SparseMatrix::dotVector(vector<double> x) {/*solve Ax = b */
	vector<double> a;
	a.resize(3);
	return a;
}
vector<double> SparseMatrix::dotVectorLeft(vector<double> x) {/*solve xA = b*/ 
	vector<double> a;
	a.resize(3);
	return a;
}
vector<double> SparseMatrix::getInverseDiagonal() {
	vector<double> a;
	a.resize(3);
	return a;
}
void SparseMatrix::setMatrix(vector<double> AA, vector<int> JR, vector<int> JC) {}
void SparseMatrix::setMatrix(double** matrix) {}

void SparseMatrix::print() {
	cout << "time to set matrix: " << time << " seconds" << endl;
	cout << "time to multiply by vector: " << timeDotVector << " seconds" << endl;
	cout << "bandwidth: " << 2 * n / timeDotVector << endl;
}