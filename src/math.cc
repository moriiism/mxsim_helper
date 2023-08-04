#include "mshp_math.h"

// For two values without errors

int MshpMath::IsSame(double aval, double bval)
{
    int retval = 0;
    if( fabs(aval - bval) < DBL_EPSILON ) {
        // same
        retval = 1;
    } else {
        // not same
        retval = 0;
    }
    return retval;
}

double MshpMath::GetMin(double aval, double bval)
{
    double val = 0.0;
    if(aval <= bval){
        val = aval;
    } else {
        val = bval;
    }
    return val;
}

double MshpMath::GetMax(double aval, double bval)
{
    double val = 0.0;
    if(aval >= bval){
        val = aval;
    } else {
        val = bval;
    }
    return val;
}

int MshpMath::GetLocMin(double aval, double bval)
{
    if(aval <= bval){
        return 0;
    } else {
        return 1;
    }
}

int MshpMath::GetLocMax(double aval, double bval)
{
    if(aval >= bval){
        return 0;
    } else {
        return 1;
    }
}


double MshpMath::GetAMean(double aval, double bval)
{
    double ans = (aval + bval) / 2.;
    return ans;
}

// For two values with gaussian errors

void MshpMath::GetAdd(double val1, double val1_err, double val2, double val2_err,
                      double* const ans_ptr, double* const ans_err_ptr)
{
    double ans     = val1 + val2;
    double ans_err = sqrt( pow(val1_err, 2) + pow(val2_err, 2) );
    *ans_ptr = ans;
    *ans_err_ptr = ans_err;
}

void MshpMath::GetSub(double val1, double val1_err, double val2, double val2_err,
                      double* const ans_ptr, double* const ans_err_ptr)
{
    double ans     = val1 - val2;
    double ans_err = sqrt( pow(val1_err, 2) + pow(val2_err, 2) );
    *ans_ptr = ans;
    *ans_err_ptr = ans_err;
}

void MshpMath::GetMul(double val1, double val1_err, double val2, double val2_err,
                      double* const ans_ptr, double* const ans_err_ptr)
{
    double ans     = val1 * val2;
    double ans_err = sqrt( pow( val1_err * val2, 2) +
                           pow( val2_err * val1, 2) );
    *ans_ptr = ans;
    *ans_err_ptr = ans_err;
}

int MshpMath::GetDiv(double val_num, double val_num_err,
                     double val_den, double val_den_err,
                     double* const ans_ptr, double* const ans_err_ptr)
{
    int status = kRetNormal;
  
    double ans     = 0.0;
    double ans_err = 0.0;
    if( fabs(val_den) > DBL_EPSILON) {
        ans     = val_num / val_den;
        ans_err = sqrt( pow( val_num_err * val_den, 2) +
                        pow( val_den_err * val_num, 2) ) / pow( val_den, 2);
        status = kRetNormal;
    } else {
        status = kRetError;
    }

    *ans_ptr = ans;
    *ans_err_ptr = ans_err;
    return status;
}


void MshpMath::GetAMean(double val1, double val1_err,
                        double val2, double val2_err,
                        double* const amean_ptr, double* const amean_err_ptr)
{
    double amean = (val1 + val2) / 2.;
    double amean_err = sqrt(pow(val1_err, 2) + pow(val2_err, 2)) / 2.;
    
    *amean_ptr = amean;
    *amean_err_ptr = amean_err;
}


int MshpMath::GetWMean(double val1, double val1_err,
                       double val2, double val2_err,
                       double* const wmean_ptr, double* const wmean_err_ptr)
{
    int status = kRetNormal;
    double wmean     = 0.0;
    double wmean_err = 0.0;
    if(val1_err < DBL_EPSILON || val2_err < DBL_EPSILON) {
        status = kRetError;
    } else {
        double num = val1 / pow(val1_err, 2) + val2 / pow(val2_err, 2);
        double den = 1.0 / pow(val1_err, 2) + 1.0 / pow(val2_err, 2);
        if(den < DBL_EPSILON) {
            status = kRetError;
        } else {
            wmean     = num / den;
            wmean_err = sqrt( 1. / den);
        }
    }
    *wmean_ptr = wmean;
    *wmean_err_ptr = wmean_err;
    return status;
}


