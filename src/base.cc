#include "mshp_base.h"

//
// MshpObject
//

// protected

void MshpObject::CopyTitle(const MshpObject* const org)
{
    if(this == org) {abort();}
    if(NULL == org) {abort();}

    title_      = org->title_;
}

// private

void MshpObject::NullMshpObject()
{
    class_name_ = "";
    title_      = "";
}

//
// MshpBase
//

void MshpBase::IsValidArray(long narr, const int* const val_arr,
                            string err_msg)
{
    if(narr < 1){
        char msg[kLineSize];
        sprintf(msg, "narr (=%ld) < 1. %s.",
                narr, err_msg.c_str());
        MshpPrintErr(msg);
        abort();
    }
    if(NULL == val_arr){
        char msg[kLineSize];
        sprintf(msg, "val_arr == NULL. %s.",
                err_msg.c_str());
        MshpPrintErr(msg);
        abort();
    }
}

void MshpBase::IsValidArray(long narr, const double* const val_arr,
                            string err_msg)
{
    if(narr < 1){
        char msg[kLineSize];
        sprintf(msg, "narr (=%ld) < 1. %s.",
                narr, err_msg.c_str());
        MshpPrintErr(msg);
        abort();
    }
    if(NULL == val_arr){
        char msg[kLineSize];
        sprintf(msg, "val_arr == NULL. %s.",
                err_msg.c_str());
        MshpPrintErr(msg);
        abort();
    }
}

void MshpBase::GenArray(vector<double> vec,
                        long* narr_ptr,
                        double** val_arr_ptr)
{
    long narr = vec.size();
    double* val_arr = new double [narr];
    for(long idata = 0; idata < narr; idata ++){
        val_arr[idata] = vec[idata];
    }
    *narr_ptr = narr;
    *val_arr_ptr = val_arr;
}

double* MshpBase::GenArray(vector<double> vec)
{
    long narr = vec.size();
    double* val_arr = new double [narr];
    for(long idata = 0; idata < narr; idata ++){
        val_arr[idata] = vec[idata];
    }
    return val_arr;
}

void MshpBase::DelArray(double* val_arr)
{
    delete [] val_arr; val_arr = NULL;
}
