#ifndef MXSIM_HELPER_MATH_H_
#define MXSIM_HELPER_MATH_H_

#include "mshp_base.h"
#include "mshp_sort.h"

namespace MshpMath
{
    // For two values without errors
    int IsSame(double aval, double bval);
        
    double GetMin(double aval, double bval);
    double GetMax(double aval, double bval);
    int GetLocMin(double aval, double bval);
    int GetLocMax(double aval, double bval);
    double GetAMean(double aval, double bval);

    // For two values with gaussian errors
    void GetAdd(double val1, double val1_err, double val2, double val2_err,
                double* const ans_ptr, double* const ans_err_ptr);
    void GetSub(double val1, double val1_err, double val2, double val2_err,
                double* const ans_ptr, double* const ans_err_ptr);
    void GetMul(double val1, double val1_err, double val2, double val2_err,
                double* const ans_ptr, double* const ans_err_ptr);
    int GetDiv(double val_num, double val_num_err, double val_den,
               double val_den_err,
               double* const ans_ptr, double* const ans_err_ptr);
    void GetAMean(double val1, double val1_err, double val2, double val2_err,
                  double* const amean_ptr, double* const amean_err_ptr);
    int GetWMean(double val1, double val1_err, double val2, double val2_err,
                 double* const wmean_ptr, double* const wmean_err_ptr);

    // sub_add_ratio = (val1 - val2) / (val1 + val2)
    int GetSubAddRatio(double val1, double val1_err,
                       double val2, double val2_err,
                       double* const ans_ptr, double* const ans_err_ptr);

    // For N values without errors
    //  for array
    double GetMin(long narr, const double* const val_arr);
    double GetMax(long narr, const double* const val_arr);
    long GetLocMin(long narr, const double* const val_arr);
    long GetLocMax(long narr, const double* const val_arr);
    double GetSum(long narr, const double* const val_arr);    

    double GetAMean(long narr, const double* const val_arr);
    // Arithmetic Mean = Sum x_i / N

    double GetVariance(long narr, const double* const val_arr);
    // Variance = [Sum (x_i - mu)^2] / N = [ Sum x_i^2 - (Sum x_i)^2 / N ] / N
    
    double GetStddev(long narr, const double* const val_arr);
    // Standard Deviation = sqrt(Variance)

    double GetUnbiasedVariance(long narr, const double* const val_arr);
    // Unbiased Variance  = [Sum (x_i - mu)^2] / (N - 1)
    // = [ Sum x_i^2 - (Sum x_i)^2 / N ] / (N - 1)    
    
    double GetSqrtOfUnbiasedVariance(long narr, const double* const val_arr);
    // Square of Unbiased Variance  = sqrt (Unbiased Variance)
    
    double GetRMS(long narr, const double* const val_arr);
    // RMS = Root Mean Square = sqrt[ (Sum x_i^2) / N ]

    double GetMedian(long narr, const double* const val_arr);

    //  for vector
    double GetMin(vector<double> vec);
    double GetMax(vector<double> vec);
    long GetLocMin(vector<double> vec);
    long GetLocMax(vector<double> vec);
    double GetSum(vector<double> vec);
    double GetAMean(vector<double> vec);
    double GetVariance(vector<double> vec);
    double GetStddev(vector<double> vec);
    double GetUnbiasedVariance(vector<double> vec);
    double GetSqrtOfUnbiasedVariance(vector<double> vec);
    double GetRMS(vector<double> vec);
    double GetMedian(vector<double> vec);
    
    // For N values with gaussian errors
    //   for array
    void GetSum(long narr, const double* const val_arr,
                const double* const val_err_arr,
                double* const sum_ptr, double* const sum_err_ptr);
    void GetAMean(long narr, const double* const val_arr,
                  const double* const val_err_arr,
                  double* const amean_ptr, double* const amean_err_ptr);
    int GenWMean(long narr, const double* const val_arr,
                 const double* const val_err_arr,
                 double* const wmean_ptr, double* const wmean_err_ptr,
                 long* const nsel_ptr, int** const mask_sel_arr_ptr);

    //   for array with mask    
    // mask: use = 1, not use = 0
    void GetSumWithMask(long narr, const double* const val_arr,
                        const double* const val_err_arr,
                        const int* const mask_arr,
                        double* const sum_ptr, double* const sum_err_ptr);
    void GetAMeanWithMask(long narr, const double* const val_arr,
                          const double* const val_err_arr,
                          const int* const mask_arr,
                          double* const amean_ptr, double* const amean_err_ptr);
    int GenWMeanWithMask(long narr, const double* const val_arr,
                         const double* const val_err_arr,
                         const int* const mask_arr,
                         double* const wmean_ptr, double* const wmean_err_ptr,
                         long* const nsel_ptr, int** const mask_sel_arr_ptr);
    
} //  namespace MshpMath

#endif // MXSIM_HELPER_MATH_H_
