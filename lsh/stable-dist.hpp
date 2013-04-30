#ifndef __LSHKIT_CORE__
#define __LSHKIT_CORE__

#include <iostream>
#include "common.hpp"


namespace hashset {

template <typename DIST>
class StableDistLsh {

protected:
	unsigned d;   // Dimension of the object
	double   w;   // Window size

	double   *a;  // Projection vector
	double   b;   // Shift value


public:
	typedef const double * Type;
	typedef unsigned long int UL;

	// Parameter to StableDistLsh
	struct Parameter {
		unsigned D;  // Dimension of the object
		double   W;  // Window size
	};

	// Default Constructor
	StableDistLsh() {}

	template<typename RNG>
	StableDistLsh(const Parameter &param, RNG &rng) {
		reset(param, rng);
	}

	template <typename RNG>
	void reset(const Parameter &param, RNG &rng) {
		boost::variate_generator<RNG &, DIST> dst_gen(rng, DIST());

		this->d =param.D;
		this->w =param.W;

		a =new double[d];
		for (unsigned i =0; i < d; i++) a[i] =dst_gen();

		b =boost::variate_generator<RNG &, Uniform>(rng, Uniform(0, w))();

		return;
	}

	// TODO:
	//unsigned getRange() const { return 0; }

	// Release memory
	void free() {
		d =0;
		w =0.0;
		b =0.0;

		delete [] a;
		a =NULL;
	}

	void print_rnd() {
		std::cout <<"\nRandom Vector\n" <<endl;

		for (unsigned i =0; i < d; i++)
			std::cout <<a[i] <<" ";

		std::cout <<"b = " <<b <<std::endl;
	}

	unsigned operator() (Type obj) const {
		double ret;

		ret =b;
		for (unsigned i =0; i < d; i++) ret +=a[i]*obj[i];

		return unsigned(int(std::floor(ret/w)));
		//unsigned res =unsigned( res2 );

		//return res2;
	}
};

// LSH for L1 distance
typedef StableDistLsh<Cauchy> CauchyLsh;
// LSH for L2 distance
typedef StableDistLsh<Gaussian> GaussianLsh;


}

#endif