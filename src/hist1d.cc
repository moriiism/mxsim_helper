#include "mshp_hist1d.h"

//
// public
//

void HistData1d::SetOvalArr(const DataArray1d* const oval_arr)
{
    GetOvalArrNonConst()->Copy(oval_arr);
}

void HistData1d::SetOvalArr(long ndata, const double* const val)
{
    GetOvalArrNonConst()->SetVal(ndata, val);
}

void HistData1d::SetOvalArr(vector<double> val)
{
    GetOvalArrNonConst()->SetVal(val);
}

void HistData1d::SetOvalElm(long ibin, double oval)
{
    IsOvalArrNotNull();
    IsValidIbin(ibin);
    GetOvalArrNonConst()->SetValElm(ibin, oval);
}

void HistData1d::Fill(double xval)
{
    IsOvalArrNotNull();
    IsValidRange(xval);
    long ibin = GetIbin(xval);
    GetOvalArrNonConst()->Fill(ibin);
}

void HistData1d::Fill(double xval, double weight)
{
    IsOvalArrNotNull();
    IsValidRange(xval);
    long ibin = GetIbin(xval);
    GetOvalArrNonConst()->Fill(ibin, weight);
}

void HistData1d::FillByLarger(double xval, double oval)
{
    IsOvalArrNotNull();
    IsValidRange(xval);
    long ibin = GetIbin(xval);
    GetOvalArrNonConst()->FillByLarger(ibin, oval);
}

void HistData1d::FillBySmaller(double xval, double oval)
{
    IsOvalArrNotNull();
    IsValidRange(xval);
    long ibin = GetIbin(xval);    
    GetOvalArrNonConst()->FillBySmaller(ibin, oval);
}

void HistData1d::SetConst(double constant)
{
    IsOvalArrNotNull();
    GetOvalArrNonConst()->SetConst(constant);
}

void HistData1d::SetByFunc(const MshpFunc* const func, const double* const par)
{
    for(int ibin = 0; ibin < GetNbinX(); ibin ++){
        double xval = GetBinCenter(ibin);
        double xval_tmp[1];
        xval_tmp[0] = xval;
        double oval = func->Eval(xval_tmp, par);
        SetOvalElm(ibin, oval);
    }
}

void HistData1d::Copy(const HistData1d* const org)
{
    if(this == org) {abort();}
    if(NULL == org) {abort();}
    
    CopyTitle(org);
    Init(org->GetHi1d());
    SetOvalArr(org->GetOvalArr());
}

//
// const functions
//

double HistData1d::GetOvalElm(long ibin) const
{
    IsOvalArrNotNull();
    IsValidIbin(ibin);
    return GetOvalArr()->GetValElm(ibin);
}

double HistData1d::GetOvalElmAtX(double xval) const
{
    IsOvalArrNotNull();
    IsValidRange(xval);
    long ibin = GetIbin(xval);
    return GetOvalElm(ibin);
}

double HistData1d::GetXvalAtOvalMin() const
{
    return GetBinCenter(GetOvalArr()->GetLocValMin());
}
    
double HistData1d::GetXvalAtOvalMax() const
{
    return GetBinCenter(GetOvalArr()->GetLocValMax());
}

void HistData1d::GenXvalArr(double** const xval_arr_ptr,
                            long* const nbin_ptr) const
{
    long nbin = GetNbinX();
    double* xval_arr = new double [nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        xval_arr[ibin] = GetBinCenter(ibin);
    }
    *xval_arr_ptr = xval_arr;
    *nbin_ptr = nbin;
}

void HistData1d::GenXvalSerrArr(double** const xval_serr_arr_ptr,
                                long* const nbin_ptr) const
{
    long nbin = GetNbinX();
    double* xval_serr_arr = new double [nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        xval_serr_arr[ibin] = GetXvalBinWidth() / 2.0;
    }
    *xval_serr_arr_ptr = xval_serr_arr;
    *nbin_ptr = nbin;
}

void HistData1d::GenOvalArr(double** const oval_arr_ptr,
                            long* const nbin_ptr) const
{
    long nbin = GetNbinX();    
    double* oval_arr = new double [nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        oval_arr[ibin] = GetOvalArr()->GetValElm(ibin);
    }
    *oval_arr_ptr = oval_arr;
    *nbin_ptr = nbin;
}


long HistData1d::GetIbin(double xval) const
{
    long ibin = GetHi1d()->GetIbin(xval, "lin");
    return ibin;
}

double HistData1d::GetBinCenter(long ibin) const
{
    double bin_center = GetHi1d()->GetBinCenter(ibin, "lin");
    return bin_center;
}

double HistData1d::GetBinLo(long ibin) const
{
    double bin_lo = GetHi1d()->GetBinLo(ibin, "lin");
    return bin_lo;
}

double HistData1d::GetBinUp(long ibin) const
{
    double bin_up = GetHi1d()->GetBinUp(ibin, "lin");
    return bin_up;
}

long HistData1d::GetIbin_WithHalfBinShifted(double val) const
{
    long ibin = GetHi1d()->GetIbin_WithHalfBinShifted(val);
    return ibin;
}

