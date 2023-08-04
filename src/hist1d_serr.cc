#include "mshp_hist1d_serr.h"

//
// public
//

void HistDataSerr1d::Init(long nbin_xval,
                          double xval_lo,
                          double xval_up)
{
    NullHistData1d();
    NewHi1d();
    GetHi1dNonConst()->InitSetByNbin(xval_lo, xval_up, nbin_xval);
    NewOvalArrAsDataArraySerr1d();
    GetOvalArrNonConst()->Init(nbin_xval);
}

void HistDataSerr1d::Init(const HistInfo1d* const hist_info)
{
    NullHistData1d();
    NewHi1d();
    GetHi1dNonConst()->InitSetByNbin(hist_info->GetLo(),
                                     hist_info->GetUp(),
                                     hist_info->GetNbin());
    NewOvalArrAsDataArraySerr1d();
    GetOvalArrNonConst()->Init(hist_info->GetNbin());
}

void HistDataSerr1d::SetOvalSerrArr(long ndata, const double* const val_serr)
{
    IsOvalArrNotNull();
    GetOvalArrNonConst()->SetValSerr(ndata, val_serr);
}
    
void HistDataSerr1d::SetOvalSerrArr(vector<double> val_serr)
{
    IsOvalArrNotNull();
    GetOvalArrNonConst()->SetValSerr(val_serr);
}

void HistDataSerr1d::SetOvalSerrElm(long ibin, double oval_serr)
{
    IsOvalArrNotNull();
    GetOvalArrNonConst()->SetValSerrElm(ibin, oval_serr);

}

void HistDataSerr1d::FillByLarger(double xval,
                                  double oval,
                                  double oval_serr)
{
    IsOvalArrNotNull();
    long ibin = GetIbin(xval);
    GetOvalArrNonConst()->FillByLarger(ibin, oval, oval_serr);
}

void HistDataSerr1d::FillBySmaller(double xval,
                                   double oval,
                                   double oval_serr)
{
    IsOvalArrNotNull();    
    long ibin = GetIbin(xval);
    GetOvalArrNonConst()->FillBySmaller(ibin, oval, oval_serr);
}


void HistDataSerr1d::SetOvalErrArrByPoissonErr()
{
    GetOvalArrNonConst()->SetValErrByPoissonErr();
}

HistDataSerr1d* const HistDataSerr1d::Clone() const
{
    HistDataSerr1d* obj_new = new HistDataSerr1d;
    obj_new->Copy(this);
    return obj_new;
}


void HistDataSerr1d::Load(string file)
{
    NullHistData1d();

    long nbin_xval = 0;
    double xval_lo = 0.0;
    double xval_up = 0.0;
    string format = "";
    ReadInfo(file, &nbin_xval, &xval_lo, &xval_up, &format);    
    Init(nbin_xval, xval_lo, xval_up);

    if("x,y,ye" != format){
        char msg[kLineSize];
        sprintf(msg, "format(=%s)", format.c_str());
        MshpPrintErrClass(msg);
        abort();
    }
    string* line_arr = NULL;
    long nline = 0;
    MshpIolib::GenReadFileSkipComment(file, &line_arr, &nline);
    if(nline != nbin_xval){
        char msg[kLineSize];
        sprintf(msg, "nline != nbin_xval");
        MshpPrintErrClass(msg);
        abort();
    }
    double xval = 0.0;
    double oval = 0.0;
    double oval_serr = 0.0; 
    for(long iline = 0; iline < nline; iline ++){
        int ncolumn = MshpStr::GetNcolumn(line_arr[iline]);
        if(3 != ncolumn){
            MshpPrintErrClass("ncolumn != 3");
            abort();
        }
        istringstream iss(line_arr[iline]);
        iss >> xval >> oval >> oval_serr;
        long ibin = GetIbin(xval);
        SetOvalElm(ibin, oval);
        SetOvalSerrElm(ibin, oval_serr);
    }
    MshpIolib::DelReadFile(line_arr);
}


const DataArraySerr1d* const HistDataSerr1d::GetOvalArr() const
{
    return dynamic_cast<const DataArraySerr1d*>(GetOvalArrNonConst());
}

double HistDataSerr1d::GetOvalSerrElm(long ibin) const
{
    IsOvalArrNotNull();
    return GetOvalArr()->GetValSerrElm(ibin);
}

double HistDataSerr1d::GetOvalSerrElmAtX(double xval) const
{
    IsOvalArrNotNull();
    long ibin = GetIbin(xval);
    return GetOvalSerrElm(ibin);
}

