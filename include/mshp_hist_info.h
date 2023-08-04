#ifndef MXSIM_HELPER_HIST_INFO_H_
#define MXSIM_HELPER_HIST_INFO_H_

#include "mshp_iolib.h"

//
// format of hist_info file:
//   # nbin  lo  up  delta-bin  mode
//   50     -10   20   none  none
//   none   -10   20   1.0  floor
//

class HistInfo1d : public MshpObject{
public:
    explicit HistInfo1d(string title = "") :
        MshpObject("HistInfo1d", title),
        nbin_(0),
        lo_(0.0),
        up_(0.0) {}
    ~HistInfo1d() {
        Null();
    }

    void InitSetByNbin(double lo, double up, long nbin);
    void InitSetByWidth(double lo, double up, double bin_width, string mode);
    void InitSetByMidPoint(double md, double bin_width,
                           double half_width, string mode);
    void Load(string file);
    void Copy(const HistInfo1d* const org);
    HistInfo1d* const Clone() const;

    // const func
    long GetNbin() const {return nbin_;};
    double GetLo() const {return lo_;};
    double GetUp() const {return up_;};

    double GetMd() const;
    double GetMdLog() const;
    double GetBinWidth() const;
    double GetBinWidthLog(long ibin) const;
    double GetFullWidth() const {return GetUp() - GetLo();};

    long GetIbin(double val, string scale = "lin") const;
    double GetBinCenter(long ibin, string scale = "lin") const;
    double GetBinLo(long ibin, string scale = "lin") const;
    double GetBinUp(long ibin, string scale = "lin") const;


    
    long GetIbin_WithHalfBinShifted(double val) const;
    
    void GenValArr(double** const val_arr_ptr,
                    long* const nbin_ptr,
                    string scale = "lin") const;
    void GenValSerrArr(double** const val_serr_arr_ptr,
                       long* const nbin_ptr,
                       string scale = "lin") const;
    void GenValTerrArr(double** const val_terr_plus_arr_ptr,
                       double** const val_terr_minus_arr_ptr,
                       long* const nbin_ptr,
                       string scale = "lin") const;  
    
    // offset_tag = "st", "md", "ed", "no"
    double GetOffsetFromTag(string offset_tag) const;
    
    void Print(FILE* fp) const;

    void IsValidForLogScale() const;    
    void IsValidIbin(long ibin) const;
    void IsValidRange(double val) const;

    //
    // static
    //
    static void SetHistInfo(string line, HistInfo1d* const hist_info_out);
    
private:
    long nbin_;
    double lo_;
    double up_;

    void Null();
};


class HistInfo2d : public MshpObject{
public:
    explicit HistInfo2d(string title = "") :
        MshpObject("HistInfo2d", title),
        hist_info_x_(NULL),
        hist_info_y_(NULL) {}
    ~HistInfo2d(){
        Null();
    }

    void InitSetByNbin(double lo_x, double up_x, long nbin_x,
                       double lo_y, double up_y, long nbin_y);
    void InitSetByWidth(double lo_x, double up_x,
                        double bin_width_x, string mode_x,
                        double lo_y, double up_y,
                        double bin_width_y, string mode_y);
    void InitSetByMidPoint(double md_x, double bin_width_x,
                           double half_width_x, string mode_x,
                           double md_y, double bin_width_y,
                           double half_width_y, string mode_y);
    void Load(string file);
    void Copy(const HistInfo2d* const org);
    HistInfo2d* const Clone() const;

    // const func
    HistInfo1d* const GetHistInfoX() const {return hist_info_x_;};
    HistInfo1d* const GetHistInfoY() const {return hist_info_y_;};

    long GetNbinX() const {return GetHistInfoX()->GetNbin();};
    double GetLoX() const {return GetHistInfoX()->GetLo();};
    double GetUpX() const {return GetHistInfoX()->GetUp();};
    double GetMdX() const {return GetHistInfoX()->GetMd();};
    double GetBinWidthX() const {return GetHistInfoX()->GetBinWidth();};
    double GetFullWidthX() const {return GetHistInfoX()->GetFullWidth();};
    long GetNbinY() const {return GetHistInfoY()->GetNbin();};
    double GetLoY() const {return GetHistInfoY()->GetLo();};
    double GetUpY() const {return GetHistInfoY()->GetUp();};
    double GetMdY() const {return GetHistInfoY()->GetMd();};
    double GetBinWidthY() const {return GetHistInfoY()->GetBinWidth();};
    double GetFullWidthY() const {return GetHistInfoY()->GetFullWidth();};
    long GetNbin()  const {return GetNbinX() * GetNbinY();};
    double GetBinArea() const {return GetBinWidthX() * GetBinWidthY();};
    double GetFullArea() const {return GetFullWidthX() * GetFullWidthY();};

    long GetIbin(long ibin_xval, long ibin_yval) const;
    long GetIbinX(long ibin) const;
    long GetIbinY(long ibin) const;
    long GetIbinXFromX(double xval) const;
    long GetIbinYFromY(double yval) const;
    long GetIbinFromXY(double xval, double yval) const;
    double GetBinCenterXFromIbinX(long ibin_xval) const;
    double GetBinCenterYFromIbinY(long ibin_yval) const;
    double GetBinCenterXFromIbin(long ibin) const;
    double GetBinCenterYFromIbin(long ibin) const;
    void GetBinCenterXYFromIbin(long ibin,
                                double* const xval_ptr,
                                double* const yval_ptr) const;
    long GetIbinX_WithHalfBinShifted(double xval) const;
    long GetIbinY_WithHalfBinShifted(double yval) const;

    void Print(FILE* fp) const;

    void IsValidIbinX(long ibin_xval) const;
    void IsValidIbinY(long ibin_yval) const;
    void IsValidRangeX(double xval) const;
    void IsValidRangeY(double yval) const;
    
private:
    // ibin_xval_ = 0, 1, ..., nbin_xval_
    // ibin_yval_ = 0, 1, ..., nbin_yval_
    // ibin = ibin_xval_ + nbin_xval_ * ibin_yval_
    
    HistInfo1d* hist_info_x_;
    HistInfo1d* hist_info_y_;

    void Null();
};

#endif // MXSIM_HELPER_HIST_INFO_H_
