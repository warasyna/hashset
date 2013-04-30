#ifndef HASHSET_MATRIX_IO
#define HASHSET_MATRIX_IO

#include <iostream>
#include <string>
#include <fstream>

namespace hashset {

template <typename T>
void Matrix<T>::load(const std::string &path) {
	int _n;
	int _d;

	std::ifstream is(path.c_str());

	if (!is) 
		{ std::cerr <<"Unknown File = " <<path <<std::endl; return; }

	is >>_n >>_d;
	reset(_n, _d);

	for (int i =0; i < _n; i++)
		for (int j =0; j < _d; j++)
			is >>data[i][j];

	return;
}

template <typename T>
void Matrix<T>::save(const std::string &path) {
	std::ofstream os(path.c_str());

	if (!os) 
		{ std::cerr <<"Unknown File = " <<path <<std::endl; return; }

	os <<getSize() <<" " <<getDim() <<std::endl;

	for (int i =0; i < N; i++) {
		for (int j =0; j < D; j++)
			os <<data[i][j] <<" ";

		os <<std::endl;
	}

	return;
}


}

#endif