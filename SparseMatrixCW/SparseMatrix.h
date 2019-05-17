
#include "stdafx.h"
#include<vector>
#include<fstream>
using namespace std;
#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

class SparseMatrix {
protected:
	int n;
	int m;
	int elements;
	double time;
	double timeDotVector;
	double timeDotVectorLeft;
	vector<double> b;
public:
	SparseMatrix();
	SparseMatrix(int n, int elements);
	virtual ~SparseMatrix();
	virtual void setMatrix(vector<double> AA, vector<int> JR, vector<int> JC);
	virtual void setMatrix(double** matrix);
	virtual vector<double> dotVector(vector<double> x) = 0;
	virtual vector<double> dotVectorLeft(vector<double> x) = 0;
	virtual void print(ostream& out);
	virtual void printB();
	int getN();
};
#endif