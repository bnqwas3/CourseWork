#include "stdafx.h"
#include"CompressedSparseRow.h"
#include<ctime>
#include<vector>
#include<iostream>
#include<fstream>
#include<chrono>
using namespace std;

CompressedSparseRow::CompressedSparseRow() : SparseMatrix::SparseMatrix() {
}

CompressedSparseRow::CompressedSparseRow(int n, int elements) : SparseMatrix::SparseMatrix(n, elements) {
}

CompressedSparseRow::~CompressedSparseRow(){
}

void CompressedSparseRow::setMatrix(double** matrix) {

	auto begin = chrono::high_resolution_clock::now();
	int k = 0;
	for (int i = 0; i < n; i++) {
		IA.push_back(k);
		for (int j = 0; j < n; j++) {
			if (matrix[i][j] != 0) {
				AA.push_back(matrix[i][j]);
				JA.push_back(j);
				k++;
			}
		}
	}
	IA.push_back(k);

	auto end = chrono::high_resolution_clock::now();
	time = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
}

void CompressedSparseRow::setMatrix(vector<double> values, vector<int> JR, vector<int> JC) {
	AA.reserve(values.size());
	copy(values.begin(), values.end(), back_inserter(AA));
	JA.reserve(JR.size());
	copy(JR.begin(), JR.end(), back_inserter(JA));
	int k = 0;
	IA.push_back(0);
	for (int i = 1; i < JC.size(); i++) {
		if (JR[i] != JR[i - 1]) {
			IA.push_back(i);
		}
	}
}

double CompressedSparseRow::calculateBj(vector<double> x, int i, int k1, int k2) {
	double b = 0;
	for (int j = k1; j < k2; j++) {
		b += AA[j] * x[JA[j]];
	}
	return b;
}

void CompressedSparseRow::dotVector(vector<double> x) {
	auto begin = chrono::high_resolution_clock::now();
	for (int i = 0; i < n; i++) {
		int k1 = IA[i];
		int k2 = IA[i + 1];
		b[i] = CompressedSparseRow::calculateBj(x, i, k1, k2);
	}

	auto end = chrono::high_resolution_clock::now();
	timeDotVector = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
}

void CompressedSparseRow::dotVectorLeft(vector<double> x) {
	vector<double> result;
	result.resize(n);
	for(int j = 0; j < n; j++) {
		int k1 = IA[j];
		int k2 = IA[j + 1];
		for (int k = k1; k < k2; k++) {
			result[JA[k]] = result[JA[k]] + x[j] * AA[k];
		}
	}
}

void CompressedSparseRow::printB() {
	SparseMatrix::printB();
}
void CompressedSparseRow::printAA() {
	cout << "AA:  ";
	for (auto i : AA) {
		cout << i << ' ';
	}
	cout << endl;
}

void CompressedSparseRow::printJA() {
	cout << "JA:  ";
	for (auto i : JA) {
		cout << i << ' ';
	}
	cout << endl;
}

void CompressedSparseRow::printIA() {
	cout << "IA:  ";
	for (auto i : IA) {
		cout << i << ' ';
	}
	cout << endl;
}

void CompressedSparseRow::print() {
	cout << "Compressed sparse row format: " << endl;
	printAA();
	printJA();
	printIA();
	SparseMatrix::print();
	cout << endl;
}