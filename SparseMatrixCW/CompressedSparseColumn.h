#include "stdafx.h"
#include<iostream>
#include"Coordinate.h"
#ifndef COMPRESSEDSPARSECOLUMN_H
#define COMRPESSEDSPARSECOLUMN_H
class CompressedSparseColumn : public SparseMatrix {
private:
	vector<double> AA;
	vector<int> JA;
	vector<int> IA;
public:
	CompressedSparseColumn();
	CompressedSparseColumn(int n, int elements);
	virtual ~CompressedSparseColumn();
	void setMatrix(double** matrix);
	void setMatrix(vector<double> values, vector<int> JR, vector<int> JC);
	vector<double> dotVector(vector<double>);
	vector<double> dotVectorLeft(vector<double>);
	double calculateBi(vector<double>, int, int);
	void printB();
	void print();
	void printAA();
	void printJA();
	void printIA();
};
#endif
