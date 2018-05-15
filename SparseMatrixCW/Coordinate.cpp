#include "stdafx.h"
#include"Coordinate.h"
#include<iostream>
#include<ctime>
using namespace std;
Coordinate::Coordinate() : SparseMatrix::SparseMatrix() {}
Coordinate::Coordinate(int n, int elements) : SparseMatrix::SparseMatrix(n, elements) {}
Coordinate::~Coordinate(){}
void Coordinate::setMatrix(double** matrix) {
	unsigned int start_time = clock();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (matrix[i][j] != 0) {
				AA.push_back(matrix[i][j]);
				JR.push_back(i);
				JC.push_back(j);
			}
		}
	}
	unsigned int end_time = clock();
	time = (double)( end_time - start_time ) / CLOCKS_PER_SEC;
}

void Coordinate::setMatrix(ifstream& in) {
	double real;
	int row;
	int column;
	double imaginary;
	for (int i = 0; i < elements; i++) {
		in >> row >> column >> real;
		AA.push_back(real);
		JR.push_back(row);
		JC.push_back(column);
	}
}
vector<double> Coordinate::getAA() {
	return AA;
}
vector<int> Coordinate::getJR() {
	return JR;
}
vector<int> Coordinate::getJC() {
	return JC;
}
void Coordinate::printAA() {
	cout << "AA:  ";
	for (int i = 0; i < elements; i++) {
		cout << AA[i] << ' ';
	}
	cout << endl;
}
void Coordinate::printJR() {
	cout << "JR:  ";
	for (int i = 0; i < elements; i++) {
		cout << JR[i] << ' ';
	}
	cout << endl;
}
void Coordinate::printJC() {
	cout << "JC:  ";
	for (int i = 0; i < elements; i++) {
		cout << JC[i] << ' ';
	}
	cout << endl;
}
void Coordinate::print() {
	cout << "Coordinate format: " << endl;
	printAA();
	printJR();
	printJC();
	SparseMatrix::print();
	cout << endl;
}