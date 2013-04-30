#ifndef __LSHKIT_COMMON__
#define __LSHKIT_COMMON__

#include <cmath>
#include <vector>
#include <boost/random.hpp>

namespace hashset {

// The default random number generator
typedef boost::mt19937 DefaultRng;

// Cauchy distribution
typedef boost::cauchy_distribution<double> Cauchy;

// Gaussian distribution
typedef boost::normal_distribution<double> Gaussian;

// Uniform distribution
typedef boost::uniform_real<double> Uniform;

// Uniform distribution with int values
typedef boost::uniform_int<int> UniformInt;

// Uniform distribution with unsigned values
typedef boost::uniform_int<unsigned> UniformUnsighned;

}

#endif