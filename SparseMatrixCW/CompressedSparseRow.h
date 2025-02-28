#include "stdafx.h"
#include<iostream>
#include<ostream>
#include"Coordinate.h"
#ifndef COMPRESSEDSPARSEROW_H
#define COMRPESSEDSPARSEROW_H
class CompressedSparseRow : public SparseMatrix {
private:
	vector<double> AA;
	vector<int> JA;
	vector<int> IA;
public:
	CompressedSparseRow();
	CompressedSparseRow(int n, int elements);
	virtual ~CompressedSparseRow();
	void setMatrix(double** matrix);
	void setMatrix(vector<double> values, vector<int> JR, vector<int> JC);
	double calculateBj(vector<double>, int, int, int);
	vector<double> dotVector(vector<double>);
	vector<double> dotVectorLeft(vector<double>);
	void printB();
	void printAA();
	void printJA();
	void printIA();
	void print(ofstream& out);
};
#endif