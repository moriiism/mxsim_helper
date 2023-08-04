#include "mshp_hist_info.h"

//
// HistInfo1d
//

//
// public
//

void HistInfo1d::InitSetByNbin(double lo, double up, long nbin)
{
    Null();
    lo_   = lo;
    up_   = up;
    nbin_ = nbin;
}

void HistInfo1d::InitSetByWidth(double lo, double up,
                                double bin_width, string mode)
{
    Null();
    
    long nbin_tmp = 0;
    if("floor" == mode){
        nbin_tmp = (long) floor( (up - lo) / bin_width);
    } else if ("ceil" == mode){
        nbin_tmp = (long) ceil( (up - lo) / bin_width);
    } else {
        MshpPrintErrClass("bad mode");
        abort();
    }

    lo_   = lo;
    nbin_ = nbin_tmp;
    up_ = lo_ + nbin_ * bin_width;
}

void HistInfo1d::InitSetByMidPoint(double md, double bin_width,
                                   double half_width, string mode)
{
    Null();
    
    long nbin_tmp = 0;
    if("floor" == mode){
        nbin_tmp = (long) floor( half_width / bin_width );
    } else if ("ceil" == mode){
        nbin_tmp = (long) ceil ( half_width / bin_width );
    } else {
        MshpPrintErrClass("bad mode");
        abort();
    }
    lo_ = md - (nbin_tmp + 0.5) * bin_width;
    up_ = md + (nbin_tmp + 0.5) * bin_width;
    nbin_ = nbin_tmp * 2 + 1;
}

void HistInfo1d::Load(string file)
{
    Null();
    
    string* line_arr = NULL;
    long nline;
    MshpIolib::GenReadFileSkipComment(file, &line_arr, &nline);
    if(1 != nline){
        MshpPrintErrClass("bad nline");
        abort();
    }

    int ncolumn = MshpStr::GetNcolumn(line_arr[0]);
    if(5 != ncolumn){
        MshpPrintErrClass("ncolum != 5");
        abort();
    }

    istringstream iss(line_arr[0]);
    string nbin_str = "";
    long nbin = 0;
    double lo = 0.0;
    double up = 0.0;
    string bin_width_str = "";
    double bin_width = 0.0;
    string mode = "";
    
    iss >> nbin_str >> lo >> up >> bin_width_str >> mode;
    MshpIolib::DelReadFile(line_arr);

    if("none" == nbin_str){
        bin_width = atof(bin_width_str.c_str());
        InitSetByWidth(lo, up, bin_width, mode);
    } else {
        if("none" != bin_width_str){
            MshpPrintErrClass("bin_width_str != none");
            abort();
        }
        if("none" != mode){
            MshpPrintErrClass("mode != none");
            abort();
        }
        nbin = atoi(nbin_str.c_str());
        InitSetByNbin(lo, up, nbin);
    }
}

void HistInfo1d::Copy(const HistInfo1d* const org)
{
    if(this == org) {abort();}
    if(NULL == org) {abort();}
    
    CopyTitle(org);
    InitSetByNbin(org->GetLo(), org->GetUp(), org->GetNbin());
}

HistInfo1d* const HistInfo1d::Clone() const
{
    HistInfo1d* obj_new = new HistInfo1d;
    obj_new->Copy(this);
    return obj_new;
}

// const func

double HistInfo1d::GetMd() const
{
    double md = ( GetLo() + GetUp() ) / 2.0;
    return md;
}

double HistInfo1d::GetMdLog() const
{
    IsValidForLogScale();
    
    double lo_log = log10(GetLo());
    double up_log = log10(GetUp());
    double md_log = (lo_log + up_log) / 2.0;
    double md = pow(10.0, md_log);
    return md;
}

double HistInfo1d::GetBinWidth() const
{
    double bin_width = ( GetUp() - GetLo() ) / GetNbin();
    return bin_width;
}

