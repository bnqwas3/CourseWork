#include "stdafx.h"
#include<iostream>
#include"Coordinate.h"
#ifndef COMPRESSEDSPARSEROW_H
#define COMRPESSEDSPARSEROW_H
using namespace std;
class CompressedSparseRow : public SparseMatrix {
private:
	vector<double> AA;
	vector<double> JA;
	vector<double> IA;
public:
	CompressedSparseRow();
	CompressedSparseRow(int n, int elements);
	virtual ~CompressedSparseRow();
	void setMatrix(double** matrix);
	void setMatrix(vector<double> values, vector<double> JR, vector<double> JC);
	void printAA();
	void printJA();
	void printIA();
	void print();
};
#endif