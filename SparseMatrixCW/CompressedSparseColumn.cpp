#include "stdafx.h"
#include"CompressedSparseColumn.h"
#include<ctime>
#include<vector>
#include<iostream>
#include<fstream>
#include<chrono>

using namespace std;


CompressedSparseColumn::CompressedSparseColumn() : SparseMatrix::SparseMatrix() {
}
CompressedSparseColumn::CompressedSparseColumn(int n, int elements) : SparseMatrix::SparseMatrix(n, elements) {
}
CompressedSparseColumn::~CompressedSparseColumn() {

}
void CompressedSparseColumn::setMatrix(double** matrix) {

	auto begin = chrono::high_resolution_clock::now();
	int k = 0;
	for (int j = 0; j < n; j++) {
		IA.push_back(k);
		for (int i = 0; i < n; i++) {
			if (matrix[i][j] != 0) {
				AA.push_back(matrix[i][j]);
				JA.push_back(i);
				k++;
			}
		}
	}
	IA.push_back(k);

	auto end = chrono::high_resolution_clock::now();
	time = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
}

void CompressedSparseColumn::setMatrix(vector<double> values, vector<int> JR, vector<int> JC) {
	auto begin = chrono::high_resolution_clock::now();
	AA.reserve(values.size());
	copy(values.begin(), values.end(), back_inserter(AA));
	JA.reserve(JR.size());
	copy(JR.begin(), JR.end(), back_inserter(JA));
	int k = 0;
	IA.push_back(0);
	for (int i = 1; i < JC.size(); i++) {
		if (JC[i] != JC[i - 1]) {
			IA.push_back(i);
		}
	}
	IA.push_back(JC.size());
	auto end = chrono::high_resolution_clock::now();
	time = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
	time /= 1000000000;
}

void CompressedSparseColumn::dotVector(vector<double> x) {

	auto begin = chrono::high_resolution_clock::now();
	for (int j = 0; j < n; j++) {
		int k1 = IA[j];
		int k2 = IA[j + 1];
		for (int k = k1; k < k2; k++) {
			b[JA[k]] = b[JA[k]] + x[j] * AA[k];
		}
	}

	auto end = chrono::high_resolution_clock::now();
	timeDotVector = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
	timeDotVector /= 1000000000;
}

void CompressedSparseColumn::printB() {
	SparseMatrix::printB();
}
void CompressedSparseColumn::printAA() {
	cout << "AA:  ";
	for (auto i : AA) {
		cout << i << ' ';
	}
	cout << endl;
}

void CompressedSparseColumn::printJA() {
	cout << "JA:  ";
	for (auto i : JA) {
		cout << i << ' ';
	}
	cout << endl;
}

void CompressedSparseColumn::printIA() {
	cout << "IA:  ";
	for (auto i : IA) {
		cout << i << ' ';
	}
	cout << endl;
}

void CompressedSparseColumn::print() {
	cout << "Compressed sparse column format: " << endl;
	SparseMatrix::print();
	cout << endl;
}