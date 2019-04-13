#include "stdafx.h"
#include"ELLpack.h"
#include<ctime>
#include<vector>
#include<iostream>
#include<fstream>
#include<chrono>
using namespace std;

ELLpack::ELLpack() : SparseMatrix::SparseMatrix() {
}
ELLpack::ELLpack(int n, int elements) : SparseMatrix::SparseMatrix(n, elements) {
	coef = new vector<double>[n];
	jcoef = new vector<int>[n];
}

ELLpack::~ELLpack() {

}

void ELLpack::setMatrix(vector<double> AA, vector<int> JR, vector<int> JC) {
	for (int i = 0; i < elements; i++) {
		coef[JR[i]].push_back(AA[i]);
		jcoef[JR[i]].push_back(JC[i]);
	}
}

void ELLpack::setMatrix(double** matrix) {

	auto begin = chrono::high_resolution_clock::now();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (matrix[i][j] != 0) {
				coef[i].push_back(matrix[i][j]);
				jcoef[i].push_back(j);
			}
		}
	}

	auto end = chrono::high_resolution_clock::now();
	time = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
}

vector<double> ELLpack::dotVector(vector<double> x) {
	auto begin = chrono::high_resolution_clock::now();

	vector<double> result;
	result.resize(x.size());
	int k;
	for (int i = 0; i < n; i++) {
		k = 0;
		for (auto j : coef[i]) {
			result[i] += x[jcoef[i][k]] * j;
			b[i] += x[jcoef[i][k]] * j;
			k++;
		}
	}

	auto end = chrono::high_resolution_clock::now();
	timeDotVector = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
	timeDotVector /= 1000000000;

	return result;
}

vector<double> ELLpack::dotVectorLeft(vector<double> x) {
	auto begin = chrono::high_resolution_clock::now();
	vector<double> result;
	result.resize(x.size());
	int k;
	for (int i = 0; i < n; i++) {
		k = 0;
		for (auto element : coef[i]) {
			result[jcoef[i][k]] += x[i] * element;
			k++;
		}
	}
	auto end = chrono::high_resolution_clock::now();
	timeDotVectorLeft = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
	timeDotVectorLeft /= 1000000000;
	return result;

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
	cout << "Need memory to store: " << endl;
	cout << "matrix COEF[" << n << "][" << elements / n << "], matrix JCOEF[" << n << "][" << elements / n << "]\n";
	cout << "summary memory: " << 2 * (elements) << " * type_size" << endl;
	SparseMatrix::print();
	cout << endl;
}