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
	for (int i = 0; i < nonZeros; i++) {
		fin >> _i >> _j >> _real >> _imaginary;
		real.push_back(_real);
		JR.push_back(_i - 1);
		JC.push_back(_j - 1);
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

void InputMatrix::print() {
	InputMatrix::printReal();
	InputMatrix::printJR();
	InputMatrix::printJC();
}