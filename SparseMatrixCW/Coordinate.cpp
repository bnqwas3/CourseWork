#include "stdafx.h"
#include"Coordinate.h"
#include<iostream>
#include<ctime>
#include<chrono>
using namespace std;
Coordinate::Coordinate() : SparseMatrix::SparseMatrix() {}
Coordinate::Coordinate(int n, int elements) : SparseMatrix::SparseMatrix(n, elements) {}
Coordinate::~Coordinate(){}
void Coordinate::setMatrix(double** matrix) {

	auto begin = chrono::high_resolution_clock::now();

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

	auto end = chrono::high_resolution_clock::now();
	time = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
	time /= 1000000000;
	
}

void Coordinate::setMatrix(ifstream& in) {
	double real;
	int row;
	int column;
	double imaginary;
	in >> row >> column >> elements;
	for (int i = 0; i < elements; i++) {
		in >> row >> column >> real;
		AA.push_back(real);
		JR.push_back(row-1);
		JC.push_back(column-1);
	}
}

void Coordinate::setMatrix(vector<double> AA, vector<int> JR, vector<int> JC) {
	auto begin = chrono::high_resolution_clock::now();
	this->AA.reserve(AA.size());
	copy(AA.begin(), AA.end(), back_inserter(this->AA));
	this->JR.reserve(JR.size());
	copy(JR.begin(), JR.end(), back_inserter(this->JR));
	this->JC.reserve(JC.size());
	copy(JC.begin(), JC.end(), back_inserter(this->JC));
	auto end = chrono::high_resolution_clock::now();
	time = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
	time /= 1000000000;
}

double Coordinate::calculateBi(int i,vector<double> x) {
	double bAti = 0;
	for (int j = 0; j < n; j++) {
		bAti += getValueAtIJ(i, j)*x[j];
	}
	return bAti;
}

double Coordinate::getValueAtIJ(int i, int j) {
	for (int index = 0; index < elements; index++) {
		if (JC[index] == j && JR[index] == i) {
			return AA[index];
		}
	}
	return 0;
}
vector<double> Coordinate::dotVector(vector<double> x) {
	auto begin = chrono::high_resolution_clock::now();
	vector<double> result;
	result.resize(x.size());
	b.reserve(x.size());
	for (int i = 0; i < elements; i++) {
		b[JR[i]] += AA[i] * x[JC[i]];
		result[JR[i]] += AA[i] * x[JC[i]];
	}
	auto end = chrono::high_resolution_clock::now();
	timeDotVector = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
	timeDotVector /= 1000000000;
	return result;
}

vector<double> Coordinate::dotVectorLeft(vector<double> x) {
	vector<double> result;
	result.resize(x.size());
	for (int i = 0; i < elements; i++) {
		result[JC[i]] += AA[i] * x[JR[i]];
	}
	return result;

}


void Coordinate::printB() {
	SparseMatrix::printB();
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