void HistDataSerr1d::PrintData(FILE* fp, string format,
                               double offset_xval,
                               double offset_oval) const
{
    long nbin_xval = GetNbinX();
    if("x,y" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e\n",
                    GetBinCenter(ibin) - offset_xval,
                    GetOvalElm(ibin) - offset_oval);
        }
    } else if ("x,y,ye" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e\n",
                    GetBinCenter(ibin) - offset_xval,
                    GetOvalElm(ibin) - offset_oval,
                    GetOvalSerrElm(ibin));
        }
    } else if ("x,y,ye+,ye-" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e\n",
                    GetBinCenter(ibin) - offset_xval,
                    GetOvalElm(ibin) - offset_oval,
                    GetOvalSerrElm(ibin),
                    -1 * GetOvalSerrElm(ibin) );
        }
    } else if ("x,xe,y" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e\n",
                    GetBinCenter(ibin) - offset_xval, GetXvalBinWidth()/2.,
                    GetOvalElm(ibin) - offset_oval);
        }
    } else if ("x,xe,y,ye" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e\n",
                    GetBinCenter(ibin) - offset_xval, GetXvalBinWidth()/2.,
                    GetOvalElm(ibin) - offset_oval,
                    GetOvalSerrElm(ibin));
        }
    } else if ("x,xe,y,ye+,ye-" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e\n",
                    GetBinCenter(ibin) - offset_xval, GetXvalBinWidth()/2.,
                    GetOvalElm(ibin) - offset_oval,
                    GetOvalSerrElm(ibin),
                    -1 * GetOvalSerrElm(ibin) );
        }
    } else if ("x,xe+,xe-,y" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e\n",
                    GetBinCenter(ibin) - offset_xval,
                    GetXvalBinWidth()/2., -1 * GetXvalBinWidth()/2.,
                    GetOvalElm(ibin) - offset_oval);
        }
    } else if ("x,xe+,xe-,y,ye" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e\n",
                    GetBinCenter(ibin) - offset_xval,
                    GetXvalBinWidth()/2., -1 * GetXvalBinWidth()/2.,
                    GetOvalElm(ibin) - offset_oval,
                    GetOvalSerrElm(ibin) );
        }
    } else if ("x,xe+,xe-,y,ye+,ye-" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e  %.15e\n",
                    GetBinCenter(ibin) - offset_xval,
                    GetXvalBinWidth()/2., -1 * GetXvalBinWidth()/2.,
                    GetOvalElm(ibin) - offset_oval,
                    GetOvalSerrElm(ibin),
                    -1 * GetOvalSerrElm(ibin) );
        }
    } else {
        char msg[kLineSize];
        sprintf(msg, "format(=%s)", format.c_str());
        MshpPrintErrClass(msg);
        abort();
    }
  
}


HistDataSerr1d* const HistDataSerr1d::GenHd1MaxInBin(long nbin_new) const
{
    if(nbin_new > GetNbinX()){
        MshpPrintErrClass("bad nbin_new");
        abort();
    }
    if(nbin_new < 1){
        MshpPrintErrClass("bad nbin_new");
        abort();
    }
    if(0 != GetNbinX() % nbin_new){
        MshpPrintErrClass("bad nbin_new");
        abort();
    }

    HistDataSerr1d* h1d_new = new HistDataSerr1d;
    h1d_new->Init(nbin_new, GetXvalLo(), GetXvalUp());
  
    for(long ibin = 0; ibin < GetNbinX(); ibin ++){
        h1d_new->FillByLarger(GetBinCenter(ibin),
                              GetOvalElm(ibin),
                              GetOvalSerrElm(ibin));
    }

    return h1d_new;
}

void HistDataSerr1d::FillRandom(const MshpFunc* const func,
                                const double* const func_par,
                                int rand_seed)
{
    MshpRand* mrand = new MshpRand;
    mrand->Init(rand_seed);
    for(long ibin = 0; ibin < GetNbinX(); ibin ++){
        double xval = GetBinCenter(ibin);
        double oval = func->Eval1d(xval, func_par);

        // poisson error
        double oval_rand = mrand->Poisson(oval);
        double oval_err = sqrt(oval_rand);
        SetOvalElm(ibin, oval_rand);
        SetOvalSerrElm(ibin, oval_err);
    }
    delete mrand;
}

void HistDataSerr1d::FillRandom(const MshpFunc* const func,
                                const double* const func_par,
                                const MshpFunc* const func_sigma,
                                const double* const func_par_sigma,
                                int rand_seed)
{
    MshpRand* mrand = new MshpRand;
    mrand->Init(rand_seed);
    for(long ibin = 0; ibin < GetNbinX(); ibin ++){
        double xval = GetBinCenter(ibin);
        double oval = func->Eval1d(xval, func_par);
        
        // gaussian error
        double sigma = func_sigma->Eval1d(xval, func_par_sigma);
        double oval_rand = mrand->Normal(oval, sigma);
        double oval_err = sigma;
        SetOvalElm(ibin, oval_rand);
        SetOvalSerrElm(ibin, oval_err);
    }
    delete mrand;
}


void HistDataSerr1d::FillRandom(const HistData1d* const hist_data, int rand_seed)
{
    Init(hist_data->GetNbinX(), hist_data->GetXvalLo(), hist_data->GetXvalUp());
    
    MshpRand* mrand = new MshpRand;
    mrand->Init(rand_seed);
    for(long ibin = 0; ibin < GetNbinX(); ibin ++){
        // poisson error
        double oval_rand = mrand->Poisson(hist_data->GetOvalElm(ibin));
        double oval_err = sqrt(oval_rand);
        SetOvalElm(ibin, oval_rand);
        SetOvalSerrElm(ibin, oval_err);
    }
    delete mrand;
}

HistDataSerr1d* HistDataSerr1d::GenSubHist(long ibinx_st, long ibinx_ed) const
{
    HistDataSerr1d* hd1d_sub = new HistDataSerr1d;
    long nbinx_sub = ibinx_ed - ibinx_st + 1;
    hd1d_sub->Init(nbinx_sub, GetBinLo(ibinx_st), GetBinUp(ibinx_ed));
    for(long ibinx = 0; ibinx < nbinx_sub; ibinx ++){
        hd1d_sub->SetOvalElm(ibinx, GetOvalElm(ibinx_st + ibinx));
        hd1d_sub->SetOvalSerrElm(ibinx, GetOvalSerrElm(ibinx_st + ibinx));
    }
    return hd1d_sub;
}


