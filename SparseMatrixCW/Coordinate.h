#include "stdafx.h"
#include"SparseMatrix.h"
#include<vector>
#include<fstream>
#ifndef COORDINATE_H
#define COORDINATE_H
using namespace std;
class Coordinate : public SparseMatrix {
private:
	vector<double> AA;
	vector<int> JR;
	vector<int> JC;
public:
	Coordinate();
	Coordinate(int n, int elements);
	virtual ~Coordinate();
	void setMatrix(double** matrix);
	void setMatrix(ifstream& in);
	vector<double> getAA();
	vector<int> getJR();
	vector<int> getJC();
	void printAA();
	void printJR();
	void printJC();
	void print();
};
#endif