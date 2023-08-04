#include "mshp_func.h"

//
// public
//

double MshpFunc::Eval1d(double xval,
                        const double* const par) const
{
    double xval_arr[1];
    xval_arr[0] = xval;
    double ans = Eval(xval_arr, par);
    return ans;
}

double MshpFunc::Eval2d(double xval, double yval,
                        const double* const par) const
{
    double xval_arr[2];
    xval_arr[0] = xval;
    xval_arr[1] = yval;
    double ans = Eval(xval_arr, par);
    return ans;
}

//
// protected
//

void MshpFunc::NullMshpFunc()
{
    npar_ = 0;
    ndim_ = 0;
}


void MshpFunc::CopyMshpFunc(const MshpFunc* const org)
{
    if(this == org) {abort();}
    if(NULL == org) {abort();}

    SetNpar(org->GetNpar());
    SetNdim(org->GetNdim());
}

