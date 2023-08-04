#include "mshp_hist2d.h"
#include "mshp_hist1d_nerr.h"

//
// public
//

void HistData2d::SetOvalArr(const DataArray1d* const oval_arr)
{
    GetOvalArrNonConst()->Copy(oval_arr);
}

void HistData2d::SetOvalArr(long ndata, const double* const val)
{
    IsOvalArrNotNull();
    GetOvalArrNonConst()->SetVal(ndata, val);
}

void HistData2d::SetOvalArr(vector<double> val)
{
    IsOvalArrNotNull();
    GetOvalArrNonConst()->SetVal(val);
}

void HistData2d::SetOvalElm(long ibin_xval, long ibin_yval, double oval)
{
    IsOvalArrNotNull();
    IsValidIbinX(ibin_xval);
    IsValidIbinY(ibin_yval);
    long ibin = GetHi2d()->GetIbin(ibin_xval, ibin_yval);
    GetOvalArrNonConst()->SetValElm(ibin, oval);
}

void HistData2d::Fill(double xval, double yval)
{
    IsOvalArrNotNull();
    IsValidRangeX(xval);
    IsValidRangeY(yval);
    long ibin = GetHi2d()->GetIbinFromXY(xval, yval);
    GetOvalArrNonConst()->Fill(ibin);
}

void HistData2d::Fill(double xval, double yval, double weight)
{
    IsOvalArrNotNull();
    IsValidRangeX(xval);
    IsValidRangeY(yval);
    long ibin = GetHi2d()->GetIbinFromXY(xval, yval);
    GetOvalArrNonConst()->Fill(ibin, weight);
}

void HistData2d::FillByLarger(double xval, double yval, double oval)
{
    IsOvalArrNotNull();
    IsValidRangeX(xval);
    IsValidRangeY(yval);
    long ibin = GetHi2d()->GetIbinFromXY(xval, yval);
    GetOvalArrNonConst()->FillByLarger(ibin, oval);
}

void HistData2d::FillBySmaller(double xval, double yval, double oval)
{
    IsOvalArrNotNull();
    IsValidRangeX(xval);
    IsValidRangeY(yval);
    long ibin = GetHi2d()->GetIbinFromXY(xval, yval);
    GetOvalArrNonConst()->FillBySmaller(ibin, oval);
}

void HistData2d::SetConst(double constant)
{
    IsOvalArrNotNull();    
    GetOvalArrNonConst()->SetConst(constant);
}

// Set by Func
void HistData2d::SetByFunc(const MshpFunc* const func, const double* const par)
{
    for(int ibinx = 0; ibinx < GetNbinX(); ibinx ++){
        for(int ibiny = 0; ibiny < GetNbinY(); ibiny ++){
            double xval = GetHi2d()->GetBinCenterXFromIbinX(ibinx);
            double yval = GetHi2d()->GetBinCenterYFromIbinY(ibiny);
            double xval_tmp[2];
            xval_tmp[0] = xval;
            xval_tmp[1] = yval;
            double oval = func->Eval(xval_tmp, par);
            SetOvalElm(ibinx, ibiny, oval);
        }
    }
}

void HistData2d::Copy(const HistData2d* const org)
{
    if(this == org) {abort();}
    if(NULL == org) {abort();}
    
    CopyTitle(org);
    Init(org->GetHi2d());
    SetOvalArr(org->GetOvalArr());
}


double HistData2d::GetOvalElm(long ibin_xval, long ibin_yval) const
{
    IsOvalArrNotNull();
    IsValidIbinX(ibin_xval);
    IsValidIbinY(ibin_yval);
    long ibin = GetHi2d()->GetIbin(ibin_xval, ibin_yval);
    double oval = GetOvalArr()->GetValElm(ibin);
    return oval;
}


double HistData2d::GetOvalElmAtXY(double xval, double yval) const
{
    IsOvalArrNotNull();
    IsValidRangeX(xval);
    IsValidRangeY(yval);
    long ibin_x = GetHi2d()->GetIbinXFromX(xval);
    long ibin_y = GetHi2d()->GetIbinYFromY(yval);
    double oval = GetOvalElm(ibin_x, ibin_y);
    return oval;
}

