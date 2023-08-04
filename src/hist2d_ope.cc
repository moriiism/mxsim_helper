#include "mshp_hist2d_ope.h"

DataArray1d** const HistData2dOpe::GenDa1dArrNerr(
    const HistData2d* const* const hd2d_arr,
    int narr)
{
    DataArray1d** da1d_arr = new DataArray1d* [narr];
    for(int iarr = 0; iarr < narr; iarr ++){
        da1d_arr[iarr] = new DataArrayNerr1d;
        da1d_arr[iarr]->Copy(hd2d_arr[iarr]->GetOvalArr());
    }
    return da1d_arr;
}

DataArray1d** const HistData2dOpe::GenDa1dArrSerr(
    const HistData2d* const* const hd2d_arr,
    int narr)
{
    DataArray1d** da1d_arr = new DataArray1d* [narr];
    for(int iarr = 0; iarr < narr; iarr ++){
        da1d_arr[iarr] = new DataArraySerr1d;
        da1d_arr[iarr]->Copy(hd2d_arr[iarr]->GetOvalArr());
    }
    return da1d_arr;
}

void HistData2dOpe::DelHd2dArr(HistData2d** const hd2d_arr, int narr)
{
    for(int iarr = 0; iarr < narr; iarr ++){
        delete hd2d_arr[iarr];
    }
    delete [] hd2d_arr;
}

int HistData2dOpe::IsFormatSame(const HistData2d* const data1,
                                const HistData2d* const data2)
{
    if(data1->GetNbinX()  != data2->GetNbinX()  ||
       data1->GetXvalLo() != data2->GetXvalLo() ||
       data1->GetXvalUp() != data2->GetXvalUp() ||
       data1->GetNbinY()  != data2->GetNbinY()  ||
       data1->GetYvalLo() != data2->GetYvalLo() ||
       data1->GetYvalUp() != data2->GetYvalUp()   ){
        MshpPrintErr("format of data1 and data2 are diffenret.");
        char msg[kLineSize];
        sprintf(msg, "data1: (GetNbinX(), GetXvalLo(), GetXvalUp()) "
                "= (%ld, %e, %e)\n",
                data1->GetNbinX(),
                data1->GetXvalLo(),
                data1->GetXvalUp());
        MshpPrintErr(msg);
        sprintf(msg, "data1: (GetNbinY(), GetYvalLo(), GetYvalUp()) "
                "= (%ld, %e, %e)\n",
                data1->GetNbinY(),
                data1->GetYvalLo(),
                data1->GetYvalUp());
        MshpPrintErr(msg);        
        sprintf(msg, "data2: (GetNbinX(), GetXvalLo(), GetXvalUp()) "
                "= (%ld, %e, %e)\n",
                data2->GetNbinX(),
                data2->GetXvalLo(),
                data2->GetXvalUp());
        MshpPrintErr(msg);        
        sprintf(msg, "data2: (GetNbinY(), GetYvalLo(), GetYvalUp()) "
                "= (%ld, %e, %e)\n",
                data2->GetNbinY(),
                data2->GetYvalLo(),
                data2->GetYvalUp());
        MshpPrintErr(msg);        
        abort();
    }
    return 1;
}

