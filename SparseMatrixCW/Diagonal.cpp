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

int Diagonal::findPositionInDiag(int differenceJC_JR) {
	set<int>::iterator iter = IOF.find(differenceJC_JR);
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
void Diagonal::setMatrix(vector<double> values, vector<int> JR, vector<int> JC) {
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

int Diagonal::getJinIOF(int j) { //return data at position j in IOF;
	auto a = IOF.begin();
	for (int i = 0; i < j; i++) {
		a++;
	}
	return *a;
}

vector<double> Diagonal::dotVector(vector<double> x) {
	auto begin = chrono::high_resolution_clock::now();
	vector<double> result;
	result.resize(x.size());
	
	int index;
	for (int i = 0; i < x.size(); i++) {
		for (int k = 0; k < DIAG[i].size(); k++) {
			index = i + IOFat(k);
			if (index >= 0 && index < x.size()) {
				result[i] += DIAG[i][k] * x[index];
				b[i] += DIAG[i][k] * x[index];
			}
		}
	}
	auto end = chrono::high_resolution_clock::now();
	timeDotVector = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
	timeDotVector /= 1000000000;
	return result;
}

vector<double> Diagonal::dotVectorLeft(vector<double> x) {
	vector<double> result;
	result.resize(x.size());
	/*int k = 0;
	for (int i = 0; i < x.size(); i++) {
		k = 0;
		for (auto element : DIAG[i]) {
			if (element != 0) {
				result[i + getJinIOF(k)] += element * x[i];
			}
			k++;
		}
	}*/
	int step = 0;
	int prevIOF = 0;
	int differenceIOF = 0;
	int defaultShift = *IOF.begin();
	int shiftY = 0;
	for (int i = 0; i < x.size(); i++) { 
		step = 0;
		differenceIOF = 0;
		for (auto nextIOF : IOF) {

			if (step != 0) {
				differenceIOF += nextIOF - prevIOF;
			}
			
			shiftY = i - defaultShift - differenceIOF;
			if (shiftY >= 0 && shiftY < x.size()) {
				result[i] += DIAG[shiftY][step] * x[shiftY];
			}

			prevIOF = nextIOF;
			step++;
		}
	}
	return result;
}

int Diagonal::find(int index) {
	for (int i = 0; i < IOFF.size(); i++) {
		if (IOFF[i] == index){
			return i;
		}
	}
	return INT_MAX;
}

int Diagonal::IOFat(int position) {
	set<int>::iterator iter = IOF.begin();
	advance(iter, position);
	return *iter;
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

void Diagonal::printIOF() {
	cout << "IOF: ";
	for (auto i : IOF) {
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