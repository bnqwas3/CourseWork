#include "stdafx.h"
#include"Coordinate.h"
#include<iostream>
using namespace std;
Coordinate::Coordinate() : SparseMatrix::SparseMatrix() {}
Coordinate::Coordinate(int n, int elements) : SparseMatrix::SparseMatrix(n, elements) {}
Coordinate::~Coordinate(){}
void Coordinate::setMatrix(double** matrix) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (matrix[i][j] != 0) {
				AA.push_back(matrix[i][j]);
				JR.push_back(i);
				JC.push_back(j);
			}
		}
	}
}

void Coordinate::setFromFile(ifstream& ofs) {
	ofs >> n;
	ofs >> m;
	ofs >> elements;
	int tempi;
	int tempj;
	double tempa;
	double tempb;
	for (int i = 0; i < elements; i++) {
		ofs >> tempi >> tempj >> tempa >> tempb;
		AA.push_back(tempa);
		JR.push_back(tempi - 1);
		JC.push_back(tempj - 1);
	}
}
vector<double> Coordinate::getAA() {
	return AA;
}
vector<double> Coordinate::getJR() {
	return JR;
}
vector<double> Coordinate::getJC() {
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
	cout << endl;
}