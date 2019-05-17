#include "stdafx.h"
#include <fstream>
#include <iostream>
#include "SparseMatrix.h"
#include "CompressedSparseRow.h"
#include "CompressedSparseColumn.h"
#include "ELLpack.h"
#include "Hybrid.h"
#include "InputMatrix.h"
#include "Diagonal.h"
#include "PCG.h"
#include "BatchWrapper.h"
#include <string>

const int MATRIX_RANK = 5;

void printMatrixFull(double** matrix) {
	cout << "Full matrix: " << endl;
	for (int i = 0; i < MATRIX_RANK; i++) {
		for (int j = 0; j < MATRIX_RANK; j++) {
			cout << matrix[i][j] << '\t';
		}
		cout << endl;
	}
	cout << endl;
}
double** copyMatrix(double matrix[][MATRIX_RANK]) {
	double** matrixDynamic = new double*[MATRIX_RANK];
	for (int i = 0; i < MATRIX_RANK; i++) {
		matrixDynamic[i] = new double[MATRIX_RANK];
		for (int j = 0; j < MATRIX_RANK; j++) {
			matrixDynamic[i][j] = matrix[i][j];
		}
	}
	return matrixDynamic;
}

double** readMatrixFromFile(ifstream& in) {
	int n;
	int m;
	in >> n >> m;
	double** matrix = new double*[n];
	for (int i = 0; i < n; i++) {
		matrix[i] = new double[m];
		for (int j = 0; j < m; j++) {
			in >> matrix[i][j];
		}
	}
	return matrix;
}

void fillX(vector<double>* x, int n) {//used to find b in Ax = b;
	for (int i = 0; i < n; i++) {
		x->push_back(double(i) * 100 / 17);
	}
}

void initializeVectors(vector<double>& _b, vector<double>& _x, int size) { 
	//used to solve Ax = b; with initial x (1,1,...,1) and b(2,4,...2n+1) using PCG method;
	for (int i = 1; i <= size; i++) {
		_b.push_back(i*2);
		_x.push_back(1);
	}
}


int main()
{

	const int BATCH_SIZE = 1000;
	const int FINAL_SIZE_MULTIPLIER = 11;

	string str = "matrices/BatchesFrom20kNonZeros/matrix";
	string path;

	/*vector<string> matrixPath;
	matrixPath.push_back("matrices/inputs/20k nonzeros/G43.mtx");
	matrixPath.push_back("matrices/inputs/20k nonzeros/G44.mtx");
	matrixPath.push_back("matrices/inputs/20k nonzeros/G45.mtx");
	matrixPath.push_back("matrices/inputs/20k nonzeros/G47.mtx");
	vector<InputMatrix> inputMatrixVector;
	for (int i = 0; i < 4; i++) {
		ifstream fin(matrixPath[i]);
		InputMatrix inputTest(fin);
		inputMatrixVector.push_back(inputTest);
		fin.close();
	}

	ofstream matrixInfo("matrices/BatchesFrom20kNonZeros/info.txt");
	for (int i = FINAL_SIZE_MULTIPLIER + 5; i < FINAL_SIZE_MULTIPLIER + 6; i++) {
		cout << i << " out of " << FINAL_SIZE_MULTIPLIER - 1 << endl;
		path = str;
		path.append(to_string(i)).append(".mtx");
		ofstream ofs(path);
		BatchWrapper batchWrapper(inputMatrixVector, i, BATCH_SIZE);
		batchWrapper.write(ofs);
		batchWrapper.writeMatrixComponents(matrixInfo);
		ofs.close();
	}
	
	matrixInfo.close();
*/

	ofstream ofs("matrices/BatchesFrom20kNonZeros/matrixResults1.txt");
	ofs << "format: batchSize coo_bandwidth csc_bandwidth hyb_bandwidth ell_bandwidth" << endl;
	for (int i = 1; i < FINAL_SIZE_MULTIPLIER; i++) {
		cout << i << " out of " << FINAL_SIZE_MULTIPLIER - 1 << endl;
		path = str;
		path.append(to_string(i)).append(".mtx");
		ifstream fin(path);
		InputMatrix input(fin);
		SparseMatrix* coo = new Coordinate(input.getN(), input.getNonZeros());
		SparseMatrix* csc = new CompressedSparseColumn(input.getN(), input.getNonZeros());		
		SparseMatrix* hyb = new Hybrid(input.getN(), input.getNonZeros());	
		//SparseMatrix* dia = new Diagonal(input.getN(), input.getNonZeros());
		SparseMatrix* ell = new ELLpack(input.getN(), input.getNonZeros());
		
		coo->setMatrix(input.getReal(), input.getJR(), input.getJC());
		csc->setMatrix(input.getReal(), input.getJR(), input.getJC());
		hyb->setMatrix(input.getReal(), input.getJR(), input.getJC());
		//dia->setMatrix(input.getReal(), input.getJR(), input.getJC());
		ell->setMatrix(input.getReal(), input.getJR(), input.getJC());
		vector<double> x;
		fillX(&x, input.getN());
		//dia->dotVector(x);
		coo->dotVector(x);
		csc->dotVector(x);
		hyb->dotVector(x);
		ell->dotVector(x);;
		ofs << i* BATCH_SIZE << ' ';
		coo->print(ofs);
		csc->print(ofs);
		//dia->print(ofs); 
		hyb->print(ofs);
		ell->print(ofs);
		ofs << endl;
	}
	
	ofs.close();
	return 0;
}