// stat
double HistData2d::GetXvalAtOvalMin() const
{
    long ibin = GetOvalArr()->GetLocValMin();
    double xval = GetHi2d()->GetBinCenterXFromIbin(ibin);
    return xval;
}
    
double HistData2d::GetXvalAtOvalMax() const
{
    long ibin = GetOvalArr()->GetLocValMax();
    double xval = GetHi2d()->GetBinCenterXFromIbin(ibin);
    return xval;
}


double HistData2d::GetYvalAtOvalMin() const
{
    long ibin = GetOvalArr()->GetLocValMin();
    double yval = GetHi2d()->GetBinCenterYFromIbin(ibin);
    return yval;
}
    
double HistData2d::GetYvalAtOvalMax() const
{
    long ibin = GetOvalArr()->GetLocValMax();
    double yval = GetHi2d()->GetBinCenterYFromIbin(ibin);
    return yval;
}

// gen xval_arr, yval_arr, oval_arr
void HistData2d::GenXYvalArr(double** const xval_arr_ptr,
                             double** const yval_arr_ptr,
                             long* const nbin_ptr) const
{
    long nbin = GetNbin();
    double* xval_arr = new double [nbin];
    double* yval_arr = new double [nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        double xval, yval;
        GetHi2d()->GetBinCenterXYFromIbin(ibin, &xval, &yval);
        xval_arr[ibin] = xval;
        yval_arr[ibin] = yval;
    }
    *xval_arr_ptr = xval_arr;
    *yval_arr_ptr = yval_arr;
    *nbin_ptr = nbin;
}

void HistData2d::GenXYvalSerrArr(double** const xval_serr_arr_ptr,
                                 double** const yval_serr_arr_ptr,
                                 long* const nbin_ptr) const
{
    long nbin = GetNbin();
    double* xval_serr_arr = new double [nbin];
    double* yval_serr_arr = new double [nbin];
    double xval_serr = GetBinWidthX() / 2.0;
    double yval_serr = GetBinWidthY() / 2.0;
    for(long ibin = 0; ibin < nbin; ibin++){
        xval_serr_arr[ibin] = xval_serr;
        yval_serr_arr[ibin] = yval_serr;
    }
    *xval_serr_arr_ptr = xval_serr_arr;
    *yval_serr_arr_ptr = yval_serr_arr;
    *nbin_ptr = nbin;
}


void HistData2d::GenOvalArr(double** const oval_arr_ptr,
                            long* const nbin_ptr) const
{
    long nbin = GetNbin();
    double* oval_arr = new double [nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        oval_arr[ibin] = GetOvalArr()->GetValElm(ibin);
    }
    *oval_arr_ptr = oval_arr;
    *nbin_ptr = nbin;
}


double HistData2d::GetOvalIntPolLin(double xval, double yval) const
{
    abort();
    
    double ans = 0.0;
//    long index_xval = GetIbinX_WithHalfBinShifted(xval);
//    long index_yval = GetIbinY_WithHalfBinShifted(yval);
//    
//    if (-1 < index_xval && index_xval < nbin_xval_ - 1 &&
//        -1 < index_yval && index_yval < nbin_yval_ - 1   ){
//        long index_xval0 = index_xval;
//        long index_xval1 = index_xval0 + 1;
//        long index_yval0 = index_yval;
//        long index_yval1 = index_yval0 + 1;
//
//        long index0 = index_xval0 + index_yval0 * nbin_xval_;
//        long index1 = index0 + 1;
//        long index2 = index0 + nbin_xval_ + 1;
//        long index3 = index0 + nbin_xval_;
//        
//        ans = MshpMath::IntPolLin(xval, yval,
//                                 GetBinCenterXFromIbinX(index_xval0),
//                                 GetBinCenterXFromIbinX(index_xval1),
//                                 GetBinCenterYFromIbinY(index_yval0),
//                                 GetBinCenterYFromIbinY(index_yval1),
//                                 GetOvalArr()->GetValElm(index0),
//                                 GetOvalArr()->GetValElm(index1),
//                                 GetOvalArr()->GetValElm(index2),
//                                 GetOvalArr()->GetValElm(index3));
//    } else {
//        if(0 < g_flag_verbose){
//            MshpPrintWarnClass("bad xval and/or yval, then just return 0.0");
//        }
//        ans = 0.0;
//    }
    return ans;
}