int HistData2dOpe::IsFormatSame(const HistData2d* const* const data_arr,
                                int nhist)
{
    if(nhist < 2){
        char msg[kLineSize];
        sprintf(msg, "nhist(=%d) < 2\n", nhist);
        MshpPrintWarn(msg);
        MshpPrintWarn("skip check");
        return 0;
    }
    for(int ihist = 1; ihist < nhist; ihist++){
        if(data_arr[0]->GetNbinX()  != data_arr[ihist]->GetNbinX()  ||
           data_arr[0]->GetXvalLo() != data_arr[ihist]->GetXvalLo() ||
           data_arr[0]->GetXvalUp() != data_arr[ihist]->GetXvalUp() ||
           data_arr[0]->GetNbinY()  != data_arr[ihist]->GetNbinY()  ||
           data_arr[0]->GetYvalLo() != data_arr[ihist]->GetYvalLo() ||
           data_arr[0]->GetYvalUp() != data_arr[ihist]->GetYvalUp()   ){
            char msg[kLineSize];
            sprintf(msg, "format of data_arr[0] and data_arr[%d] are different\n",
                    ihist);
            MshpPrintErr(msg);
            sprintf(msg, "data_arr[0]: (GetNbinX(), GetXvalLo(), GetXvalUp()) "
                    "= (%ld, %e, %e)\n",
                    data_arr[0]->GetNbinX(),
                    data_arr[0]->GetXvalLo(),
                    data_arr[0]->GetXvalUp());
            MshpPrintErr(msg);            
            sprintf(msg, "data_arr[0]: (GetNbinY(), GetYvalLo(), GetYvalUp()) "
                    "= (%ld, %e, %e)\n",
                    data_arr[0]->GetNbinY(),
                    data_arr[0]->GetYvalLo(),
                    data_arr[0]->GetYvalUp());
            MshpPrintErr(msg);                        
            sprintf(msg, "data_arr[%d]: (GetNbinX(), GetXvalLo(), GetXvalUp()) "
                    "= (%ld, %e, %e)\n",
                    ihist,
                    data_arr[ihist]->GetNbinX(),
                    data_arr[ihist]->GetXvalLo(),
                    data_arr[ihist]->GetXvalUp());
            MshpPrintErr(msg);                                    
            sprintf(msg, "data_arr[%d]: (GetNbinY(), GetYvalLo(), GetYvalUp()) "
                    "= (%ld, %e, %e)\n",
                    ihist,
                    data_arr[ihist]->GetNbinY(),
                    data_arr[ihist]->GetYvalLo(),
                    data_arr[ihist]->GetYvalUp());
            MshpPrintErr(msg);                                    
            abort();
        }
    }
    return 1;
}


void HistData2dOpe::GetProjectX(const HistData2d* const in,
                                long ibin_ylo, long ibin_yup,
                                string calc_mode,
                                HistDataNerr1d* const out)
{
    in->GetHi2d()->IsValidIbinY(ibin_ylo);
    in->GetHi2d()->IsValidIbinY(ibin_yup);
    
    out->Init(in->GetNbinX(),
              in->GetXvalLo(),
              in->GetXvalUp());
    for(long ibin_xval = 0; ibin_xval < in->GetNbinX(); ibin_xval++){
        long nbin_tmp = ibin_yup - ibin_ylo + 1;
        double* tmp_arr = new double [nbin_tmp];
        long ibin_tmp = 0;
        for(long ibin_yval = ibin_ylo; ibin_yval <= ibin_yup; ibin_yval++){
            tmp_arr[ibin_tmp] = in->GetOvalElm(ibin_xval, ibin_yval);
            ibin_tmp ++;
        }
        double val_proj = 0.0;
        GetProject(nbin_tmp, tmp_arr,
                   calc_mode, in->GetBinWidthY(),
                   &val_proj);
        delete [] tmp_arr;
        out->SetOvalElm(ibin_xval, val_proj);
    }
}

