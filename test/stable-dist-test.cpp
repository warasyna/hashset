#include <iostream>
#include <boost/format.hpp>
#include <boost/random.hpp>

#include "common.hpp"
#include "matrix.hpp"
#include "stable-dist.hpp"

using namespace std;
using namespace hashset;


int main() {
	int    K;
	double W;

	string input_path;

	DefaultRng rng;
	GaussianLsh::Parameter param;


	cin >>W >>K;
	cin >>input_path;

	DoubleMatrix data(input_path);

	param.D =data.getDim();
	param.W =W;


	vector<unsigned> ret;

	vector<GaussianLsh> lsh;
	vector<unsigned>    a;

	lsh.resize(K);
	a.resize(K);
	ret.resize(8);
	for (int i =0; i < K; i++) {
		lsh[i].reset(param, rng);
		lsh[i].print_rnd();

		a[i] =rng();
	}


	cout <<"\nPlot the random data\n";
	for (int i =0; i < K; i++) cout <<a[i] <<" ";
	cout <<endl;

	cout <<"\nPlot the Data:\n";
	for (int i =0; i < data.getSize(); i++) {
		for (int j =0; j < data.getDim(); j++) {
			cout <<data[i][j] <<" ";
		}
		cout <<endl;
	}

	cout <<"\nPlot the dim reduction data:\n";
	for (int i =0; i < data.getSize(); i++) {
		for (int j =0; j < K; j++) {
			unsigned x =lsh[j](data[i]);
			cout <<x <<" ";
			ret[i] +=(x*a[j]);
		}
		cout <<"Hash R2: " <<ret[i] <<endl;
	}

	return 0;
}