void HistData2d::Save(string outfile, string format,
                      double offset_xval,
                      double offset_yval,
                      double offset_oval) const
{
    FILE* fp = fopen(outfile.c_str(), "w");
    PrintInfo(fp);
    fprintf(fp, "# format      = %s\n", format.c_str());
    fprintf(fp, "\n");
    PrintData(fp, format, offset_xval, offset_yval, offset_oval);
    fclose(fp);
}

void HistData2d::SaveData(string outfile, string format,
                          double offset_xval,
                          double offset_yval,
                          double offset_oval) const
{
    FILE* fp = fopen(outfile.c_str(), "w");
    PrintData(fp, format, offset_xval, offset_yval, offset_oval);
    fclose(fp);
}

void HistData2d::PrintInfo(FILE* fp) const
{
    fprintf(fp, "# nbin_xval_  = %ld\n", GetNbinX());
    fprintf(fp, "# xval_lo_    = %e\n", GetXvalLo());
    fprintf(fp, "# xval_up_    = %e\n", GetXvalUp());
    fprintf(fp, "# nbin_yval_  = %ld\n", GetNbinY());
    fprintf(fp, "# yval_lo_    = %e\n", GetYvalLo());
    fprintf(fp, "# yval_up_    = %e\n", GetYvalUp());
}


// generate events from a probability distribution
void HistData2d::GenRandomEvtFromProbDist(
    int nevt,
    int rand_seed,
    double** xval_arr_ptr,
    double** yval_arr_ptr) const
{
    long nbin = GetOvalArr()->GetNdata();
    double sum = MshpMath::GetSum(nbin, GetOvalArr()->GetVal());
    // normalize
    double* data_norm = new double [nbin];
    for(long ibin = 0; ibin < nbin; ibin ++){
        data_norm[ibin] = GetOvalArr()->GetValElm(ibin) / sum;
    }
    // cumulative dist
    double* cum_arr = new double [nbin];
    double cum = 0.0;
    for(long ibin = 0; ibin < nbin; ibin ++){
        cum += data_norm[ibin];
        cum_arr[ibin] = cum;
        printf("cum_arr = %e\n", cum_arr[ibin]);
    }

    double* xval_arr = new double[nevt];
    double* yval_arr = new double[nevt];
    MshpRand* mrand = new MshpRand;
    mrand->Init(rand_seed);
    for(int ievt = 0; ievt < nevt; ievt++){
        double rand = mrand->Uniform();
        long ibin_find = MshpSort::BinarySearch(nbin, cum_arr, rand);
        xval_arr[ievt] = GetHi2d()->GetBinCenterXFromIbin(ibin_find + 1);
        yval_arr[ievt] = GetHi2d()->GetBinCenterYFromIbin(ibin_find + 1);
    }
    delete mrand;
    delete [] data_norm;
    delete [] cum_arr;
    *xval_arr_ptr = xval_arr;
    *yval_arr_ptr = yval_arr;
}


double HistData2d::GetOffsetXFromTag(string offset_tag) const
{
    double offset = 0.0;
    if("st" == offset_tag){
        offset = GetXvalLo();
    } else if ("ed" == offset_tag){
        offset = GetXvalUp();
    } else if ("md" == offset_tag){
        offset = ( GetXvalLo() + GetXvalUp() ) / 2.;
    } else if ("no" == offset_tag){
        offset = 0.0;
    } else {
        offset = atof(offset_tag.c_str());
    }
    return offset;
}


double HistData2d::GetOffsetYFromTag(string offset_tag) const
{
    double offset = 0.0;
    if("st" == offset_tag){
        offset = GetYvalLo();
    } else if ("ed" == offset_tag){
        offset = GetYvalUp();
    } else if ("md" == offset_tag){
        offset = ( GetYvalLo() + GetYvalUp() ) / 2.;
    } else if ("no" == offset_tag){
        offset = 0.0;        
    } else {
        offset = atof(offset_tag.c_str());
    }
    return offset;
}


