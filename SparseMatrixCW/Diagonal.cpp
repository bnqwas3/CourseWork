#include "stdafx.h"
#include"Diagonal.h"
#include<iostream>
#include<ctime>
#include<chrono>
using namespace std;
Diagonal::Diagonal() : SparseMatrix::SparseMatrix() {}
Diagonal::Diagonal(int n, int elements) : SparseMatrix::SparseMatrix(n, elements) {
	DIAG = new vector<double>[n];
}
Diagonal::~Diagonal() {}

void Diagonal::allocateMemoryDiag() {
	for (int i = 0; i < n; i++) { //fill DIAG with zeroes
		for (int j = 0; j < IOFF.size(); j++) {
			DIAG[i].push_back(0);
		}
	}
}
void Diagonal::setMatrix(vector<double> values, vector<int> JR, vector<int> JC) { // works only if JC sorted
	auto begin = chrono::high_resolution_clock::now();
	int indexFrom = 0;
	for (int i = 0; i < n; i++) { //fill IOFF
		IOFF.push_back(JC[i] - JR[i]);
		if (JC[i] != JC[i + 1]) {
			break;
		}
	}
	for (int i = JC.size() - 1; i >= JC.size() - n; i--) {
		if (JC[i] == JR[i]) {
			continue;
		}
		if (JC[i] != n - 1) {
			break;
		}
		IOFF.push_back(JC[i] - JR[i]);
	}

	allocateMemoryDiag();
	int position;
	for (int i = 0; i < values.size(); i++) {
		position = find(JC[i] - JR[i]);
		if (position != INT_MAX) {
			DIAG[JR[i]][position] = values[i];
		}
		
	}
	auto end = chrono::high_resolution_clock::now();
	time = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
	time /= 1000000000;
}

void Diagonal::dotVector(vector<double> x) {
	auto begin = chrono::high_resolution_clock::now();
	for (int j = 0; j < IOFF.size(); j++) {
		int JOFF = IOFF[j];
		for (int i = 0; i < n; i++) {
			if (DIAG[i][j] != 0) {
				b[i] = b[i] + DIAG[i][j] * x[i + JOFF];
			}
		}
	}
	auto end = chrono::high_resolution_clock::now();
	timeDotVector = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
	timeDotVector /= 1000000000;
}

int Diagonal::find(int index) {
	for (int i = 0; i < IOFF.size(); i++) {
		if (IOFF[i] == index){
			return i;
		}
	}
	return INT_MAX;
}

void Diagonal::printDIAG() {
	cout << "DIAG: " << endl;
	for (int i = 0; i < n; i++) {
		for (auto j = DIAG[i].begin(); j != DIAG[i].end(); ++j) {
			cout << *j << '\t';
		}
		cout << endl;
	}
}

void Diagonal::printIOFF() {
	cout << "IOFF:  ";
	for (auto i : IOFF) {
		cout << i << ' ';
	}
	cout << endl;
}

void Diagonal::printB() {
	SparseMatrix::printB();
}

void Diagonal::print() {
	cout << "Diagonal: " << endl;
	SparseMatrix::print();
	cout << endl;
}