#include "stdafx.h"
#include"Hybrid.h"
#include<ctime>
#include<vector>
#include<iostream>
#include<fstream>
#include<chrono>
using namespace std;

Hybrid::Hybrid() : SparseMatrix::SparseMatrix() {
}
Hybrid::Hybrid(int n, int elements) : SparseMatrix::SparseMatrix(n, elements) {
	coef = new vector<double>[n];
	jcoef = new vector<int>[n];
}

Hybrid::~Hybrid() {

}

void Hybrid::fillColumn(int k, double** matrix, int columnToFill) {
	if (k <= n * 2 / 3) {
		for (int i = 0; i < n; i++) {
			if (matrix[i][columnToFill] != 0) {
				this->AA.push_back(matrix[i][columnToFill]);
				this->JR.push_back(i);
				this->JC.push_back(columnToFill);
			}
		}
	}
	else {
		for (int i = 0; i < n; i++) {
			if (matrix[i][columnToFill] != 0) {
				this->coef[i].push_back(matrix[i][columnToFill]);
				this->jcoef[i].push_back(columnToFill);
			}
		}
	}
	
}

void Hybrid::setMatrix(double** matrix) {

	auto begin = chrono::high_resolution_clock::now();
	int k = 0;
	for (int i = 0; i < n; i++) {
		k = 0;
		for (int j = 0; j < n; j++) {
			if (matrix[j][i] != 0) {
				k++;
			}
		}
		fillColumn(k, matrix, i);
			
	}
	auto end = chrono::high_resolution_clock::now();
	time = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
}

void Hybrid::setMatrix(vector<double> values, vector<int> JR, vector<int> JC) { // works only if JC sorted
	auto begin = chrono::high_resolution_clock::now();
	int indexFrom = 0;
	int indexTo = 1;
	int k = 1;
	for (int i = 0; i < values.size() - 1; i++) {
		if (JC[i] != JC[i + 1]) {
			if (k <= n * 2 / 3) {			//FILL COORDINATE;
				for (int i = indexFrom; i <= indexTo; i++) {
					this->AA.push_back(values[i]);
					this->JR.push_back(JR[i]);
					this->JC.push_back(JC[i]);
				}
			}
			else {
				for (int i = indexFrom; i <= indexTo; i++) {
					this->coef[i].push_back(AA[i]);
					this->jcoef[i].push_back(JC[i]);
				}
			}
			indexFrom = i;
		}
		else {
			indexTo = i;
		}
	}

	auto end = chrono::high_resolution_clock::now();
	time = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
}

void Hybrid::dotVector(vector<double> x) {

	auto begin = chrono::high_resolution_clock::now();
	int k = 0;
	for (int i = 0; i < n; i++) {
		k = 0;
		for (auto j : coef[i]) {
			b[i] += x[jcoef[i][k]] * j;
			k++;
		}
	}
	k = 0;
	for (auto i : AA) {
		b[JR[k]] += i * x[JC[k]];
		k++;
	}

	auto end = chrono::high_resolution_clock::now();
	timeDotVector = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
}
void Hybrid::printCOEF() {
	cout << "COEF: " << endl;
	for (int i = 0; i < n; i++) {
		for (auto j = coef[i].begin(); j != coef[i].end(); ++j) {
			cout << *j << ' ';
		}
		cout << endl;
	}
}

void Hybrid::printJCOEF() {
	cout << "JCOEF: " << endl;
	for (int i = 0; i < n; i++) {
		for (auto j = jcoef[i].begin(); j != jcoef[i].end(); ++j) {
			cout << *j << ' ';
		}
		cout << endl;
	}
}

void Hybrid::printAA() {
	cout << "AA:  ";
	for (auto i : AA) {
		cout << i << ' ';
	}
	cout << endl;
}

void Hybrid::printJR() {
	cout << "JR:  ";
	for (auto i : JR) {
		cout << i << ' ';
	}
	cout << endl;
}

void Hybrid::printJC() {
	cout << "JC:  ";
	for (auto i : JC) {
		cout << i << ' ';
	}
	cout << endl;
}

void Hybrid::print() {
	cout << "Hybrid: " << endl;
	printCOEF();
	printJCOEF();
	printAA();
	printJR();
	printJC();
	SparseMatrix::print();
	cout << endl;
}