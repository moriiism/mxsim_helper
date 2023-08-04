#include "mshp_hist1d_nerr.h"

//
// public
//

// Init
void HistDataNerr1d::Init(long nbin_xval,
                          double xval_lo,
                          double xval_up)
{
    NullHistData1d();
    NewHi1d();
    GetHi1dNonConst()->InitSetByNbin(xval_lo, xval_up, nbin_xval);
    NewOvalArrAsDataArrayNerr1d();
    GetOvalArrNonConst()->Init(nbin_xval);    
}

void HistDataNerr1d::Init(const HistInfo1d* const hist_info)
{
    NullHistData1d();
    NewHi1d();
    GetHi1dNonConst()->InitSetByNbin(hist_info->GetLo(),
                                     hist_info->GetUp(),
                                     hist_info->GetNbin());
    NewOvalArrAsDataArrayNerr1d();
    GetOvalArrNonConst()->Init(hist_info->GetNbin());
}

HistDataNerr1d* const HistDataNerr1d::Clone() const
{
    HistDataNerr1d* obj_new = new HistDataNerr1d;
    obj_new->Copy(this);
    return obj_new;
}

void HistDataNerr1d::Load(string file)
{
    NullHistData1d();

    long nbin_xval = 0;
    double xval_lo = 0.0;
    double xval_up = 0.0;
    string format = "";
    ReadInfo(file, &nbin_xval, &xval_lo, &xval_up, &format);
    Init(nbin_xval, xval_lo, xval_up);
    
    if("x,y" != format){
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
    for(long iline = 0; iline < nline; iline ++){
        int ncolumn = MshpStr::GetNcolumn(line_arr[iline]);
        if(2 != ncolumn){
            MshpPrintErrClass("ncolumn != 2");
            abort();
        }
        istringstream iss(line_arr[iline]);
        iss >> xval >> oval;
        long ibin = GetIbin(xval);
        SetOvalElm(ibin, oval);
    }
    MshpIolib::DelReadFile(line_arr);
}

const DataArrayNerr1d* const HistDataNerr1d::GetOvalArr() const
{
    return dynamic_cast<const DataArrayNerr1d*>(GetOvalArrNonConst());
}

void HistDataNerr1d::PrintData(FILE* fp, string format,
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
                    0.0);
        }
    } else if ("x,y,ye+,ye-" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e\n",
                    GetBinCenter(ibin) - offset_xval,
                    GetOvalElm(ibin) - offset_oval, 0.0, 0.0);
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
                    0.0);
        }
    } else if ("x,xe,y,ye+,ye-" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e\n",
                    GetBinCenter(ibin) - offset_xval, GetXvalBinWidth()/2.,
                    GetOvalElm(ibin) - offset_oval, 0.0, 0.0);
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
                    GetOvalElm(ibin) - offset_oval, 0.0);
        }
    } else if ("x,xe+,xe-,y,ye+,ye-" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e  %.15e\n",
                    GetBinCenter(ibin) - offset_xval,
                    GetXvalBinWidth()/2., -1 * GetXvalBinWidth()/2.,
                    GetOvalElm(ibin) - offset_oval, 0.0, 0.0);
        }
    } else {
        char msg[kLineSize];
        sprintf(msg, "format(=%s)", format.c_str());
        MshpPrintErrClass(msg);
        abort();
    }
}


HistDataNerr1d* const HistDataNerr1d::GenHd1MaxInBin(long nbin_new) const
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
    
    HistDataNerr1d* h1d_new = new HistDataNerr1d;
    h1d_new->Init(nbin_new, GetXvalLo(), GetXvalUp());
  
    for(long ibin = 0; ibin < GetNbinX(); ibin ++){
        h1d_new->FillByLarger( GetBinCenter(ibin), GetOvalElm(ibin) );
    }

    return h1d_new;
}

void HistDataNerr1d::FillRandom(const MshpFunc* const func,
                                const double* const func_par,
                                int rand_seed)
{
    MshpRand* mrand = new MshpRand;
    mrand->Init(rand_seed);
    for(long ibin = 0; ibin < GetNbinX(); ibin ++){
        double xval = GetBinCenter(ibin);
        double oval = func->Eval1d(xval, func_par);
        double oval_rand = mrand->Poisson(oval);
        SetOvalElm(ibin, oval_rand);
    }
    delete mrand;
}

void HistDataNerr1d::FillRandom(const HistData1d* const hist_data, int rand_seed)
{
    Init(hist_data->GetNbinX(), hist_data->GetXvalLo(), hist_data->GetXvalUp());
    
    MshpRand* mrand = new MshpRand;
    mrand->Init(rand_seed);
    for(long ibin = 0; ibin < GetNbinX(); ibin ++){
        double oval_rand = mrand->Poisson(hist_data->GetOvalElm(ibin));
        SetOvalElm(ibin, oval_rand);
    }
    delete mrand;
}

HistDataNerr1d* HistDataNerr1d::GenSubHist(long ibinx_st, long ibinx_ed) const
{
    HistDataNerr1d* hd1d_sub = new HistDataNerr1d;
    long nbinx_sub = ibinx_ed - ibinx_st + 1;
    hd1d_sub->Init(nbinx_sub, GetBinLo(ibinx_st), GetBinUp(ibinx_ed));
    for(long ibinx = 0; ibinx < nbinx_sub; ibinx ++){
        hd1d_sub->SetOvalElm(ibinx, GetOvalElm(ibinx_st + ibinx));
    }
    return hd1d_sub;
}
