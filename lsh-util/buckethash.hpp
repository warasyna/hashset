//TODO: To-itsu

#ifndef __HASHSET_HASHING__
#define __HASHSET_HASHING__

#include "stable-dist.hpp"


namespace hashset {

template <typename LSH>
class BucketHash {
public:
	typedef          LSH       Super;
	typedef typename LSH::Type Type;

	struct Parameter: public Super::Parameter {
		unsigned K;      // The number of hash functions in a hash family
		unsigned range;  // Desired range of the LSH
	};

	// Default constructor
	BucketHash() {}

	template <typename RNG>
	void reset(const Parameter &param, RNG &rng) {
		range =param.range;

		lsh.resize(param.K);
		a.resize(param.K);

		for (unsigned i =0; i < param.K; i++) {
			lsh[i].reset(param, rng);
			a[i] =rng();
		}

		return;
	}

	template<typename RNG>
	BucketHash(const Parameter &param, RNG &rng) {
		reset(param, rng);
	}

	unsigned getRange() const { return range; }

	unsigned operator () (Type obj) const {
		unsigned ret =0;

		for (unsigned i =0; i < lsh.size(); i++) {
			unsigned x =lsh[i](obj);
			cout <<x <<" ";
			ret +=(x*a[i]);
		}

		return ret;
	}

	// Methods for debug
	void print_rnd() {
		cout <<"\nPlot the random data\n";
		for (unsigned i =0; i < a.size(); i++) cout <<a[i] <<" ";
		cout <<endl;
	}



protected:
	std::vector<Super>    lsh;
	std::vector<unsigned> a;

	unsigned range;

};


}

#endif