// sub_add_ratio = (val1 - val2) / (val1 + val2)
int MshpMath::GetSubAddRatio(double val1, double val1_err,
                             double val2, double val2_err,
                             double* const ans_ptr, double* const ans_err_ptr)
{
    int status = kRetNormal;
  
    double ans     = 0.0;
    double ans_err = 0.0;
    if( fabs(val1 + val2) > DBL_EPSILON) {
        ans     = (val1 - val2) / (val1 + val2);
        ans_err = 2 * sqrt( pow(val2 * val1_err, 2) +  pow(val1 * val2_err, 2) )
            / pow(val1 + val2, 2);
        status = kRetNormal;
    } else {
        status = kRetError;
    }

    *ans_ptr = ans;
    *ans_err_ptr = ans_err;
    return status;
}


// For N values without errors
//  for array

double MshpMath::GetMin(long narr, const double* const val_arr)
{
    MshpBase::IsValidArray(narr, val_arr);
    double min = val_arr[0];
    for(long iarr = 1; iarr < narr; iarr ++){
        if(min > val_arr[iarr]){
            min = val_arr[iarr];
        }
    }
    return min;
}

double MshpMath::GetMax(long narr, const double* const val_arr)
{
    MshpBase::IsValidArray(narr, val_arr);    
    double max = val_arr[0];
    for(long iarr = 1; iarr < narr; iarr ++){
        if(max < val_arr[iarr]){
            max = val_arr[iarr];
        }
    }
    return max;
}

long MshpMath::GetLocMin(long narr, const double* const val_arr)
{
    MshpBase::IsValidArray(narr, val_arr);
    double min = val_arr[0];
    long imin = 0;
    for(long iarr = 1; iarr < narr; iarr ++){
        if(min > val_arr[iarr]){
            min = val_arr[iarr];
            imin = iarr;
        }
    }
    return imin;
}

long MshpMath::GetLocMax(long narr, const double* const val_arr)
{
    MshpBase::IsValidArray(narr, val_arr);    
    double max = val_arr[0];
    long imax = 0;
    for(long iarr = 1; iarr < narr; iarr ++){
        if(max < val_arr[iarr]){
            max = val_arr[iarr];
            imax = iarr;
        }
    }
    return imax;
}

double MshpMath::GetSum(long narr, const double* const val_arr)
{
    MshpBase::IsValidArray(narr, val_arr);
    double ans = 0.0;
    for(long idata = 0; idata < narr; idata++){
        ans += val_arr[idata];
    }
    return ans;
}

double MshpMath::GetAMean(long narr, const double* const val_arr)
{
    MshpBase::IsValidArray(narr, val_arr);    
    double sum = 0.0;
    for (long index = 0; index < narr; index++){
        sum += val_arr[index];
    }
    double ave = sum / narr;
    return ave;
}

double MshpMath::GetVariance(long narr, const double* const val_arr)
{
    MshpBase::IsValidArray(narr, val_arr);    
    double sum = 0;
    double sum2 = 0;
    for (long index = 0; index < narr; index++){
        sum  += val_arr[index];
        sum2 += val_arr[index] * val_arr[index];
    }
    double variance = ( sum2 - pow(sum, 2) / narr ) / narr;
    return variance;
}

double MshpMath::GetStddev(long narr, const double* const val_arr)
{
    MshpBase::IsValidArray(narr, val_arr);    
    double stddev = sqrt( GetVariance(narr, val_arr) );
    return stddev;
}

