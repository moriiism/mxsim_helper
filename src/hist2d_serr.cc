#include "mshp_hist2d_serr.h"

//
// public
//

void HistDataSerr2d::Init(long nbin_xval, double xval_lo, double xval_up,
                          long nbin_yval, double yval_lo, double yval_up)
{
    NullHistData2d();
    NewHi2d();
    GetHi2dNonConst()->InitSetByNbin(xval_lo, xval_up, nbin_xval,
                                     yval_lo, yval_up, nbin_yval);
    NewOvalArrAsDataArraySerr1d();
    GetOvalArrNonConst()->Init(nbin_xval * nbin_yval);
}

void HistDataSerr2d::Init(const HistInfo2d* const hist_info)
{
    NullHistData2d();
    NewHi2d();
    GetHi2dNonConst()->InitSetByNbin(hist_info->GetLoX(),
                                     hist_info->GetUpX(),
                                     hist_info->GetNbinX(),
                                     hist_info->GetLoY(),
                                     hist_info->GetUpY(),
                                     hist_info->GetNbinY());  
    NewOvalArrAsDataArraySerr1d();
    GetOvalArrNonConst()->Init(hist_info->GetNbin());
}

void HistDataSerr2d::SetOvalSerrArr(long ndata, const double* const val_serr)
{
    IsOvalArrNotNull();
    GetOvalArrNonConst()->SetValSerr(ndata, val_serr);
}

void HistDataSerr2d::SetOvalSerrArr(vector<double> val_serr)
{
    IsOvalArrNotNull();
    GetOvalArrNonConst()->SetValSerr(val_serr);
}

void HistDataSerr2d::SetOvalSerrElm(long ibin_xval,
                                    long ibin_yval,
                                    double oval_serr)
{
    IsOvalArrNotNull();
    IsValidIbinX(ibin_xval);
    IsValidIbinY(ibin_yval);
    long ibin = GetHi2d()->GetIbin(ibin_xval, ibin_yval);
    GetOvalArrNonConst()->SetValSerrElm(ibin, oval_serr);
}

void HistDataSerr2d::FillByLarger(double xval, double yval,
                                  double oval,
                                  double oval_serr)
{
    IsOvalArrNotNull();
    IsValidRangeX(xval);
    IsValidRangeY(yval);
    long ibin = GetHi2d()->GetIbinFromXY(xval, yval);
    GetOvalArrNonConst()->FillByLarger(ibin, oval, oval_serr);
}

void HistDataSerr2d::FillBySmaller(double xval, double yval,
                                   double oval,
                                   double oval_serr)
{
    IsOvalArrNotNull();
    IsValidRangeX(xval);
    IsValidRangeY(yval);
    long ibin = GetHi2d()->GetIbinFromXY(xval, yval);
    GetOvalArrNonConst()->FillBySmaller(ibin, oval, oval_serr);
}

void HistDataSerr2d::SetOvalErrArrByPoissonErr()
{
    GetOvalArrNonConst()->SetValErrByPoissonErr();
}


HistDataSerr2d* const HistDataSerr2d::Clone() const
{
    HistDataSerr2d* obj_new = new HistDataSerr2d;
    obj_new->Copy(this);
    return obj_new;
}


//void HistDataSerr2d::Load(string file)
//{
//    NullHistData2d();
//
//    long nbin_xval = 0;
//    double xval_lo = 0.0;
//    double xval_up = 0.0;
//    long nbin_yval = 0;
//    double yval_lo = 0.0;
//    double yval_up = 0.0;
//    string format = "";
//    ReadInfo(file,
//             &nbin_xval, &xval_lo, &xval_up,
//             &nbin_yval, &yval_lo, &yval_up, &format);
//    Init(nbin_xval, xval_lo, xval_up,
//         nbin_yval, yval_lo, yval_up);
//    GraphDataSerr3d* gdata3d = new GraphDataSerr3d;
//    gdata3d->Load(file, format);
//    for(long idata = 0; idata < gdata3d->GetNdata(); idata++){
//        long ibin_x = GetHi2d()->GetIbinXFromX(gdata3d->GetXvalElm(idata));
//        long ibin_y = GetHi2d()->GetIbinYFromY(gdata3d->GetYvalElm(idata));
//        SetOvalElm(ibin_x, ibin_y, gdata3d->GetOvalElm(idata) );
//        SetOvalSerrElm(ibin_x, ibin_y, gdata3d->GetOvalSerrElm(idata) );
//    }
//    delete gdata3d;
//}


