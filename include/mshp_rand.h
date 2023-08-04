#ifndef MXSIM_HELPER_RAND_H_
#define MXSIM_HELPER_RAND_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <random>
#include "mshp_base.h"

class MshpRand: private Uncopyable{
public:
    MshpRand(){}
    ~MshpRand(){}

    void Init(int seed);
    double Uniform(void);
    double Normal(double mu, double sigma);
    int Poisson(double mean);
private:
    std::mt19937 mt_;
};

#endif // MXSIM_HELPER_RAND_H_
