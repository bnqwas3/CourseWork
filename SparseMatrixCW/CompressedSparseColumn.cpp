#include "stdafx.h"
#include"CompressedSparseColumn.h"
#include<vector>
#include<iostream>
#include<fstream>

using namespace std;


CompressedSparseColumn::CompressedSparseColumn() : SparseMatrix::SparseMatrix() {
}
CompressedSparseColumn::CompressedSparseColumn(int n, int elements) : SparseMatrix::SparseMatrix(n, elements) {
}
CompressedSparseColumn::~CompressedSparseColumn() {

}
void CompressedSparseColumn::setMatrix(double** matrix) {
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
}

void CompressedSparseColumn::setMatrix(vector<double> values, vector<double> JR, vector<double> JC) {
	AA.reserve(values.size());
	copy(values.begin(), values.end(), back_inserter(AA));
	JA.reserve(JC.size());
	copy(JC.begin(), JC.end(), back_inserter(JA));
	int k = 0;
	IA.push_back(0);
	for (int i = 1; i < JC.size(); i++) {
		if (JR[i] != JR[i - 1]) {
			IA.push_back(i);
		}
	}
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
	printAA();
	printJA();
	printIA();
	cout << endl;
}