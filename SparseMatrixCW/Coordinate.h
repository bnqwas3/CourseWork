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
	vector<double> JR;
	vector<double> JC;
public:
	Coordinate();
	Coordinate(int n, int elements);
	virtual ~Coordinate();
	void setMatrix(double** matrix);
	vector<double> getAA();
	vector<double> getJR();
	vector<double> getJC();
	void printAA();
	void printJR();
	void printJC();
	void print();
};
#endif