double HistInfo1d::GetBinWidthLog(long ibin) const
{
    IsValidForLogScale();
    double lo_at_ibin = GetBinLo(ibin, "log");
    double up_at_ibin = GetBinUp(ibin, "log");
    double bin_width = up_at_ibin - lo_at_ibin;
    return bin_width;
}

long HistInfo1d::GetIbin(double val, string scale) const
{
    IsValidRange(val);
    
    long ibin = 0;
    if("lin" == scale){
        double bin_width = GetBinWidth();
        ibin = static_cast<long>(
            floor( ( val - GetLo() ) / bin_width )
            );
    } else if("log" == scale){
        IsValidForLogScale();
        
        double lo_log = log10(GetLo());
        double up_log = log10(GetUp());
        double bin_width_log = (up_log - lo_log) / GetNbin();
        double val_log = log10(val);
        ibin = static_cast<long>(
            floor( ( val_log - lo_log ) / bin_width_log )
            );
    } else {
        char msg[kLineSize];
        sprintf(msg, "bad scale (=%s)",
                scale.c_str());
        MshpPrintErr(msg);
        abort();
    }
    return ibin;
}

double HistInfo1d::GetBinCenter(long ibin, string scale) const
{
    IsValidIbin(ibin);
    
    double bin_center = 0.0;
    if("lin" == scale){
        double bin_width = GetBinWidth();
        bin_center = GetLo() + (ibin + 0.5) * bin_width;
    } else if("log" == scale){
        IsValidForLogScale();
        double lo_log = log10(GetLo());
        double up_log = log10(GetUp());
        double bin_width_log = (up_log - lo_log) / GetNbin();
        double bin_center_log = lo_log + (ibin + 0.5) * bin_width_log;
        bin_center = pow(10.0, bin_center_log);
    } else {
        char msg[kLineSize];
        sprintf(msg, "bad scale (=%s)",
                scale.c_str());
        MshpPrintErr(msg);
        abort();
    }
    return bin_center;
}


double HistInfo1d::GetBinLo(long ibin, string scale) const
{
    IsValidIbin(ibin);
    double bin_lo = 0.0;
    if("lin" == scale){
        double bin_width = GetBinWidth();
        bin_lo = GetLo() + ibin * bin_width;
    } else if("log" == scale){
        IsValidForLogScale();
        double lo_log = log10(GetLo());
        double up_log = log10(GetUp());
        double bin_width_log = (up_log - lo_log) / GetNbin();
        double bin_lo_log = lo_log + ibin * bin_width_log;
        bin_lo = pow(10.0, bin_lo_log);
    } else {
        char msg[kLineSize];
        sprintf(msg, "bad scale (=%s)",
                scale.c_str());
        MshpPrintErr(msg);
        abort();
    }
    return bin_lo;
}


double HistInfo1d::GetBinUp(long ibin, string scale) const
{
    IsValidIbin(ibin);
    double bin_up = 0.0;
    if("lin" == scale){
        double bin_width = GetBinWidth();
        bin_up = GetLo() + (ibin + 1) * bin_width;
    } else if("log" == scale){
        IsValidForLogScale();
        double lo_log = log10(GetLo());
        double up_log = log10(GetUp());
        double bin_width_log = (up_log - lo_log) / GetNbin();
        double bin_up_log = lo_log + (ibin + 1) * bin_width_log;
        bin_up = pow(10.0, bin_up_log);
    } else {
        char msg[kLineSize];
        sprintf(msg, "bad scale (=%s)",
                scale.c_str());
        MshpPrintErr(msg);
        abort();
    }
    return bin_up;
}

long HistInfo1d::GetIbin_WithHalfBinShifted(double val) const
{
    IsValidRange(val);
    double val_lo_half_bin_shifted = GetLo() + 0.5 * GetBinWidth();
    long ibin = static_cast<long>(
        floor((val - val_lo_half_bin_shifted) / GetBinWidth()) );
    return ibin;
}

