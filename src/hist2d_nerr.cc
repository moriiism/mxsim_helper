#include "mshp_hist2d_nerr.h"

//
// public
//

void HistDataNerr2d::Init(long nbin_xval, double xval_lo, double xval_up,
                          long nbin_yval, double yval_lo, double yval_up)

{
    NullHistData2d();
    NewHi2d();
    GetHi2dNonConst()->InitSetByNbin(xval_lo, xval_up, nbin_xval,
                                     yval_lo, yval_up, nbin_yval);
    NewOvalArrAsDataArrayNerr1d();
    GetOvalArrNonConst()->Init(nbin_xval * nbin_yval);
}

void HistDataNerr2d::Init(const HistInfo2d* const hist_info)
{
    NullHistData2d();
    NewHi2d();
    GetHi2dNonConst()->InitSetByNbin(hist_info->GetLoX(),
                                     hist_info->GetUpX(),
                                     hist_info->GetNbinX(),
                                     hist_info->GetLoY(),
                                     hist_info->GetUpY(),
                                     hist_info->GetNbinY());  
    NewOvalArrAsDataArrayNerr1d();
    GetOvalArrNonConst()->Init(hist_info->GetNbin());
}

HistDataNerr2d* const HistDataNerr2d::Clone() const
{
    HistDataNerr2d* obj_new = new HistDataNerr2d;
    obj_new->Copy(this);
    return obj_new;
}

//void HistDataNerr2d::Load(string file)
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
//
//    if("x,y,z" != format){
//        char msg[kLineSize];
//        sprintf(msg, "format(=%s)", format.c_str());
//        MshpPrintErrClass(msg);
//        abort();
//    }
//    GraphDataNerr3d* gdata3d = new GraphDataNerr3d;
//    gdata3d->Load(file, format);
//    for(long idata = 0; idata < gdata3d->GetNdata(); idata++){
//        long ibin_x = GetHi2d()->GetIbinXFromX(gdata3d->GetXvalElm(idata));
//        long ibin_y = GetHi2d()->GetIbinYFromY(gdata3d->GetYvalElm(idata));
//        SetOvalElm(ibin_x, ibin_y, gdata3d->GetOvalElm(idata) );
//    }
//    delete gdata3d;
//}

const DataArrayNerr1d* const HistDataNerr2d::GetOvalArr() const
{
    return dynamic_cast<const DataArrayNerr1d*>(GetOvalArrNonConst());
}

void HistDataNerr2d::PrintData(FILE* fp, string format,
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
                    GetOvalElm(ibin_x, ibin_y) - offset_oval, 0.0);
        }
    } else if ("x,xe,y,ye,z,ze" == format){
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
                    GetOvalElm(ibin_x, ibin_y) - offset_oval, 0.0);
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
                    GetOvalElm(ibin_x, ibin_y) - offset_oval, 0.0, 0.0);
        }
    } else if ("x,xe,y,ye,z,ze+,ze-" == format){
        for(long ibin = 0; ibin < nbin; ibin ++){
            double xval_bin_center, yval_bin_center;
            GetHi2d()->GetBinCenterXYFromIbin(ibin,
                                              &xval_bin_center,
                                              &yval_bin_center);
            long ibin_x = GetHi2d()->GetIbinX(ibin);
            long ibin_y = GetHi2d()->GetIbinY(ibin);            
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e  %.15e  %.15e\n",
                    xval_bin_center - offset_xval, GetBinWidthX()/2.,
                    yval_bin_center - offset_yval, GetBinWidthY()/2.,
                    GetOvalElm(ibin_x, ibin_y) - offset_oval, 0.0, 0.0);
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
                    "%.15e  %.15e  %.15e  %.15e  %.15e  %.15e  "
                    "%.15e  %.15e  %.15e\n",
                    xval_bin_center - offset_xval, GetBinWidthX()/2.,
                    -1 * GetBinWidthX()/2.,
                    yval_bin_center - offset_yval, GetBinWidthY()/2.,
                    -1 * GetBinWidthX()/2.,
                    GetOvalElm(ibin_x, ibin_y) - offset_oval, 0.0, 0.0);
        }
    } else {
        char msg[kLineSize];
        sprintf(msg, "format(=%s)", format.c_str());
        MshpPrintErrClass(msg);
        abort();
    }
}

void HistDataNerr2d::FillRandom(const MshpFunc* const func,
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

        double oval_rand = mrand->Poisson(oval);
        SetOvalElm(ibin_x, ibin_y, oval_rand);
    }
    delete mrand;
}

void HistDataNerr2d::FillRandom(const HistData2d* const hist_data,
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
        SetOvalElm(ibin_x, ibin_y, oval_rand);
    }
    delete mrand;
}

HistDataNerr2d* HistDataNerr2d::GenSubHist(long ibinx_st, long ibinx_ed,
                                           long ibiny_st, long ibiny_ed) const
{
    HistDataNerr2d* hd2d_sub = new HistDataNerr2d;
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
            hd2d_sub->SetOvalElm(
                ibinx, ibiny,
                GetOvalElm(ibinx_st + ibinx, ibiny_st + ibiny));
        }
    }
    return hd2d_sub;
}
