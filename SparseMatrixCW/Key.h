
#include "stdafx.h"
#include <ostream>

#ifndef KEY_H
#define KEY_H

class Key {
public:
	int row;
	int column;
	Key(int i, int j) {
		this->row = i;
		this->column = j;
	}

	bool operator<(const Key& k) const {

		if (this->column < k.column) {
			return this->column < k.column;
		}
		else if (this->column == k.column) {
			return this->row < k.row;
		}
		else {
			return this->column < k.column;
		}
	}

	friend std::ostream& operator<<(std::ostream& os, const Key& key) {
		os << key.row + 1 << ' ' << key.column + 1;
		return os;
	}
};

#endif // !KEY_H