#include "stdafx.h"
#include"SparseMatrix.h"
#include<vector>
#include<fstream>
#include<set>
#ifndef DIAGONAL_H
#define DIAGONAL_H
using namespace std;
class Diagonal : public SparseMatrix {
private:
	vector<double>* DIAG;
	vector<int> IOFF;
	set<int> IOF;
public:
	Diagonal();
	Diagonal(int, int);
	virtual ~Diagonal();
	void setMatrix(vector<double>, vector<int>, vector<int>);
	vector<double> dotVector(vector<double>);
	vector<double> dotVectorLeft(vector<double>);
	void allocateMemoryDiag();
	void printDIAG();
	void printIOFF();
	void printIOF();
	int find(int);
	int findPositionInDiag(int);
	int getJinIOF(int);
	void printB();
	void print(ofstream& out);
	int IOFat(int);
};
#endif