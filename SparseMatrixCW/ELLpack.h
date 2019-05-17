#include "stdafx.h"
#include"SparseMatrix.h"
#include<vector>
#include<fstream>
#ifndef ELLpack_H
#define ELLpack_H
using namespace std;

class ELLpack : public SparseMatrix {
private:
	vector<double>* coef;
	vector<int>* jcoef;
public:
	ELLpack();
	ELLpack(int n, int elements);
	virtual ~ELLpack();
	void setMatrix(double**);
	void setMatrix(vector<double> AA, vector<int> JR, vector<int> JC);
	vector<double> dotVector(vector<double> x);
	vector<double> dotVectorLeft(vector<double> x);
	void printCOEF();
	void printJCOEF();
	void print(ofstream& out);
};
#endif