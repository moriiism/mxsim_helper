#ifndef MXSIM_HELPER_FUNC_PAR_H_
#define MXSIM_HELPER_FUNC_PAR_H_

#include "mshp_iolib.h"

class MshpFuncPar : public MshpObject{
public:
    explicit MshpFuncPar(string title = "") :
        MshpObject("MshpFuncPar", title),
        npar_(0),
        par_name_(NULL),
        par_(NULL) {}
    ~MshpFuncPar() {
        Null();
    }
    void Init(int npar);
    void Set(int npar,
             const string* const par_name,
             const double* const par);
    void SetElm(int ipar,
                string par_name,
                double par);
    void InitSet(int npar,
                 const string* const par_name,
                 const double* const par);
    
    void Load(string file);

    void Copy(const MshpFuncPar* const org);
    MshpFuncPar* const Clone() const;

    void Print(FILE* fp) const;

    int GetNpar() const {return npar_;};
    const string* const GetParName() const {return par_name_;};
    const double* const GetPar() const     {return par_;};
    string GetParNameElm(int ipar) const {return par_name_[ipar];};
    double GetParElm(int ipar) const     {return par_[ipar];};
    
private:
    int npar_;
    string* par_name_;
    double* par_;

    void Null();
};

#endif // MXSIM_HELPER_FUNC_PAR_H_
