#include "stdafx.h"
#include"CompressedSparseRow.h"
#include<vector>
#include<iostream>
#include<fstream>
using namespace std;

CompressedSparseRow::CompressedSparseRow() : SparseMatrix::SparseMatrix() {
}

CompressedSparseRow::CompressedSparseRow(int n, int elements) : SparseMatrix::SparseMatrix(n, elements) {
}

CompressedSparseRow::~CompressedSparseRow(){
}

void CompressedSparseRow::setMatrix(double** matrix) {
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
	cout << endl;
}