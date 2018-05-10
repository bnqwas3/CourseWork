#include "stdafx.h"
#include"ELLpack.h"
#include<vector>
#include<iostream>
#include<fstream>
using namespace std;

ELLpack::ELLpack() : SparseMatrix::SparseMatrix() {
}
ELLpack::ELLpack(int n, int elements) : SparseMatrix::SparseMatrix(n, elements) {
	coef = new vector<int>[n];
	jcoef = new vector<int>[n];
}

ELLpack::~ELLpack() {

}

void ELLpack::setMatrix(vector<int> AA, vector<int> JR, vector<int> JC) {
	for (int i = 0; i < elements; i++) {
		coef[JR[i]].push_back(AA[i]);
		jcoef[JR[i]].push_back(JC[i]);
	}
}

void ELLpack::setMatrix(double** matrix) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (matrix[i][j] != 0) {
				coef[i].push_back(matrix[i][j]);
				jcoef[i].push_back(j);
			}
		}
	}
}
void ELLpack::printCOEF() {
	cout << "COEF: " << endl;
	for (int i = 0; i < n; i++) {
		for (auto j = coef[i].begin(); j != coef[i].end(); ++j) {
			cout << *j << ' ';
		}
		cout << endl;
	}
}

void ELLpack::printJCOEF() {
	cout << "JCOEF: " << endl;
	for (int i = 0; i < n; i++) {
		for (auto j = jcoef[i].begin(); j != jcoef[i].end(); ++j) {
			cout << *j << ' ';
		}
		cout << endl;
	}
}

void ELLpack::print() {
	cout << "ELLpack-itpack: " << endl;
	printCOEF();
	printJCOEF();
	cout << endl;
}