#include "stdafx.h"
#include"BatchWrapper.h"
#include "InputMatrix.h"
#include <time.h>

BatchWrapper::BatchWrapper(vector<InputMatrix> inputMatrix,const int _size, const int _inputSize) {
	srand(time(NULL));
	n = inputMatrix[0].getN() * _size;
	m = inputMatrix[0].getM() * _size;
	nonZeros = 0;
	for (int i = 0; i < _size; i++) {
		for (int j = 0; j < _size; j++) {
			int random = rand() % inputMatrix.size();
			nonZeros += inputMatrix[random].getNonZeros();
			matricesInside.push_back(random);
			for (int k = 0; k < inputMatrix[random].getJC().size(); k++) {
				int row = i * _inputSize + inputMatrix[random].getJR()[k];
				int column = j * _inputSize + inputMatrix[random].getJC()[k];
				Key key = Key(row, column);
				double val = inputMatrix[random].getReal()[k];
				batch.insert(std::make_pair(key, val));
			}
		}
	}
}
void BatchWrapper::writeMatrixComponents(ostream& out) {
	out << matricesInside.size();
	for (auto i : matricesInside) {
		out << ' ' << i;
	}
	out << endl;
}

void BatchWrapper::write(ostream& out) {
	out << n << ' '<< m << ' ' << nonZeros << endl;
	for (auto i : batch) {
		out << i.first << ' ' << i.second << endl;
	}
}

BatchWrapper::~BatchWrapper() {
	matricesInside.clear();
	batch.clear();
}