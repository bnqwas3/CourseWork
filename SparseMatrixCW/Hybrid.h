#include "stdafx.h"
#include<iostream>
#include"SparseMatrix.h"
#ifndef HYBRID_H
#define HYBRID_H
class Hybrid : public SparseMatrix {
private:
	vector<double> AA;
	vector<int> JR;
	vector<int> JC;
	vector<double>* coef;
	vector<int>* jcoef;
	int k;
public:
	Hybrid();
	Hybrid(int n, int elements);
	virtual ~Hybrid();
	void setMatrix(double** matrix);
	void setMatrix(vector<double> values, vector<int> JR, vector<int> JC);
	void dotVector(vector<double> x);
	void print();
	void printAA();
	void printJR();
	void printJC();
	void printCOEF();
	void printJCOEF();
	void fillColumn(int k, double** matrix, int columnToFill);
};
#endif