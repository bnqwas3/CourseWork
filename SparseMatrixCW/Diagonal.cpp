#include "stdafx.h"
#include"Diagonal.h"
#include<iostream>
#include<ctime>
#include<chrono>
#include<set>
using namespace std;
Diagonal::Diagonal() : SparseMatrix::SparseMatrix() {}
Diagonal::Diagonal(int n, int elements) : SparseMatrix::SparseMatrix(n, elements) {
	DIAG = new vector<double>[n];
}
Diagonal::~Diagonal() {}

void Diagonal::allocateMemoryDiag() {
	for (int i = 0; i < n; i++) { //fill DIAG with zeroes
		for (int j = 0; j < IOF.size(); j++) {
			DIAG[i].push_back(0);
		}
	}
}

int Diagonal::findPositionInDiag(int JC_JR) {
	set<int>::iterator iter = IOF.find(JC_JR);
	int setint;
	if (iter != IOF.end())
	{
		setint = *iter;
	}
	else {
		cout << "OUT OF INDEX" << endl;
		setint = INT_MAX;
	}
	int dist = std::distance(IOF.begin(), iter);
	return dist;
}
void Diagonal::setMatrix(vector<double> values, vector<int> JR, vector<int> JC) { // works only if JC sorted
	auto begin = chrono::high_resolution_clock::now();
	for (int i = 0; i < values.size(); i++) { // fill IOFF
		IOF.insert(JC[i] - JR[i]);
	}
	allocateMemoryDiag();
	for (int i = 0; i < values.size(); i++) {
		DIAG[JR[i]][findPositionInDiag(JC[i] - JR[i])] = values[i];
	}
	auto end = chrono::high_resolution_clock::now();
	time = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
	time /= 1000000000;
}

int Diagonal::getJinIOF(int j) {
	auto a = IOF.begin();
	for (int i = 0; i < j; i++) {
		a++;
	}
	return *a;
}

void Diagonal::dotVector(vector<double> x) {
	auto begin = chrono::high_resolution_clock::now();
	for (int j = 0; j < IOF.size(); j++) {
		int JOFF = getJinIOF(j);
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
	printDIAG();
	printIOFF();
	SparseMatrix::print();
	cout << endl;
}