double HistData2d::GetOffsetOFromTag(string offset_tag) const
{
    double offset = 0.0;
    if("st" == offset_tag){
        offset = GetOvalArr()->GetValMin();
    } else if ("ed" == offset_tag){
        offset = GetOvalArr()->GetValMax();
    } else if ("md" == offset_tag){
        offset = ( GetOvalArr()->GetValMin() + GetOvalArr()->GetValMax() ) / 2.;
    } else if ("no" == offset_tag){
        offset = 0.0;
    } else {
        offset = atof(offset_tag.c_str());
    }
    return offset;
}

//
// static
//

void HistData2d::ReadInfo(string file,
                          long* nbin_xval_ptr,
                          double* xval_lo_ptr,
                          double* xval_up_ptr,
                          long* nbin_yval_ptr,
                          double* yval_lo_ptr,
                          double* yval_up_ptr,
                          string* format_ptr)
{
    long nbin_xval = 0;
    double xval_lo = 0.0;
    double xval_up = 0.0;
    long nbin_yval = 0;
    double yval_lo = 0.0;
    double yval_up = 0.0;
    string format = "";
    
    string* line_arr = NULL;
    long ndata = 0;
    MshpIolib::GenReadFileComment(file, &line_arr, &ndata);
    for(long idata = 0; idata < ndata; idata ++){
        int ncolumn = 0;
        string* split_arr = NULL;
        MshpStr::GenSplit(line_arr[idata], &ncolumn, &split_arr);
        if(4 != ncolumn){
            continue;
        }
        if("nbin_xval_" == split_arr[1]){
            nbin_xval = atoi(split_arr[3].c_str());
        }
        if("xval_lo_" == split_arr[1]){
            xval_lo = atof(split_arr[3].c_str());
        }
        if("xval_up_" == split_arr[1]){
            xval_up = atof(split_arr[3].c_str());
        }

        if("nbin_yval_" == split_arr[1]){
            nbin_yval = atoi(split_arr[3].c_str());
        }
        if("yval_lo_" == split_arr[1]){
            yval_lo = atof(split_arr[3].c_str());
        }
        if("yval_up_" == split_arr[1]){
            yval_up = atof(split_arr[3].c_str());
        }
        
        if("format" == split_arr[1]){
            format = split_arr[3];
        }        
        
        delete [] split_arr;
    }
    MshpIolib::DelReadFile(line_arr);

    *nbin_xval_ptr = nbin_xval;
    *xval_lo_ptr = xval_lo;
    *xval_up_ptr = xval_up;
    *nbin_yval_ptr = nbin_yval;
    *yval_lo_ptr = yval_lo;
    *yval_up_ptr = yval_up;    
    *format_ptr = format;

    if(0 < g_flag_verbose){
        MshpPrintInfo("done.");
    }
}



//
// protected
//

void HistData2d::NullHistData2d()
{
    if(NULL != hi2d_) {delete hi2d_; hi2d_ = NULL;}
    if(NULL != oval_arr_) {delete oval_arr_; oval_arr_ = NULL;}
}

void HistData2d::NewOvalArrAsDataArrayNerr1d()
{
    oval_arr_ = new DataArrayNerr1d;
}

void HistData2d::NewOvalArrAsDataArraySerr1d()
{
    oval_arr_ = new DataArraySerr1d;
}

void HistData2d::NewHi2d()
{
    hi2d_ = new HistInfo2d;
}

void HistData2d::IsHi2dNotNull() const
{
    if(NULL == GetHi2d()){
        MshpPrintErrClass("bad GetHi2d() (=NULL)");
        abort();
    }
}

void HistData2d::IsOvalArrNotNull() const
{
    if(NULL == GetOvalArr()){
        MshpPrintErrClass("bad GetOvalArr() (=NULL)");
        abort();
    }

}

void HistData2d::IsValidIbinX(long ibin_xval) const
{
    GetHi2d()->IsValidIbinX(ibin_xval);
}

void HistData2d::IsValidIbinY(long ibin_yval) const
{
    GetHi2d()->IsValidIbinY(ibin_yval);
}

void HistData2d::IsValidRangeX(double xval) const
{
    GetHi2d()->IsValidRangeX(xval);
}

void HistData2d::IsValidRangeY(double yval) const
{
    GetHi2d()->IsValidRangeY(yval);
}

