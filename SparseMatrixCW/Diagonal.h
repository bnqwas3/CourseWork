#include "stdafx.h"
#include"SparseMatrix.h"
#include<vector>
#include<fstream>
#ifndef DIAGONAL_H
#define DIAGONAL_H
using namespace std;
class Diagonal : public SparseMatrix {
private:
	vector<double>* DIAG;
	vector<int> IOFF;
public:
	Diagonal();
	Diagonal(int, int);
	virtual ~Diagonal();
	void setMatrix(vector<double>, vector<int>, vector<int>);
	void dotVector(vector<double>);
	void allocateMemoryDiag();
	void printDIAG();
	void printIOFF();
	int find(int);
	void printB();
	void print();
};
#endif