double MshpMath::GetUnbiasedVariance(long narr, const double* const val_arr)
{
    MshpBase::IsValidArray(narr, val_arr);    
    if(narr < 2){
        char msg[kLineSize];
        sprintf(msg, "narr (=%ld) < 2", narr);
        MshpPrintErr(msg);
        abort();
    }
    double sum = 0;
    double sum2 = 0;
    for (long index = 0; index < narr; index++){
        sum  += val_arr[index];
        sum2 += val_arr[index] * val_arr[index];
    }
    double unbiased_variance = ( sum2 - pow(sum, 2) / narr ) / (narr - 1);
    return unbiased_variance;
}

double MshpMath::GetSqrtOfUnbiasedVariance(long narr, const double* const val_arr)
{
    MshpBase::IsValidArray(narr, val_arr);
    double sqrt_of_unbiased_variance = sqrt( GetUnbiasedVariance(narr, val_arr) );
    return sqrt_of_unbiased_variance;
}


double MshpMath::GetRMS(long narr, const double* const val_arr)
{
    MshpBase::IsValidArray(narr, val_arr);    
    double sum2 = 0;
    for (long index = 0; index < narr; index++){
        sum2 += val_arr[index] * val_arr[index];
    }
    double rms = sqrt(sum2 / narr);
    return rms;
}

double MshpMath::GetMedian(long narr, const double* const val_arr)
{
    MshpBase::IsValidArray(narr, val_arr);

    long* index_arr = new long[narr];
    bool down = false;
    MshpSort::Sort(narr, val_arr, index_arr, down);

    // 0, 1, 2, 3, 4 : narr = 5
    // narr / 2 = 2

    // 0, 1, 2, 3, 4, 5 : narr = 6
    // narr / 2 = 3
    
    double median = 0.0;
    if (1 == narr % 2){
        // odd
        median = val_arr[index_arr[narr/2]];
    } else {
        // even
        median = (val_arr[index_arr[narr/2 - 1]] + val_arr[index_arr[narr/2]])
            / 2.0;
    }
    delete [] index_arr;
    return median;
}





// For N values without errors
//  for vector

double MshpMath::GetMin(vector<double> vec)
{
    long narr = 0;
    double* val_arr = NULL;
    MshpBase::GenArray(vec, &narr, &val_arr);
    double ans = GetMin(narr, val_arr);
    MshpBase::DelArray(val_arr);
    return ans;
}

double MshpMath::GetMax(vector<double> vec)
{
    long narr = 0;
    double* val_arr = NULL;
    MshpBase::GenArray(vec, &narr, &val_arr);
    double ans = GetMax(narr, val_arr);
    MshpBase::DelArray(val_arr);
    return ans;
}

long MshpMath::GetLocMin(vector<double> vec)
{
    long narr = 0;
    double* val_arr = NULL;
    MshpBase::GenArray(vec, &narr, &val_arr);
    long ans = GetLocMin(narr, val_arr);
    MshpBase::DelArray(val_arr);
    return ans;
}

long MshpMath::GetLocMax(vector<double> vec)
{
    long narr = 0;
    double* val_arr = NULL;
    MshpBase::GenArray(vec, &narr, &val_arr);
    long ans = GetLocMax(narr, val_arr);
    MshpBase::DelArray(val_arr);
    return ans;
}

double MshpMath::GetSum(vector<double> vec)
{
    long narr = 0;
    double* val_arr = NULL;
    MshpBase::GenArray(vec, &narr, &val_arr);
    double ans = GetSum(narr, val_arr);
    MshpBase::DelArray(val_arr);
    return ans;
}

double MshpMath::GetAMean(vector<double> vec)
{
    long narr = 0;
    double* val_arr = NULL;
    MshpBase::GenArray(vec, &narr, &val_arr);
    double ans = GetAMean(narr, val_arr);
    MshpBase::DelArray(val_arr);
    return ans;
}

double MshpMath::GetVariance(vector<double> vec)
{
    long narr = 0;
    double* val_arr = NULL;
    MshpBase::GenArray(vec, &narr, &val_arr);
    double ans = GetVariance(narr, val_arr);
    MshpBase::DelArray(val_arr);
    return ans;
}

