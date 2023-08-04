#include "mshp_rand.h"

void MshpRand::Init(int seed)
{
    if(0 == seed){
        std::random_device seed_gen;
        std::mt19937 mt(seed_gen());
        mt_ = mt;
    } else {
        std::mt19937 mt(seed);
        mt_ = mt;
    }
}

double MshpRand::Uniform(void)
{
    //double val = genrand64_real1();
    //double val = HDmtRand() / RAND_MAX;
    //double val = rand() / (double)RAND_MAX;
    //printf("%f\n", val);

    std::uniform_real_distribution<> rand01(0.0, 1.0);
    double val = rand01(mt_);
    return val;
}


//
////double MshpRand::Normal(double mu, double sigma)
////{
////    double z=sqrt( -2.0*log(Uniform()) ) * sin( 2.0*M_PI*Uniform() );
////    double val = mu + sigma*z;
////    return val;
////}

double MshpRand::Normal(double mu, double sigma)
{
    std::normal_distribution<> norm(mu, sigma);
    double val = norm(mt_);
    return val;
}

////
//// made from Cern/Root TRandom.cxx
////
///// Generates a random integer N according to a Poisson law.
///// Prob(N) = exp(-mean)*mean^N/Factorial(N)
/////
///// Use a different procedure according to the mean value.
///// The algorithm is the same used by CLHEP.
///// For lower value (mean < 25) use the rejection method based on
///// the exponential.
///// For higher values use a rejection method comparing with a Lorentzian
///// distribution, as suggested by several authors.
///// This routine since is returning 32 bits integer will not work for values
///// larger than 2*10**9.
////

int MshpRand::Poisson(double mean)
{
    int n;
    if (mean <= 0) return 0;
    if (mean < 25) {
        double expmean = exp(-mean);
        double pir = 1;
        n = -1;
        while(1) {
            n++;
            pir *= Uniform();
            if (pir <= expmean) break;
        }
        return n;
    }
    // for large value we use inversion method
    else if (mean < 1E9) {
        double em, t, y;
        double sq, alxm, g;
        double pi = M_PI;
 
        sq = sqrt(2.0*mean);
        alxm = log(mean);
        g = mean*alxm - std::lgamma(mean + 1.0);
 
        do {
            do {
                y = tan(pi * Uniform());
                em = sq*y + mean;
            } while( em < 0.0 );
 
            em = floor(em);
            t = 0.9*(1.0 + y*y)* exp(em*alxm - std::lgamma(em + 1.0) - g);
        } while( Uniform() > t );
 
        return int(em);
    }
    else {
        // use Gaussian approximation vor very large values
        n = int(Normal(0, 1)*sqrt(mean) + mean +0.5);
        return n;
    }
}