const DataArraySerr1d* const HistDataSerr2d::GetOvalArr() const
{
    return dynamic_cast<const DataArraySerr1d*>(GetOvalArrNonConst());
}

double HistDataSerr2d::GetOvalSerrElm(long ibin_xval, long ibin_yval) const
{
    IsOvalArrNotNull();
    IsValidIbinX(ibin_xval);
    IsValidIbinY(ibin_yval);
    long ibin = GetHi2d()->GetIbin(ibin_xval, ibin_yval);
    return GetOvalArr()->GetValSerrElm(ibin);
}

double HistDataSerr2d::GetOvalSerrElmAtXY(double xval, double yval) const
{
    IsOvalArrNotNull();
    IsValidRangeX(xval);
    IsValidRangeY(yval);
    long ibin_x = GetHi2d()->GetIbinXFromX(xval);
    long ibin_y = GetHi2d()->GetIbinYFromY(yval);
    return GetOvalSerrElm(ibin_x, ibin_y);
}

void HistDataSerr2d::GenOvalSerrArr(double** const oval_serr_arr_ptr,
                                    long* const nbin_ptr) const
{
    long nbin = GetNbin();
    double* oval_serr_arr = new double [nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        oval_serr_arr[ibin] = GetOvalArr()->GetValSerrElm(ibin);
    }
    *oval_serr_arr_ptr = oval_serr_arr;
    *nbin_ptr = nbin;
}

