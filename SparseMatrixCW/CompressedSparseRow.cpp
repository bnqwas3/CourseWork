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
		for (int j = 0; j < n; j++) {
			if (matrix[i][j] != 0) {
				AA.push_back(matrix[i][j]);
				JA.push_back(j);
				k++;
			}
		}
		IA.push_back(k);
	}
	//IA.push_back(IA.back() + 1); // last = amount of elements(starts from 0);
}

void CompressedSparseRow::setMatrix(vector<double> values, vector<double> JR, vector<double> JC) {
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
	for (int i = 0; i < elements; i++) {
		cout << AA[i] << ' ';
	}
	cout << endl;
}

void CompressedSparseRow::printJA() {
	cout << "JA:  ";
	for (int i = 0; i < elements; i++) {
		cout << JA[i] << ' ';
	}
	cout << endl;
}

void CompressedSparseRow::printIA() {
	cout << "IA:  ";
	for (int i = 0; i < n; i++) {
		cout << IA[i] << ' ';
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