void HistData1d::Save(string outfile, string format,
                      double offset_xval,
                      double offset_oval) const
{
    FILE* fp = fopen(outfile.c_str(), "w");
    PrintInfo(fp);
    fprintf(fp, "# format      = %s\n", format.c_str());
    fprintf(fp, "\n");
    PrintData(fp, format, offset_xval, offset_oval);
    fclose(fp);
}

void HistData1d::SaveData(string outfile, string format,
                          double offset_xval,
                          double offset_oval) const
{
    FILE* fp = fopen(outfile.c_str(), "w");
    PrintData(fp, format, offset_xval, offset_oval);
    fclose(fp);
}

void HistData1d::PrintInfo(FILE* fp) const
{
    fprintf(fp, "# nbin_xval_  = %ld\n", GetNbinX());
    fprintf(fp, "# xval_lo_    = %e\n", GetXvalLo());
    fprintf(fp, "# xval_up_    = %e\n", GetXvalUp());
}


void HistData1d::PrintData(FILE* fp, string format,
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

// generate events from histogram with poisson statistic
DataArrayNerr1d* const HistData1d::GenRandomEvt(int rand_seed) const
{
    MshpRand* mrand = new MshpRand;
    mrand->Init(rand_seed);
    vector<double> time_vec;

    double tbinfwidth = GetXvalBinWidth();
    for(long ibin = 0; ibin < GetNbinX(); ibin ++){
        double bin_center = GetBinCenter(ibin);
        double bin_lo     = bin_center - 0.5 * tbinfwidth;
        double count_wpe = mrand->Poisson(GetOvalElm(ibin));
      
        for(long ievt = 0; ievt < count_wpe; ievt ++){
            double time_evt = bin_lo + mrand->Uniform() * tbinfwidth;
            time_vec.push_back(time_evt);
        }
    }
    
    DataArrayNerr1d* data_arr = new DataArrayNerr1d;
    data_arr->Init(time_vec.size());
    data_arr->SetVal(time_vec);

    delete mrand;
    return data_arr;
}

// generate events from a probability distribution
void HistData1d::GenRandomEvtFromProbDist(
    int nevt,
    int rand_seed,
    double** xval_arr_ptr) const
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
    MshpRand* mrand = new MshpRand;
    mrand->Init(rand_seed);
    for(int ievt = 0; ievt < nevt; ievt++){
        double rand = mrand->Uniform();
        long ibin_find = MshpSort::BinarySearch(nbin, cum_arr, rand);
        xval_arr[ievt] = GetBinCenter(ibin_find + 1);
    }
    delete mrand;
    delete [] data_norm;
    delete [] cum_arr;
    *xval_arr_ptr = xval_arr;
}


double HistData1d::GetOffsetXFromTag(string offset_tag) const
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

double HistData1d::GetOffsetOFromTag(string offset_tag) const
{
    double offset = 0.0;
    if("st" == offset_tag){
        offset = GetOvalArr()->GetValAndErrMin();
    } else if ("ed" == offset_tag){
        offset = GetOvalArr()->GetValAndErrMax();
    } else if ("md" == offset_tag){
        offset = ( GetOvalArr()->GetValAndErrMin() +
                   GetOvalArr()->GetValAndErrMax() ) / 2.;
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

void HistData1d::ReadInfo(string file, 
                          long* nbin_xval_ptr,
                          double* xval_lo_ptr,
                          double* xval_up_ptr,
                          string* format_ptr)
{
    long nbin_xval = 0;
    double xval_lo = 0.0;
    double xval_up = 0.0;
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
        if("format" == split_arr[1]){
            format = split_arr[3];
        }        
        
        delete [] split_arr;
    }
    MshpIolib::DelReadFile(line_arr);

    *nbin_xval_ptr = nbin_xval;
    *xval_lo_ptr = xval_lo;
    *xval_up_ptr = xval_up;
    *format_ptr = format;
}


//
// protected
//

void HistData1d::NullHistData1d()
{
    if(NULL != hi1d_) {delete hi1d_; hi1d_ = NULL;}
    if(NULL != oval_arr_) {delete oval_arr_; oval_arr_ = NULL;}
}

void HistData1d::NewOvalArrAsDataArrayNerr1d()
{
    oval_arr_ = new DataArrayNerr1d;
}

void HistData1d::NewOvalArrAsDataArraySerr1d()
{
    oval_arr_ = new DataArraySerr1d;
}

void HistData1d::NewHi1d()
{
    hi1d_ = new HistInfo1d;
}

void HistData1d::IsHi1dNotNull() const
{
    if(NULL == GetHi1d()){
        abort();
    }
}

void HistData1d::IsOvalArrNotNull() const
{
    if(NULL == GetOvalArr()){
        abort();
    }
}

void HistData1d::IsValidIbin(long ibin) const
{
    GetHi1d()->IsValidIbin(ibin);
}

void HistData1d::IsValidRange(double val) const
{
    GetHi1d()->IsValidRange(val);
}

