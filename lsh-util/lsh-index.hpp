#ifndef _HASHSET_LSH_INDEX_
#define _HASHSET_LSH_INDEX_

#include <map>

#include "common.hpp"


namespace hashset {

//TODO: double dake ni shinai
template <typename LSH>
class LshIndex {

protected:
	Table<LSH> *tables;  // MatS, MatT

public:

	//TODO:
	typedef typename LSH::Type Type;

	// Constructor
	LshIndex() {}

	// Initialize the hash tables
	void init(unsigned L) {
		tables =new Table<LSH>[L];

		return;
	}

	// Insert data to the index
	void insert(unsigned key, Type data) {
		for (unsigned i =0; i < tables.size(); i++)
			tables[i].insert(key, data);
		
		return;
	}

};


template <typename LSH>
class Table {

protected:
	
	typedef unsigned long int UL;
	typedef std::map<UL, unsigned> Bucket;

	LSH                  *lsh;
	std::map<UL, Bucket> buckets;


public:

	//typedef          LSH       Super;
	typedef typename LSH::Type Type;

	/*struct Parameter: public Super::Parameter {
		unsigned range;
	};*/

	// Constructor
	Table() {}

	void init(const Parameter &param) {
		lsh =new LSH[L];

		for (int i =0; i < L; i++) {
			lsh[i].reset(param, engine);
		}
	}
	
	// Insert data to the index
	void insert(unsigned key, Type data) {

		UL h2 =lsh(data);
		UL h1 =h2 % range;

		buckets[h1][h2] =key;

		return;
	}

	unsigned getRange() const { return range; }
};


}

#endif