void HistInfo1d::GenValArr(double** const val_arr_ptr,
                           long* const nbin_ptr,
                           string scale) const
{
    long nbin = GetNbin();
    double* val_arr = new double [nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        val_arr[ibin] = GetBinCenter(ibin, scale);
    }
    *val_arr_ptr = val_arr;
    *nbin_ptr = nbin;
}


void HistInfo1d::GenValSerrArr(double** const val_serr_arr_ptr,
                               long* const nbin_ptr,
                               string scale) const
{
    long nbin = GetNbin();
    double* val_serr_arr = new double [nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        val_serr_arr[ibin] = (GetBinUp(ibin, scale) - GetBinLo(ibin, scale))
            / 2.0;
    }
    *val_serr_arr_ptr = val_serr_arr;
    *nbin_ptr = nbin;
}


void HistInfo1d::GenValTerrArr(double** const val_terr_plus_arr_ptr,
                               double** const val_terr_minus_arr_ptr,
                               long* const nbin_ptr,
                               string scale) const
{
    long nbin = GetNbin();
    double* val_terr_plus_arr = new double [nbin];
    double* val_terr_minus_arr = new double [nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        val_terr_plus_arr[ibin] = GetBinUp(
            ibin, scale) - GetBinCenter(ibin, scale);
        val_terr_minus_arr[ibin] = GetBinLo(
            ibin, scale) - GetBinCenter(ibin, scale);
    }
    *val_terr_plus_arr_ptr = val_terr_plus_arr;
    *val_terr_minus_arr_ptr = val_terr_minus_arr;
    *nbin_ptr = nbin;
}


double HistInfo1d::GetOffsetFromTag(string offset_tag) const
{
    double offset = 0.0;
    if("st" == offset_tag){
        offset = GetLo();
    } else if ("ed" == offset_tag){
        offset = GetUp();
    } else if ("md" == offset_tag){
        offset = GetMd();
    } else if ("no" == offset_tag){
        offset = 0.0;
    } else {
        offset = atof(offset_tag.c_str());
    }
    return offset;
}


void HistInfo1d::Print(FILE* fp) const
{
    fprintf(fp, "nbin_ = %ld\n", GetNbin());
    fprintf(fp, "lo_   = %f\n", GetLo());
    fprintf(fp, "up_   = %f\n", GetUp());
}

void HistInfo1d::SetHistInfo(string line, HistInfo1d* const hist_info_out)
{
    int ncolumn = MshpStr::GetNcolumn(line);
    if(5 != ncolumn){
        MshpPrintErr("ncolum != 5");
        abort();
    }

    istringstream iss(line);
    string nbin_str = "";
    long nbin = 0;
    double lo = 0.0;
    double up = 0.0;
    string bin_width_str = "";
    double bin_width = 0.0;
    string mode = "";
    
    iss >> nbin_str >> lo >> up >> bin_width_str >> mode;
    if("none" == nbin_str){
        bin_width = atof(bin_width_str.c_str());
        hist_info_out->InitSetByWidth(lo, up, bin_width, mode);
    } else {
        if("none" != bin_width_str){
            MshpPrintErr("bin_width_str != none");
            abort();
        }
        if("none" != mode){
            MshpPrintErr("mode != none");
            abort();
        }
        nbin = atoi(nbin_str.c_str());
        hist_info_out->InitSetByNbin(lo, up, nbin);
    }
}

void HistInfo1d::IsValidForLogScale() const
{
    if(GetLo() < DBL_EPSILON ||
       GetUp() < DBL_EPSILON){
        char msg[kLineSize];
        sprintf(msg, "bad lo (=%e) or up (=%e)",
                GetLo(), GetUp());
        MshpPrintErr(msg);
        abort();
    }
}

void HistInfo1d::IsValidIbin(long ibin) const
{
    if(ibin < 0 || GetNbin() <= ibin){
        char msg[kLineSize];
        sprintf(msg, "bad ibin (=%ld)", ibin);
        MshpPrintErr(msg);
        abort();
    }
}