void HistDataSerr2d::PrintData(FILE* fp, string format,
                               double offset_xval,
                               double offset_yval,
                               double offset_oval) const
{
    long nbin = GetNbin();
    if("x,y,z" == format){
        for(long ibin = 0; ibin < nbin; ibin ++){
            double xval_bin_center, yval_bin_center;
            GetHi2d()->GetBinCenterXYFromIbin(ibin,
                                              &xval_bin_center,
                                              &yval_bin_center);
            long ibin_x = GetHi2d()->GetIbinX(ibin);
            long ibin_y = GetHi2d()->GetIbinY(ibin);
            fprintf(fp, "%.15e  %.15e  %.15e\n",
                    xval_bin_center - offset_xval,
                    yval_bin_center - offset_yval,
                    GetOvalElm(ibin_x, ibin_y) - offset_oval);
        }
    } else if ("x,y,z,ze" == format){
        for(long ibin = 0; ibin < nbin; ibin ++){
            double xval_bin_center, yval_bin_center;
            GetHi2d()->GetBinCenterXYFromIbin(ibin,
                                              &xval_bin_center,
                                              &yval_bin_center);
            long ibin_x = GetHi2d()->GetIbinX(ibin);
            long ibin_y = GetHi2d()->GetIbinY(ibin);
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e\n",
                    xval_bin_center - offset_xval,
                    yval_bin_center - offset_yval,
                    GetOvalElm(ibin_x, ibin_y) - offset_oval,
                    GetOvalSerrElm(ibin_x, ibin_y));
        }
    } else if("x,xe,y,ye,z,ze" == format){
        for(long ibin = 0; ibin < nbin; ibin ++){
            double xval_bin_center, yval_bin_center;
            GetHi2d()->GetBinCenterXYFromIbin(ibin,
                                              &xval_bin_center,
                                              &yval_bin_center);
            long ibin_x = GetHi2d()->GetIbinX(ibin);
            long ibin_y = GetHi2d()->GetIbinY(ibin);
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e  %.15e\n",
                    xval_bin_center - offset_xval, GetBinWidthX()/2.,
                    yval_bin_center - offset_yval, GetBinWidthY()/2.,
                    GetOvalElm(ibin_x, ibin_y) - offset_oval,
                    GetOvalSerrElm(ibin_x, ibin_y));
        }
    } else if ("x,xe,y,ye,z" == format){
        for(long ibin = 0; ibin < nbin; ibin ++){
            double xval_bin_center, yval_bin_center;
            GetHi2d()->GetBinCenterXYFromIbin(ibin,
                                              &xval_bin_center,
                                              &yval_bin_center);
            long ibin_x = GetHi2d()->GetIbinX(ibin);
            long ibin_y = GetHi2d()->GetIbinY(ibin);            
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e\n",
                    xval_bin_center - offset_xval, GetBinWidthX()/2.,
                    yval_bin_center - offset_yval, GetBinWidthY()/2.,
                    GetOvalElm(ibin_x, ibin_y) - offset_oval);
        }
    } else if ("x,y,z,ze+,ze-" == format){
        for(long ibin = 0; ibin < nbin; ibin ++){
            double xval_bin_center, yval_bin_center;
            GetHi2d()->GetBinCenterXYFromIbin(ibin,
                                              &xval_bin_center,
                                              &yval_bin_center);
            long ibin_x = GetHi2d()->GetIbinX(ibin);
            long ibin_y = GetHi2d()->GetIbinY(ibin);            
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e\n",
                    xval_bin_center - offset_xval, 
                    yval_bin_center - offset_yval, 
                    GetOvalElm(ibin_x, ibin_y) - offset_oval,
                    GetOvalSerrElm(ibin_x, ibin_y),
                    -1 * GetOvalSerrElm(ibin_x, ibin_y));
        }
    } else if("x,xe,y,ye,z,ze+,ze-" == format){
        for(long ibin = 0; ibin < nbin; ibin ++){
            double xval_bin_center, yval_bin_center;
            GetHi2d()->GetBinCenterXYFromIbin(ibin,
                                              &xval_bin_center,
                                              &yval_bin_center);
            long ibin_x = GetHi2d()->GetIbinX(ibin);
            long ibin_y = GetHi2d()->GetIbinY(ibin);
            fprintf(fp,
                    "%.15e  %.15e  "
                    "%.15e  %.15e  "
                    "%.15e  %.15e  %.15e\n",
                    xval_bin_center - offset_xval, GetBinWidthX()/2.,
                    yval_bin_center - offset_yval, GetBinWidthY()/2.,
                    GetOvalElm(ibin_x, ibin_y) - offset_oval,
                    GetOvalSerrElm(ibin_x, ibin_y),
                    -1 * GetOvalSerrElm(ibin_x, ibin_y));
        }
    } else if ("x,xe+,xe-,y,ye+,ye-,z,ze+,ze-" == format){
        for(long ibin = 0; ibin < nbin; ibin ++){
            double xval_bin_center, yval_bin_center;
            GetHi2d()->GetBinCenterXYFromIbin(ibin,
                                              &xval_bin_center,
                                              &yval_bin_center);
            long ibin_x = GetHi2d()->GetIbinX(ibin);
            long ibin_y = GetHi2d()->GetIbinY(ibin);            
            fprintf(fp,
                    "%.15e  %.15e  %.15e  "
                    "%.15e  %.15e  %.15e  "
                    "%.15e  %.15e  %.15e\n",
                    xval_bin_center - offset_xval, GetBinWidthX()/2.,
                    -1 * GetBinWidthX()/2.,
                    yval_bin_center - offset_yval, GetBinWidthY()/2.,
                    -1 * GetBinWidthX()/2.,
                    GetOvalElm(ibin_x, ibin_y) - offset_oval,
                    GetOvalSerrElm(ibin_x, ibin_y),
                    -1 * GetOvalSerrElm(ibin_x, ibin_y));
        }
    } else {
        char msg[kLineSize];
        sprintf(msg, "format(=%s)", format.c_str());
        MshpPrintErrClass(msg);
        abort();
    }
}


// poisson error
void HistDataSerr2d::FillRandom(const MshpFunc* const func,
                                const double* const func_par,
                                int rand_seed)
{
    MshpRand* mrand = new MshpRand;
    mrand->Init(rand_seed);
    for(long ibin = 0; ibin < GetNbin(); ibin ++){
        long ibin_x = GetHi2d()->GetIbinX(ibin);
        long ibin_y = GetHi2d()->GetIbinY(ibin);
        double xval = GetHi2d()->GetBinCenterXFromIbinX(ibin_x);
        double yval = GetHi2d()->GetBinCenterYFromIbinY(ibin_y);

        double xval_arr[2];
        xval_arr[0] = xval;
        xval_arr[1] = yval;
        double oval = func->Eval(xval_arr, func_par);

        // poisson error
        double oval_rand = mrand->Poisson(oval);
        double oval_err = sqrt(oval_rand);
        SetOvalElm(ibin_x, ibin_y, oval_rand);
        SetOvalSerrElm(ibin_x, ibin_y, oval_err);
    }
    delete mrand;
}

