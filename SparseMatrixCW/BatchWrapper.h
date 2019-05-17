
#include "stdafx.h"
#include<vector>
#include<fstream>
#include"SparseMatrix.h"
#include"InputMatrix.h"
#include <map>
#include "Key.h"
using namespace std;
#ifndef BATCHWRAPPER_H
#define BATCHWRAPPER_H

class BatchWrapper {
private:
	int n;
	int m;
	int nonZeros;
	map<Key, double> batch;
	vector<int> matricesInside;

	BatchWrapper();

public:
	BatchWrapper(vector<InputMatrix> inputMatrix, const int _size, const int _inputSize);
	virtual ~BatchWrapper();
	void write(ostream& out);
	void writeMatrixComponents(ostream& out);

};
#endif