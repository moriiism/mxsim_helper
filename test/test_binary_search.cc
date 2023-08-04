#include "mshp_str.h"
#include "mshp_iolib.h"
#include "mshp_sort.h"
//#include "mshp_hist1d_nerr.h"
//#include "mshp_qdp_tool.h"
//#include "mshp_func.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;


int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;

    int nbin = 5;
    double* cum_arr = new double [nbin];
    cum_arr[0] = 1.0;
    cum_arr[1] = 2.0;
    cum_arr[2] = 3.0;
    cum_arr[3] = 4.0;
    cum_arr[4] = 5.0;

    double rand = 0.0;
    const double* pind = std::lower_bound(cum_arr, cum_arr + nbin, rand);
    int ibin = pind - cum_arr;
    printf("ibin = %d\n", ibin);
    
    
    return status_prog;
}
