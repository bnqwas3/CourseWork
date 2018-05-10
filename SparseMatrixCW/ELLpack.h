#include "stdafx.h"
#include"SparseMatrix.h"
#include<vector>
#include<fstream>
#ifndef ELLpack_H
#define ELLpack_H
using namespace std;

class ELLpack : public SparseMatrix {
private:
	vector<int>* coef;
	vector<int>* jcoef;
public:
	ELLpack();
	ELLpack(int n, int elements);
	virtual ~ELLpack();
	void setMatrix(double**);
	void setMatrix(vector<int> AA, vector<int> JR, vector<int> JC);
	void printCOEF();
	void printJCOEF();
	void print();
};
#endif