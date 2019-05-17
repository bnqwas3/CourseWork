#include "stdafx.h"
#include<vector>
#include<iostream>
#include<chrono>
#include"PCG.h"
using namespace std;

PCG::PCG(SparseMatrix* A, vector<double> inverseDiag, double epsilon, vector<double> _b, vector<double> _x) {
	auto begin = chrono::high_resolution_clock::now();
	alpha = 0;
	beta = 0;
	int n = A->getN();
	inverse_C.resize(n);
	r.resize(n);
	d.resize(n);
	z.resize(n);
	r_new.resize(n);
	z_new.resize(n);
	d_new.resize(n);
	errorVector.resize(n);
	getInverseC(inverse_C, inverseDiag);
	b = _b;
	x = _x;
	initializeValues(errorVector, r, z, d, inverse_C, b, A, x);
	int i = 0;
	while(getNorm(errorVector) > epsilon && i < 1000) {
		if (i != 0) prepareToNextStep(z, d, r, z_new, r_new, d_new);
		getNext_Alpha(alpha, z, r, d, A);
		getNext_x(x, d, alpha);
		getNext_r(r_new, r, alpha, d, A);
		getNext_z(z_new, z, r_new, inverse_C);
		getNext_Beta(beta, z_new, r_new, z, r);
		getNext_d(d_new, beta, z_new, d);
		getErrorVector(errorVector, r, r_new);
		i++;
		cout << i << ' ';
		printVector(errorVector);
	}
	auto end = chrono::high_resolution_clock::now();
	time = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
	time /= 1000000000;
}

double PCG::vectorDotVector(vector<double>& a, vector<double>& b) {
	double result = 0;
	for (int i = 0; i < a.size(); i++) {
		result += a[i] * b[i];
	}
	return result;
}

void PCG::getNext_Alpha(double& alpha, vector<double>& z, vector<double>& r, vector<double>& d, SparseMatrix* A) {

	vector<double> temp(A->dotVectorLeft(d));
	double denominator = vectorDotVector(temp, d);
	alpha = vectorDotVector(z, r) / denominator;
}

void PCG::getNext_x(vector<double>& x, vector<double>& d, double alpha) {
	for (int i = 0; i < x.size(); i++) {
		x[i] += alpha * d[i];
	}
}

void PCG::getNext_r(vector<double>& r_new, vector<double>& r, double alpha, vector<double>& d, SparseMatrix* A) {
	vector<double> temp(A->dotVector(d));
	for (int i = 0; i < r.size(); i++) {
		r_new[i] = r[i] - alpha * temp[i];
	}
}

void PCG::getNext_z(vector<double>& z_new, vector<double>& z, vector<double>& r_new, vector<double>& inverse_C) {
	for (int i = 0; i < r_new.size(); i++) {
		z_new[i] = inverse_C[i] * r_new[i];
	}
}

void PCG::getNext_Beta(double beta, vector<double>& z_new, vector<double>& r_new, vector<double>& z, vector<double>& r) {
	double numerator = 0;
	double denumerator = 0;
	for (int i = 0; i < z_new.size(); i++) {
		numerator += z_new[i] * r_new[i];
		denumerator += z[i] * r[i];
	}
	beta = numerator / denumerator;

}

void PCG::getNext_d(vector<double>& d_new, double beta, vector<double>& z_new, vector<double>& d) {
	for (int i = 0; i < d_new.size(); i++) {
		d_new[i] = z_new[i] + beta * d[i];
	}
}

void PCG::initializeValues(vector<double>& errorVector, vector<double>& r, vector<double>& z, vector<double>& d, vector<double> inverse_C, vector<double> b, SparseMatrix* A, vector<double> x) {
	vector<double> temp(A->dotVector(x));
	for (int i = 0; i < b.size(); i++) {
		r[i] = b[i] - temp[i];
		errorVector[i] = r[i];
		z[i] = inverse_C[i] * r[i];
		d[i] = z[i];
	}
}

void PCG::prepareToNextStep(vector<double>& z, vector<double>& d, vector<double>& r, vector<double> z_new, vector<double> r_new, vector<double> d_new) {
	z = z_new;
	r = r_new;
	d = d_new;
}

void PCG::getErrorVector(vector<double>& errorVector, vector<double> r, vector<double> r_new) {
	for (int i = 0; i < errorVector.size(); i++) {
		errorVector[i] = abs(r[i] - r_new[i]);
	}
}
double PCG::getNorm(vector<double> x) {
	double norm = 0;
	for (auto i : x) {
		if (i > norm) {
			norm = i;
		}
	}
	return norm;
}

void PCG::printVector(vector<double> x) {
	for (int i = 0; i < x.size(); i += x.size() / 5) {//print 5 elements of vector
		cout << x[i] << ' ';
	}
	cout << endl;
}

void PCG::getInverseC(vector<double>& inverse_C, vector<double> diag) {
	inverse_C = diag;
}

void printVector(vector<double> x) {
	for (auto i : x) {
		cout << i << ' ';
	}
	cout << endl;
	
}

void PCG::printXi(int i) {
	cout <<"x[" << i << "] = " <<  x[i] << ' ';
}