void HistInfo1d::IsValidRange(double val) const
{
    if(val < GetLo() || GetUp() < val){
        char msg[kLineSize];
        sprintf(msg, "bad val (=%e)", val);
        MshpPrintErr(msg);
        abort();
    }
}

// private

void HistInfo1d::Null()
{
    nbin_ = 0;
    lo_   = 0.0;
    up_   = 0.0;
}

//
// HistInfo2d
//

//
// public
//

void HistInfo2d::InitSetByNbin(double lo_x, double up_x, long nbin_x,
                               double lo_y, double up_y, long nbin_y)
{
    Null();
    hist_info_x_ = new HistInfo1d;
    hist_info_y_ = new HistInfo1d;
    hist_info_x_->InitSetByNbin(lo_x, up_x, nbin_x);
    hist_info_y_->InitSetByNbin(lo_y, up_y, nbin_y);    
}

void HistInfo2d::InitSetByWidth(double lo_x, double up_x,
                                double bin_width_x, string mode_x,
                                double lo_y, double up_y,
                                double bin_width_y, string mode_y)
{
    Null();
    hist_info_x_ = new HistInfo1d;
    hist_info_y_ = new HistInfo1d;
    hist_info_x_->InitSetByWidth(lo_x, up_x, bin_width_x, mode_x);
    hist_info_y_->InitSetByWidth(lo_y, up_y, bin_width_y, mode_y);
}


void HistInfo2d::InitSetByMidPoint(double md_x, double bin_width_x,
                                   double half_width_x, string mode_x,
                                   double md_y, double bin_width_y,
                                   double half_width_y, string mode_y)
{
    Null();
    hist_info_x_ = new HistInfo1d;
    hist_info_y_ = new HistInfo1d;
    hist_info_x_->InitSetByMidPoint(md_x, bin_width_x, half_width_x, mode_x);
    hist_info_y_->InitSetByMidPoint(md_y, bin_width_y, half_width_y, mode_y);
}


void HistInfo2d::Load(string file)
{
    Null();
    
    string* line_arr = NULL;
    long nline;
    MshpIolib::GenReadFileSkipComment(file, &line_arr, &nline);
    if(2 != nline){
        MshpPrintErrClass("bad nline");
        abort();
    }

    hist_info_x_ = new HistInfo1d;
    hist_info_y_ = new HistInfo1d;
    HistInfo1d::SetHistInfo(line_arr[0], hist_info_x_);
    HistInfo1d::SetHistInfo(line_arr[1], hist_info_y_);
    MshpIolib::DelReadFile(line_arr);
}

void HistInfo2d::Copy(const HistInfo2d* const org)
{
    if(this == org) {abort();}
    if(NULL == org) {abort();}
    
    CopyTitle(org);
    Null();
    hist_info_x_ = new HistInfo1d;
    hist_info_y_ = new HistInfo1d;
    hist_info_x_->Copy(org->GetHistInfoX());
    hist_info_y_->Copy(org->GetHistInfoY());
}

HistInfo2d* const HistInfo2d::Clone() const
{
    HistInfo2d* obj_new = new HistInfo2d;
    obj_new->Copy(this);
    return obj_new;
}


long HistInfo2d::GetIbin(long ibin_xval, long ibin_yval) const
{
    IsValidIbinX(ibin_xval);
    IsValidIbinY(ibin_yval);
    long ibin = ibin_xval + GetNbinX() * ibin_yval;
    return ibin;
}
    
long HistInfo2d::GetIbinX(long ibin) const
{
    long ibin_xval = ibin % GetNbinX();
    IsValidIbinX(ibin_xval);
    return ibin_xval;
}

long HistInfo2d::GetIbinY(long ibin) const
{
    long ibin_yval = ibin / GetNbinX();
    IsValidIbinY(ibin_yval);
    return ibin_yval;
}

long HistInfo2d::GetIbinXFromX(double xval) const
{
    IsValidRangeX(xval);
    long ibin_xval = static_cast<long>(
        floor((xval - GetLoX()) / GetBinWidthX()) );
    return ibin_xval;
}

