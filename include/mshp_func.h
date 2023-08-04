#ifndef MXSIM_HELPER_FUNC_H_
#define MXSIM_HELPER_FUNC_H_

#include "mshp_base.h"

class MshpFunc : public MshpObject{
public:
    MshpFunc(string class_name, string title) :
        MshpObject(class_name, title),
        npar_(0), ndim_(0) {}
    virtual ~MshpFunc(){}
    void SetNpar(int npar) {npar_ = npar;};
    void SetNdim(int ndim) {ndim_ = ndim;};
   
    //
    // const functions
    //
    
    int GetNpar() const {return npar_;};
    int GetNdim() const {return ndim_;};

    virtual double Eval(const double* const xval,
                        const double* const par) const = 0;
    double operator()(const double* const xval,
                      const double* const par) const
        {return Eval(xval, par);};
    
    double Eval1d(double xval,
                  const double* const par) const;
    double Eval2d(double xval, double yval,
                  const double* const par) const;

protected:
    void NullMshpFunc();
    void CopyMshpFunc(const MshpFunc* const org);
private:
    int npar_;
    int ndim_;
};

#endif // MXSIM_HELPER_FUNC_H_