double MshpMath::GetStddev(vector<double> vec)
{
    long narr = 0;
    double* val_arr = NULL;
    MshpBase::GenArray(vec, &narr, &val_arr);
    double ans = GetStddev(narr, val_arr);
    MshpBase::DelArray(val_arr);
    return ans;
}

double MshpMath::GetUnbiasedVariance(vector<double> vec)
{
    long narr = 0;
    double* val_arr = NULL;
    MshpBase::GenArray(vec, &narr, &val_arr);
    double ans = GetUnbiasedVariance(narr, val_arr);
    MshpBase::DelArray(val_arr);
    return ans;
}

double MshpMath::GetSqrtOfUnbiasedVariance(vector<double> vec)
{
    long narr = 0;
    double* val_arr = NULL;
    MshpBase::GenArray(vec, &narr, &val_arr);
    double ans = GetSqrtOfUnbiasedVariance(narr, val_arr);
    MshpBase::DelArray(val_arr);
    return ans;
}

double MshpMath::GetRMS(vector<double> vec)
{
    long narr = 0;
    double* val_arr = NULL;
    MshpBase::GenArray(vec, &narr, &val_arr);
    double ans = GetRMS(narr, val_arr);
    MshpBase::DelArray(val_arr);
    return ans;
}

double MshpMath::GetMedian(vector<double> vec)
{
    long narr = 0;
    double* val_arr = NULL;
    MshpBase::GenArray(vec, &narr, &val_arr);
    double ans = GetMedian(narr, val_arr);
    MshpBase::DelArray(val_arr);
    return ans;
}

// For N values with gaussian errors

void MshpMath::GetSum(long narr, const double* const val_arr,
                      const double* const val_err_arr,
                      double* const sum_ptr, double* const sum_err_ptr)
{
    MshpBase::IsValidArray(narr, val_arr);
    MshpBase::IsValidArray(narr, val_err_arr);
    double sum      = 0.0;
    double sum_err2 = 0.0;
    for(long index = 0; index < narr; index++){    
        sum += val_arr[index];
        sum_err2 += pow(val_err_arr[index], 2);
    }
    double sum_err = sqrt(sum_err2);
    
    *sum_ptr     = sum;
    *sum_err_ptr = sum_err;
}

void MshpMath::GetAMean(long narr, const double* const val_arr,
                        const double* const val_err_arr,
                        double* const amean_ptr, double* const amean_err_ptr)
{
    MshpBase::IsValidArray(narr, val_arr);
    MshpBase::IsValidArray(narr, val_err_arr);
    double sum = 0.0;
    double sum_err2 = 0.0;
    for(long index = 0; index < narr; index++){
        sum += val_arr[index];
        sum_err2 += pow(val_err_arr[index], 2);
    }
    double amean = sum / narr;
    double amean_err = sqrt(sum_err2) / narr;

    *amean_ptr = amean;
    *amean_err_ptr = amean_err;
}

int MshpMath::GenWMean(long narr, const double* const val_arr,
                       const double* const val_err_arr,
                       double* const wmean_ptr, double* const wmean_err_ptr,
                       long* const nsel_ptr, int** const mask_sel_arr_ptr)
{
    int status = kRetNormal;
    MshpBase::IsValidArray(narr, val_arr);
    MshpBase::IsValidArray(narr, val_err_arr);
    long num_bad = 0;
    double num = 0.0;
    double den = 0.0;
    long nsel = 0;
    int* mask_sel_arr = new int [narr];
    for(long index = 0; index < narr; index++){
        mask_sel_arr[index] = 0;
    }
    for(long index = 0; index < narr; index++){
        if( pow(val_err_arr[index], 2) < DBL_EPSILON ){
            num_bad ++;
        } else {
            nsel ++;
            num += val_arr[index] / pow(val_err_arr[index], 2);
            den += 1. / pow(val_err_arr[index], 2);
            mask_sel_arr[index] = 1;
        }
    }
    double wmean     = num / den;
    double wmean_err = sqrt( 1. / den);
    *wmean_ptr = wmean;
    *wmean_err_ptr = wmean_err;
    *nsel_ptr = nsel;
    *mask_sel_arr_ptr = mask_sel_arr;

    if(num_bad > 0){
        status = kRetError;
    } else {
        status = kRetNormal;
    }
    return status;
}