long HistInfo2d::GetIbinYFromY(double yval) const
{
    IsValidRangeY(yval);
    long ibin_yval = static_cast<long>(
        floor((yval - GetLoY()) / GetBinWidthY()) );
    return ibin_yval;
}
   
long HistInfo2d::GetIbinFromXY(double xval, double yval) const
{
    IsValidRangeX(xval);
    IsValidRangeY(yval);
    long ibin_xval = GetIbinXFromX(xval);
    long ibin_yval = GetIbinYFromY(yval);
    long ibin = GetIbin(ibin_xval, ibin_yval);
    return ibin;
}
    
double HistInfo2d::GetBinCenterXFromIbinX(long ibin_xval) const
{
    IsValidIbinX(ibin_xval);
    double bin_center = GetLoX() + (ibin_xval + 0.5) * GetBinWidthX();
    return bin_center;
}

double HistInfo2d::GetBinCenterYFromIbinY(long ibin_yval) const
{
    IsValidIbinY(ibin_yval);
    double bin_center = GetLoY() + (ibin_yval + 0.5) * GetBinWidthY();
    return bin_center;
}
    
double HistInfo2d::GetBinCenterXFromIbin(long ibin) const
{
    long ibin_xval = GetIbinX(ibin);
    IsValidIbinX(ibin_xval);
    double bin_center = GetBinCenterXFromIbinX(ibin_xval);
    return bin_center;
}

double HistInfo2d::GetBinCenterYFromIbin(long ibin) const
{
    long ibin_yval = GetIbinY(ibin);
    IsValidIbinY(ibin_yval);
    double bin_center = GetBinCenterYFromIbinY(ibin_yval);
    return bin_center;
}
    
void HistInfo2d::GetBinCenterXYFromIbin(long ibin,
                                        double* const xval_ptr,
                                        double* const yval_ptr) const
{
    double bin_center_xval = GetBinCenterXFromIbin(ibin);
    double bin_center_yval = GetBinCenterYFromIbin(ibin);
    *xval_ptr = bin_center_xval;
    *yval_ptr = bin_center_yval;
}
    
long HistInfo2d::GetIbinX_WithHalfBinShifted(double xval) const
{
    IsValidRangeX(xval);
    double xval_lo_half_bin_shifted = GetLoX() + 0.5 * GetBinWidthX();
    long ibin_xval = static_cast<long>(
        floor((xval - xval_lo_half_bin_shifted) / GetBinWidthX()) );
    return ibin_xval;
}
    
long HistInfo2d::GetIbinY_WithHalfBinShifted(double yval) const
{
    IsValidRangeY(yval);
    double yval_lo_half_bin_shifted = GetLoY() + 0.5 * GetBinWidthY();
    long ibin_yval = static_cast<long>(
        floor((yval - yval_lo_half_bin_shifted) / GetBinWidthY()) );
    return ibin_yval;
}    

void HistInfo2d::Print(FILE* fp) const
{
    fprintf(fp, "hist_info_x_:\n");
    GetHistInfoX()->Print(fp);
    fprintf(fp, "hist_info_y_:\n");
    GetHistInfoY()->Print(fp);
}

void HistInfo2d::IsValidIbinX(long ibin_xval) const
{
    GetHistInfoX()->IsValidIbin(ibin_xval);
}

void HistInfo2d::IsValidIbinY(long ibin_yval) const
{
    GetHistInfoY()->IsValidIbin(ibin_yval);
}

void HistInfo2d::IsValidRangeX(double xval) const
{
    GetHistInfoX()->IsValidRange(xval);
}

void HistInfo2d::IsValidRangeY(double yval) const
{
    GetHistInfoY()->IsValidRange(yval);
}

// private

void HistInfo2d::Null()
{
    if(NULL != hist_info_x_){ delete hist_info_x_; hist_info_x_ = NULL;}
    if(NULL != hist_info_y_){ delete hist_info_y_; hist_info_y_ = NULL;}
}

