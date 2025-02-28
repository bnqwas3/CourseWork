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
	for (int i = 0; i < JC.size() - 1; i++) {
		if (JC[i] != JC[i + 1]) {
			if (i + 1 - indexFrom <= n * 2 / 3) { //FILL COORDINATE
				for (int j = indexFrom; j <= i; j++) {
					this->AA.push_back(values[j]);
					this->JR.push_back(JR[j]);
					this->JC.push_back(JC[j]);
				}
			}
			else {
				for (int j = indexFrom; j <= i; j++) { //FILL ELL_PACK
					this->coef[JR[j]].push_back(values[j]);
					this->jcoef[JR[j]].push_back(JC[j]);
				}
			}
			indexFrom = i + 1;
		}
	}
	int k = JC.size() - indexFrom;
	for (int i = indexFrom; i < JC.size(); i++) { //fill last column
		if (k <= n * 2 / 3) {
			this->AA.push_back(values[i]);
			this->JR.push_back(JR[i]);
			this->JC.push_back(JC[i]);
		}
		else {
			this->coef[JR[i]].push_back(values[i]);
			this->jcoef[JR[i]].push_back(JC[i]);
		}
	}
	auto end = chrono::high_resolution_clock::now();
	time = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
	time /= 1000000000;
}

vector<double> Hybrid::dotVector(vector<double> x) {
	auto begin = chrono::high_resolution_clock::now();
	vector<double> result;
	result.resize(x.size());
	int k = 0;
	for (int i = 0; i < n; i++) {
		k = 0;
		for (auto j : coef[i]) {
			result[i] += x[jcoef[i][k]] * j;
			k++;
		}
	}
	k = 0;
	for (auto i : AA) {
		result[JR[k]] += i * x[JC[k]];
		k++;
	}

	auto end = chrono::high_resolution_clock::now();
	timeDotVector = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
	timeDotVector /= 1000000000;
	return result;
}

vector<double> Hybrid::dotVectorLeft(vector<double> x) {
	auto begin = chrono::high_resolution_clock::now();
	vector<double> result;
	result.resize(x.size());
	int k = 0;
	for (int i = 0; i < AA.size(); i++) {
		result[JC[i]] += AA[i] * x[JR[i]];
	}
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

void Hybrid::print(ofstream& out) {
	out << "Hybrid: " << endl;
	out << "Need memory to store: " << endl;
	out << "array AA[" << AA.size() << "], array JR[" << JR.size() << "], array JC[" << JC.size() << "]\n";
	out << "matrix COEF[" << n << "][" << coef[0].size() << "], matrix JCOEF[" << n << "][" << coef[0].size() << "]\n";
	out << "summary memory: " << AA.size() + JR.size() + JC.size() + 2 * (n * coef[0].size()) << " * type_size" << endl;
	SparseMatrix::print(out);
	out << endl;
}