void MshpMath::GetSumWithMask(long narr, const double* const val_arr,
                              const double* const val_err_arr,
                              const int* const mask_arr,
                              double* const sum_ptr, double* const sum_err_ptr)
{
    MshpBase::IsValidArray(narr, val_arr);
    MshpBase::IsValidArray(narr, val_err_arr);
    MshpBase::IsValidArray(narr, mask_arr);
    double sum      = 0.0;
    double sum_err2 = 0.0;
    for(long index = 0; index < narr; index++){
        if(1 == mask_arr[index]){
            sum += val_arr[index];
            sum_err2 += pow(val_err_arr[index], 2);
        }
    }
    double sum_err = sqrt(sum_err2);
    
    *sum_ptr     = sum;
    *sum_err_ptr = sum_err;
}


void MshpMath::GetAMeanWithMask(long narr, const double* const val_arr,
                                const double* const val_err_arr,
                                const int* const mask_arr,
                                double* const amean_ptr,
                                double* const amean_err_ptr)
{
    MshpBase::IsValidArray(narr, val_arr);
    MshpBase::IsValidArray(narr, val_err_arr);
    MshpBase::IsValidArray(narr, mask_arr);
    double sum = 0.0;
    double sum_err2 = 0.0;
    long nsel = 0;
    for(long index = 0; index < narr; index++){
        if(1 == mask_arr[index]){
            nsel ++;
            sum += val_arr[index];
            sum_err2 += pow(val_err_arr[index], 2);
        }
    }
    double amean = 0.0;
    double amean_err = 0.0;
    if(nsel > 0){
        amean = sum / nsel;
        amean_err = sqrt(sum_err2) / nsel;
    }
    *amean_ptr     = amean;
    *amean_err_ptr = amean_err;
}


int MshpMath::GenWMeanWithMask(long narr, const double* const val_arr,
                               const double* const val_err_arr,
                               const int* const mask_arr,
                               double* const wmean_ptr,
                               double* const wmean_err_ptr,
                               long* const nsel_ptr,
                               int** const mask_sel_arr_ptr)
{
    int status = kRetNormal;
    MshpBase::IsValidArray(narr, val_arr);
    MshpBase::IsValidArray(narr, val_err_arr);
    MshpBase::IsValidArray(narr, mask_arr);
    long num_bad = 0;
    double num = 0.0;
    double den = 0.0;
    long nsel = 0;
    int* mask_sel_arr = new int [narr];
    for(long index = 0; index < narr; index++){
        mask_sel_arr[index] = 0;
    }
    for(long index = 0; index < narr; index++){
        if(fabs(mask_arr[index] - 1.0) < DBL_EPSILON){
            if( pow(val_err_arr[index], 2) < DBL_EPSILON ){
                num_bad ++;
            } else {
                nsel ++;
                num += val_arr[index] / pow(val_err_arr[index], 2);
                den += 1. / pow(val_err_arr[index], 2);
                mask_sel_arr[index] = 1;
            }
        }
    }
    double wmean     = 0.0;
    double wmean_err = 0.0;
    if( fabs(den) < DBL_EPSILON ){
        num_bad ++;
    } else {
        wmean     = num / den;
        wmean_err = sqrt( 1. / den);
    }

    *wmean_ptr = wmean;
    *wmean_err_ptr = wmean_err;
    *nsel_ptr = nsel;
    *mask_sel_arr_ptr = mask_sel_arr;    

    if(num_bad > 0){
        status = kRetError;
    } else {
        status = kRetNormal;
    }
    return status;
}

