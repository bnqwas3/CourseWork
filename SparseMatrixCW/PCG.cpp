#include "stdafx.h"
#include<vector>
#include<iostream>
#include"PCG.h"
using namespace std;

PCG::PCG(SparseMatrix* A, vector<double> inverseDiag) {
	alpha = 0;
	beta = 0;
	int n = 3;
	inverse_C.resize(n);
	r.resize(n);
	d.resize(n);
	z.resize(n);
	r_new.resize(n);
	z_new.resize(n);
	d_new.resize(n);

	getInverseC(inverse_C, inverseDiag);

	b.push_back(8);
	b.push_back(6);
	b.push_back(4);

	x.push_back(1);
	x.push_back(1);
	x.push_back(1);
	initializeValues(r, z, d, inverse_C, b, A, x);
	for (int i = 0; i < 100; i++) {
		if (i != 0) prepareToNextStep(z, d, r, z_new, r_new, d_new);
		getNext_Alpha(alpha, z, r, d, A);
		getNext_x(x, d, alpha);
		getNext_r(r_new, r, alpha, d, A);
		getNext_z(z_new, z, r_new, inverse_C);
		getNext_Beta(beta, z_new, r_new, z, r);
		getNext_d(d_new, beta, z_new, d);
		cout << i << ": ";
		printVector(x);
	}
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

void PCG::initializeValues(vector<double>& r, vector<double>& z, vector<double>& d, vector<double> inverse_C, vector<double> b, SparseMatrix* A, vector<double> x) {
	vector<double> temp(A->dotVector(x));
	for (int i = 0; i < b.size(); i++) {
		r[i] = b[i] - temp[i];
		z[i] = inverse_C[i] * r[i];
		d[i] = z[i];
	}
}

void PCG::prepareToNextStep(vector<double>& z, vector<double>& d, vector<double>& r, vector<double> z_new, vector<double> r_new, vector<double> d_new) {
	z = z_new;
	r = r_new;
	d = d_new;
}

void PCG::printVector(vector<double> x) {
	for (int i = 0; i < x.size(); i++) {
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