void HistData2dOpe::GetProjectX(const HistData2d* const in,
                                long ibin_ylo, long ibin_yup,
                                string calc_mode, string error_mode,
                                HistDataSerr1d* const out)
{
    in->GetHi2d()->IsValidIbinY(ibin_ylo);
    in->GetHi2d()->IsValidIbinY(ibin_yup);
    out->Init(in->GetNbinX(),
              in->GetXvalLo(),
              in->GetXvalUp());
    for(long ibin_xval = 0; ibin_xval < in->GetNbinX(); ibin_xval++){
        long nbin_tmp = ibin_yup - ibin_ylo + 1;
        double* tmp_arr = new double [nbin_tmp];
        double* tmp_err_arr = new double [nbin_tmp];
        long ibin_tmp = 0;
        for(long ibin_yval = ibin_ylo; ibin_yval <= ibin_yup; ibin_yval++){
            tmp_arr[ibin_tmp]     = in->GetOvalElm(ibin_xval, ibin_yval);
            tmp_err_arr[ibin_tmp] = in->GetOvalSerrElm(ibin_xval, ibin_yval);
            ibin_tmp ++;
        }
        double val_proj = 0.0;
        double val_proj_err = 0.0;
        GetProject(nbin_tmp,
                   tmp_arr, tmp_err_arr,
                   calc_mode, error_mode,
                   in->GetBinWidthY(),
                   &val_proj, &val_proj_err);
        delete [] tmp_arr;
        delete [] tmp_err_arr;
        out->SetOvalElm(ibin_xval, val_proj);
        out->SetOvalSerrElm(ibin_xval, val_proj_err);
    }
}

void HistData2dOpe::GetProjectY(const HistData2d* const in,
                                long ibin_xlo, long ibin_xup,
                                string calc_mode,
                                HistDataNerr1d* const out)
{
    in->GetHi2d()->IsValidIbinX(ibin_xlo);
    in->GetHi2d()->IsValidIbinX(ibin_xup);
    
    out->Init(in->GetNbinY(),
              in->GetYvalLo(),
              in->GetYvalUp());
    for(long ibin_yval = 0; ibin_yval < in->GetNbinY(); ibin_yval++){
        long nbin_tmp = ibin_xup - ibin_xlo + 1;
        double* tmp_arr = new double [nbin_tmp];
        long ibin_tmp = 0;
        for(long ibin_xval = ibin_xlo; ibin_xval <= ibin_xup; ibin_xval++){
            tmp_arr[ibin_tmp] = in->GetOvalElm(ibin_xval, ibin_yval);
            ibin_tmp ++;
        }
        double val_proj = 0.0;
        GetProject(nbin_tmp, tmp_arr,
                   calc_mode, in->GetBinWidthX(),
                   &val_proj);
        delete [] tmp_arr;
        out->SetOvalElm(ibin_yval, val_proj);
    }
}

void HistData2dOpe::GetProjectY(const HistData2d* const in,
                                long ibin_xlo, long ibin_xup,
                                string calc_mode, string error_mode,
                                HistDataSerr1d* const out)
{
    in->GetHi2d()->IsValidIbinX(ibin_xlo);
    in->GetHi2d()->IsValidIbinX(ibin_xup);
    out->Init(in->GetNbinY(),
              in->GetYvalLo(),
              in->GetYvalUp());
    for(long ibin_yval = 0; ibin_yval < in->GetNbinY(); ibin_yval++){
        long nbin_tmp = ibin_xup - ibin_xlo + 1;
        double* tmp_arr = new double [nbin_tmp];
        double* tmp_err_arr = new double [nbin_tmp];
        long ibin_tmp = 0;
        for(long ibin_xval = ibin_xlo; ibin_xval <= ibin_xup; ibin_xval++){
            tmp_arr[ibin_tmp]     = in->GetOvalElm(ibin_xval, ibin_yval);
            tmp_err_arr[ibin_tmp] = in->GetOvalSerrElm(ibin_xval, ibin_yval);
            ibin_tmp ++;
        }
        double val_proj = 0.0;
        double val_proj_err = 0.0;
        GetProject(nbin_tmp,
                   tmp_arr, tmp_err_arr,
                   calc_mode, error_mode,
                   in->GetBinWidthX(),
                   &val_proj, &val_proj_err);
        delete [] tmp_arr;
        delete [] tmp_err_arr;
        out->SetOvalElm(ibin_yval, val_proj);
        out->SetOvalSerrElm(ibin_yval, val_proj_err);
    }
}


