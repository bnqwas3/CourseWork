
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
public:
	SparseMatrix();
	SparseMatrix(int n, int elements);
	virtual ~SparseMatrix();
	virtual void setMatrix(vector<int> AA, vector<int> JR, vector<int> JC);
	virtual void setMatrix(double** matrix);
	virtual void print();
	virtual void setFromFile(ifstream& ofs);
};
#endif