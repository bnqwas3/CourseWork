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
	Coordinate(int, int);
	virtual ~Coordinate();
	void setMatrix(double**);
	void setMatrix(ifstream&);
	void setMatrix(vector<double>, vector<int>, vector<int>);
	vector<double> dotVector(vector<double>);
	double calculateBi(int, vector<double>);
	vector<double> dotVectorLeft(vector<double>);
	double getValueAtIJ(int, int);
	vector<double> getAA();
	vector<int> getJR();
	vector<int> getJC();
	void printAA();
	void printJR();
	void printJC();
	void printB();
	void print(ofstream& out);
};
#endif