#include "stdafx.h"
#include "InputMatrix.h"
#include<vector>
#include<iostream>
#include<fstream>

InputMatrix::InputMatrix() {
}

InputMatrix::~InputMatrix() {

}

InputMatrix::InputMatrix(ifstream &fin) {
	int _i;
	int _j;
	double _real;
	double _imaginary;
	fin >> n >> m >> nonZeros;
	inverseDiagonal.resize(n);
	for (int i = 0; i < inverseDiagonal.size(); i++) {
		inverseDiagonal[i] = 1;
	}
	for (int i = 0; i < nonZeros; i++) {
		fin >> _i >> _j >> _real;
		real.push_back(_real);
		JR.push_back(_i - 1);
		JC.push_back(_j - 1);
		if (_i == _j) {
			inverseDiagonal[_i - 1] = 1.0/_real;
		}
	}
}

vector<double> InputMatrix::getReal() {
	return real;
}

vector<double> InputMatrix::getImaginary() {
	return imaginary;
}

vector<int> InputMatrix::getJR() {
	return JR;
}

vector<int> InputMatrix::getJC() {
	return JC;
}

vector<double> InputMatrix::getInverseDiagonal() {
	return inverseDiagonal;
}
int InputMatrix::getN() {
	return n;
}

int InputMatrix::getM() {
	return m;
}

int InputMatrix::getNonZeros() {
	return nonZeros;
}

void InputMatrix::printReal() {
	cout << "real: " << endl;
	for (auto i : real) {
		cout << i << ' ';
	}
	cout << endl;
}

void InputMatrix::printJR() {
	cout << "JR: " << endl;
	for (auto i : JR) {
		cout << i << ' ';
	}
	cout << endl;
}

void InputMatrix::printJC() {
	cout << "JC: " << endl;
	for (auto i : JC) {
		cout << i << ' ';
	}
	cout << endl;
}

void InputMatrix::printWithZeros() {
	double ** matrix = new double*[n];
	for (int i = 0; i < n; i++) {
		matrix[i] = new double[n];
		for (int j = 0; j < n; j++) {
			matrix[i][j] = 0;
		}
	}

	for (int i = 0; i < nonZeros; i++) {
		matrix[JR[i]][JC[i]] = real[i];
	}
	cout << "full matrix: " << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << matrix[i][j] << '\t';
		}
		cout << endl;
	}
	for (int i = 0; i < n; i++) {
		delete[] matrix[i];
	}
}
void InputMatrix::print() {
	InputMatrix::printReal();
	InputMatrix::printJR();
	InputMatrix::printJC();
}