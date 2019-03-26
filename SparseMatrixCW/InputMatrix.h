#include "stdafx.h"
#include<vector>
#include<fstream>
#include<iostream>
#ifndef INPUTMATRIX_H
#define INPUTMATRIX_H
using namespace std;
#pragma once
class InputMatrix {
private:
	int n;
	int m;
	int nonZeros;
	vector<double> real;
	vector<double> imaginary;
	vector<int> JR;
	vector<int> JC;
	vector<double> inverseDiagonal;
	InputMatrix();
public:
	InputMatrix(ifstream &);
	virtual ~InputMatrix();
	vector<double> getReal();
	vector<double> getImaginary();
	vector<int> getJR();
	vector<int> getJC();
	int getN();
	int getM();
	int getNonZeros();
	void printReal();
	void printJR();
	void printJC();
	void print();
	void printWithZeros();
	vector<double> getInverseDiagonal();
};
#endif