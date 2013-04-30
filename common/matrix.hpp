#ifndef _HASHSET_MATRIX_
#define _HASHSET_MATRIX_

#include <iostream>

namespace hashset {

// Matrix
/**
 * An matrix of size (N*D) is used to store an array of N D-dimensional
 * vectors.
 */

template <class T>
class Matrix {

	int	N;
	int D;
	T   **data;

public:

	// Constructor
	Matrix() :D(0), N(0), data(NULL) {}

	Matrix(int _d, int _n) : data(NULL) { reset(_d, _n); }

	Matrix(const std::string &path): data(NULL) { load(path); }


	// Destructor
	~Matrix() { free(); }


	void load(const std::string &path);
	void save(const std::string &path);


	int getSize() const { return N; }
	int getDim() const { return D; }


	// Reset the size of matrix
	void reset(int _n, int _d) {
		N =_n;
		D =_d;

		if (data != NULL) free();

		data =new T*[N];
		for (int i =0; i < N; i++)
			data[i] =new T[D];

		return;
	}

	// Release memory
	void free() {
		D =N =0;

		if (data != NULL) {
			for (int i =0; i < N; i++)
				delete [] data[i];

			delete [] data;
		}

		data =NULL;
	}


	// Get the ith data vector
	const T* operator [] (int i) const {
		return data[i];
	}
	
};

typedef Matrix<int>    IntMatrix;
typedef Matrix<double> DoubleMatrix;

}

#include "matrix-io.hpp"
#endif