#include <iostream>
#include <boost/format.hpp>
#include <boost/random.hpp>

#include "common.hpp"
#include "matrix.hpp"
#include "stable-dist.hpp"
#include "buckethash.hpp"

using namespace std;
using namespace hashset;


int main() {
	typedef BucketHash<GaussianLsh> MyLsh;

	int    K;
	double W;
	int    range;

	string input_path;

	DefaultRng rng;
	GaussianLsh::Parameter paramG;
	MyLsh::Parameter       paramB;


	cin >>W >>K;
	cin >>input_path;

	DoubleMatrix data(input_path);

	cout <<"\nPlot the Data:\n";
	for (int i =0; i < data.getSize(); i++) {
		for (int j =0; j < data.getDim(); j++) {
			cout <<data[i][j] <<" ";
		}
		cout <<endl;
	}


	paramG.D =paramB.D =data.getDim();
	paramG.W =paramB.W =W;
	paramB.K =unsigned(K);

	range =unsigned( data.getSize() );
	paramB.range =range;

	// Gaussian: test
	cout <<"Gaussian Test:" <<endl;

	vector<unsigned>    ret;

	vector<GaussianLsh> lsh;
	vector<unsigned>    a;

	lsh.resize(K);
	a.resize(K);
	ret.resize(data.getSize());
	for (int i =0; i < K; i++) {
		lsh[i].reset(paramG, rng);
		lsh[i].print_rnd();

		a[i] =rng();
	}

	cout <<"\nPlot the random data\n";
	for (int i =0; i < K; i++) cout <<a[i] <<" ";
	cout <<endl;

	cout <<"\nPlot the dim reduction data:\n";
	for (int i =0; i < data.getSize(); i++) {
		for (int j =0; j < K; j++) {
			unsigned x =lsh[j](data[i]);
			cout <<x <<" ";
			ret[i] +=(x*a[j]);
		}
		cout <<"Hash R1: " <<ret[i]%range; 
		cout <<" Hash R2: " <<ret[i]       <<endl;
	}

	cout <<"##### End of the Gaussian Test ###############" <<endl <<endl;


	//Bucket Hash Test
	cout <<"Bucket Hash Test: " <<endl;
	ret.clear();
	ret.resize(data.getSize());

	MyLsh mlsh;
	mlsh.reset(paramB, rng);

	mlsh.print_rnd(); cout <<endl;

	for (int i =0; i < data.getSize(); i++) {
		ret[i] =mlsh(data[i]);
		
		cout <<"Hash R1: " <<ret[i]%range; 
		cout <<" Hash R2: " <<ret[i]       <<endl;
	}

	return 0;
}