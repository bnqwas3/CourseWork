#include "stdafx.h"
#include<iostream>
#include"Coordinate.h"
#ifndef COMPRESSEDSPARSECOLUMN_H
#define COMRPESSEDSPARSECOLUMN_H
class CompressedSparseColumn : public SparseMatrix {
private:
	vector<int> AA;
	vector<int> JA;
	vector<int> IA;
public:
	CompressedSparseColumn();
	CompressedSparseColumn(int n, int elements);
	void setMatrix(int** matrix);
	void setMatrix(vector<double> values, vector<double> JR, vector<double> JC);
	void print();
	void printAA();
	void printJA();
	void printIA();
};
#endif