void HistData2dOpe::GetProject(long ndata,
                               const double* const array,
                               string calc_mode, double bin_width,
                               double* const val_proj_ptr)
{
    double val_proj = 0.0;
    if("add" == calc_mode){
        val_proj = MshpMath::GetSum(ndata, array);
    } else if ("integral" == calc_mode){
        val_proj = MshpMath::GetSum(ndata, array) * bin_width;
    } else if ("amean" == calc_mode){
        val_proj = MshpMath::GetAMean(ndata, array);
    } else if ("min" == calc_mode){
        val_proj = MshpMath::GetMin(ndata, array);
    } else if ("max" == calc_mode){
        val_proj = MshpMath::GetMax(ndata, array);
    } else if ("stddev" == calc_mode){
        val_proj = MshpMath::GetStddev(ndata, array);
    } else {
        MshpPrintErr("bad calc_mode");
        abort();
    }
    *val_proj_ptr = val_proj;
}

void HistData2dOpe::GetProject(long ndata,
                               const double* const array,
                               const double* const array_err,
                               string calc_mode, string error_mode,
                               double bin_width,
                               double* const val_proj_ptr,
                               double* const val_proj_err_ptr)
{
    double val_proj = 0.0;
    double val_proj_err = 0.0;
    if("add" == calc_mode || "integral" == calc_mode){
        if("gauss" == error_mode){
            MshpMath::GetSum(ndata, array, array_err, &val_proj, &val_proj_err);
        } else if("poisson" == error_mode){
            val_proj = MshpMath::GetSum(ndata, array);
            val_proj_err = sqrt(val_proj);
        } else if("zero" == error_mode){
            val_proj = MshpMath::GetSum(ndata, array);
            val_proj_err = 0.0;
        } else {
            MshpPrintErr("bad error_mode");
            abort();
        }
        if("integral" == calc_mode){
            val_proj *= bin_width;
            val_proj_err *= bin_width;
        }
    } else if ("amean" == calc_mode){
        if("gauss" == error_mode){
            MshpMath::GetAMean(ndata, array, array_err, &val_proj, &val_proj_err);
        } else if("poisson" == error_mode){
            double val_add = MshpMath::GetSum(ndata, array);
            val_proj = val_add / ndata;
            val_proj_err = sqrt(val_add) / ndata;
        } else if("zero" == error_mode){
            double val_add = MshpMath::GetSum(ndata, array);
            val_proj = val_add / ndata;
            val_proj_err = 0.0;
        } else {
            MshpPrintErr("bad error_mode");
            abort();
        }
    } else if ("wmean" == calc_mode){
        if("gauss" == error_mode || "zero" == error_mode){
            long nsel = 0;
            int* mask_sel_arr = NULL;
            MshpMath::GenWMean(ndata, array, array_err,
                               &val_proj, &val_proj_err,
                               &nsel, &mask_sel_arr);
            delete [] mask_sel_arr;
            if("zero" == error_mode){
                val_proj_err = 0.0;
            }
        } else {
            MshpPrintErr("bad error_mode");
            abort();
        }

    } else if ("min" == calc_mode){
        long index = MshpMath::GetLocMin(ndata, array);
        val_proj = array[index];
        if("gauss" == error_mode || "poisson" == error_mode){
            val_proj_err = array_err[index];
        } else if("zero" == error_mode) {
            val_proj_err = 0.0;
        } else {
            MshpPrintErr("bad error_mode");
            abort();
        }
    } else if ("max" == calc_mode){
        long index = MshpMath::GetLocMax(ndata, array);
        val_proj = array[index];
        if("gauss" == error_mode || "poisson" == error_mode){
            val_proj_err = array_err[index];
        } else if("zero" == error_mode) {
            val_proj_err = 0.0;
        } else {
            MshpPrintErr("bad error_mode");
            abort();
        }
    } else {
        MshpPrintErr("bad calc_mode");
        abort();
    }

    *val_proj_ptr = val_proj;
    *val_proj_err_ptr = val_proj_err;
}