// gaussian error
void HistDataSerr2d::FillRandom(const MshpFunc* const func,
                                const double* const func_par,
                                const MshpFunc* const func_sigma,
                                const double* const func_par_sigma,
                                int rand_seed)
{
    MshpRand* mrand = new MshpRand;
    mrand->Init(rand_seed);
    for(long ibin = 0; ibin < GetNbin(); ibin ++){
        long ibin_x = GetHi2d()->GetIbinX(ibin);
        long ibin_y = GetHi2d()->GetIbinY(ibin);
        double xval = GetHi2d()->GetBinCenterXFromIbinX(ibin_x);
        double yval = GetHi2d()->GetBinCenterYFromIbinY(ibin_y);
        
        double xval_arr[2];
        xval_arr[0] = xval;
        xval_arr[1] = yval;
        double oval = func->Eval(xval_arr, func_par);
        
        // gaussian error
        double sigma = func_sigma->Eval(xval_arr, func_par_sigma);
        double oval_rand = mrand->Normal(oval, sigma);
        double oval_err = sigma;
        SetOvalElm(ibin_x, ibin_y, oval_rand);
        SetOvalSerrElm(ibin_x, ibin_y, oval_err);
    }
    delete mrand;
}

// poisson error
void HistDataSerr2d::FillRandom(const HistData2d* const hist_data,
                                int rand_seed)
{
    Init(hist_data->GetNbinX(), hist_data->GetXvalLo(), hist_data->GetXvalUp(),
         hist_data->GetNbinY(), hist_data->GetYvalLo(), hist_data->GetYvalUp());
    
    MshpRand* mrand = new MshpRand;
    mrand->Init(rand_seed);
    for(long ibin = 0; ibin < GetNbin(); ibin ++){
        long ibin_x = GetHi2d()->GetIbinX(ibin);
        long ibin_y = GetHi2d()->GetIbinY(ibin);
        
        // poisson error
        double oval_rand = mrand->Poisson(hist_data->GetOvalElm(ibin_x, ibin_y));
        double oval_err = sqrt(oval_rand);
        SetOvalElm(ibin_x, ibin_y, oval_rand);
        SetOvalSerrElm(ibin_x, ibin_y, oval_err);
    }
    delete mrand;
}

HistDataSerr2d* HistDataSerr2d::GenSubHist(long ibinx_st, long ibinx_ed,
                                           long ibiny_st, long ibiny_ed) const
{
    HistDataSerr2d* hd2d_sub = new HistDataSerr2d;
    long nbinx_sub = ibinx_ed - ibinx_st + 1;
    long nbiny_sub = ibiny_ed - ibiny_st + 1;
    double xlo_sub = GetHi2d()->GetHistInfoX()->GetBinLo(ibinx_st);
    double xup_sub = GetHi2d()->GetHistInfoX()->GetBinUp(ibinx_ed);
    double ylo_sub = GetHi2d()->GetHistInfoY()->GetBinLo(ibiny_st);
    double yup_sub = GetHi2d()->GetHistInfoY()->GetBinUp(ibiny_ed);    
    hd2d_sub->Init(nbinx_sub, xlo_sub, xup_sub,
                   nbiny_sub, ylo_sub, yup_sub);
    for(long ibinx = 0; ibinx < nbinx_sub; ibinx ++){
        for(long ibiny = 0; ibiny < nbiny_sub; ibiny ++){
            hd2d_sub->SetOvalElm(ibinx, ibiny,
                                 GetOvalElm(ibinx_st + ibinx, ibiny_st + ibiny));
            hd2d_sub->SetOvalSerrElm(ibinx, ibiny,
                                     GetOvalSerrElm(ibinx_st + ibinx,
                                                    ibiny_st + ibiny));
        }
    }
    return hd2d_sub;
}


