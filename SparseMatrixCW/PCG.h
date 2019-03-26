#include "stdafx.h"
#include "SparseMatrix.h"
#include<vector>
#include<fstream>
using namespace std;
#ifndef PCG_H
#define PCG_H
class PCG{
protected:
	vector<double> inverse_C;
	vector<double> b;
	vector<double> x;
	vector<double> r;
	vector<double> d;
	vector<double> z;
	vector<double> r_new;
	vector<double> z_new;
	vector<double> d_new;
	double alpha = 0;
	double beta = 0;
private:
	double vectorDotVector(vector<double>&, vector<double>&);
	void getNext_Alpha(double&, vector<double>&, vector<double>&, vector<double>&, SparseMatrix*);
	void getNext_x(vector<double>&, vector<double>&, double);
	void getNext_r(vector<double>&, vector<double>&, double, vector<double>&, SparseMatrix*);
	void getNext_z(vector<double>&, vector<double>&, vector<double>&, vector<double>&);
	void getNext_Beta(double, vector<double>&, vector<double>&, vector<double>&, vector<double>&);
	void getNext_d(vector<double>&, double, vector<double>&, vector<double>&);
	void initializeValues(vector<double>&, vector<double>&, vector<double>&, vector<double>, vector<double>, SparseMatrix*, vector<double>);
	void prepareToNextStep(vector<double>&, vector<double>&, vector<double>&, vector<double>, vector<double>, vector<double>);
	void getInverseC(vector<double>&, vector<double>);
	void printVector(vector<double>);
public:
	PCG(SparseMatrix*,vector<double>);
};

#endif