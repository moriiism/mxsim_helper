#include "mshp_func_par.h"

// public

void MshpFuncPar::Init(int npar)
{
    Null();
    
    npar_ = npar;
    par_name_ = new string [npar];
    par_      = new double [npar];
}

void MshpFuncPar::Set(int npar,
                      const string* const par_name,
                      const double* const par)
{
    if(npar_ != npar){
        abort();
    }
    for(int ipar = 0; ipar < npar; ipar++){
        par_name_[ipar] = par_name[ipar];
        par_[ipar]      = par[ipar];
    }
}

void MshpFuncPar::SetElm(int ipar,
                         string par_name,
                         double par)
{
    par_name_[ipar] = par_name;
    par_[ipar] = par;
}

void MshpFuncPar::InitSet(int npar,
                          const string* const par_name,
                          const double* const par)
{
    Init(npar);
    Set(npar, par_name, par);
}


void MshpFuncPar::Load(string file)
{
    Null();
    
    string* line_arr = NULL;
    long nline = 0;
    MshpIolib::GenReadFileSkipComment(file, &line_arr, &nline);
    Init(nline);
    for(long iline = 0; iline < nline; iline ++){
        int ncolumn = MshpStr::GetNcolumn(line_arr[iline]);
        if(2 != ncolumn){
            MshpPrintWarnClass("ncolumn != 2");
        }
        istringstream iss(line_arr[iline]);
        string par_name_tmp;
        double par_tmp;
        iss >> par_name_tmp >> par_tmp;
        SetElm(iline, par_name_tmp, par_tmp);
    }
    MshpIolib::DelReadFile(line_arr);
    if(0 < g_flag_verbose){
        MshpPrintInfoClass("done.");
    }
}


void MshpFuncPar::Copy(const MshpFuncPar* const org)
{
    if(this == org) {abort();}
    if(NULL == org) {abort();}
    
    CopyTitle(org);
    InitSet(org->GetNpar(),
            org->GetParName(),
            org->GetPar());
}

MshpFuncPar* const MshpFuncPar::Clone() const
{
    MshpFuncPar* obj_new = new MshpFuncPar;
    obj_new->Copy(this);
    return obj_new;
}


void MshpFuncPar::Print(FILE* fp) const
{
    fprintf(fp, "%s: npar = %d\n",
            GetClassName().c_str(), npar_);
    for(int ipar = 0; ipar < GetNpar(); ipar ++){
        fprintf(fp, "%s: par_name_[%d] = %s\n",
                GetClassName().c_str(),
                ipar, GetParNameElm(ipar).c_str());
        fprintf(fp, "%s: par_[%d]      = %e\n",
                GetClassName().c_str(),
                ipar, GetParElm(ipar));
    }
}

//
// private
//

void MshpFuncPar::Null()
{
    npar_ = 0;
    if(NULL != par_name_) {delete [] par_name_; par_name_ = NULL;}
    if(NULL != par_) {delete [] par_; par_ = NULL;}
}
