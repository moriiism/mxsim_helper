#ifndef MXSIM_HELPER_HIST2D_H_
#define MXSIM_HELPER_HIST2D_H_

#include "mshp_data1d.h"
#include "mshp_hist_info.h"
#include "mshp_func.h"
#include "mshp_hist1d.h"

class HistDataNerr2d;
class HistDataSerr2d;

class HistData2d : public MshpObject{
public:
    HistData2d(string class_name, string title) :
        MshpObject(class_name, title),
        hi2d_(NULL),
        oval_arr_(NULL) {}
    virtual ~HistData2d() {}
   
    virtual void Init(long nbin_xval, double xval_lo, double xval_up,
                      long nbin_yval, double yval_lo, double yval_up) = 0;
    virtual void Init(const HistInfo2d* const hist_info) = 0;
    void SetOvalArr(const DataArray1d* const oval_arr);
    void SetOvalArr(long ndata, const double* const val);
    void SetOvalArr(vector<double> val);    
    virtual void SetOvalSerrArr(long ndata, const double* const val_serr)
        {MshpPrintErrVFunc; abort();};
    virtual void SetOvalSerrArr(vector<double> val_serr)
        {MshpPrintErrVFunc; abort();};

    void SetOvalElm(long ibin_xval, long ibin_yval, double oval);
    virtual void SetOvalSerrElm(long ibin_xval, long ibin_yval, double oval_serr)
        {MshpPrintErrVFunc; abort();};

    void Fill(double xval, double yval);
    void Fill(double xval, double yval, double weight);
    void FillByLarger(double xval, double yval, double oval);
    virtual void FillByLarger(double xval, double yval,
                              double oval,
                              double oval_serr)
        {MshpPrintErrVFunc; abort();};
    
    void FillBySmaller(double xval, double yval, double oval);
    virtual void FillBySmaller(double xval, double yval,
                               double oval,
                               double oval_serr)
        {MshpPrintErrVFunc; abort();};

    void SetConst(double constant);
    
    virtual void SetOvalErrArrByPoissonErr()
        {MshpPrintErrVFunc; abort();};

    // Set by Func
    void SetByFunc(const MshpFunc* const func, const double* const par);

    void Copy(const HistData2d* const org);
    // virtual void Load(string file) = 0;

    const HistInfo2d* const GetHi2d() const {return hi2d_;};
    virtual const DataArray1d* const GetOvalArr() const = 0;

    long GetNbinX() const {return GetHi2d()->GetNbinX();};
    long GetNbinY() const {return GetHi2d()->GetNbinY();};
    long GetNbin()  const {return GetHi2d()->GetNbin();};
    double GetXvalLo() const {return GetHi2d()->GetLoX();};
    double GetXvalUp() const {return GetHi2d()->GetUpX();};
    double GetYvalLo() const {return GetHi2d()->GetLoY();};
    double GetYvalUp() const {return GetHi2d()->GetUpY();};
    double GetXvalMd() const {return GetHi2d()->GetMdX();};
    double GetYvalMd() const {return GetHi2d()->GetMdY();};
    double GetXvalFullWidth() const {return GetHi2d()->GetFullWidthX();};
    double GetYvalFullWidth() const {return GetHi2d()->GetFullWidthY();};
    double GetBinWidthX() const {return GetHi2d()->GetBinWidthX();};
    double GetBinWidthY() const {return GetHi2d()->GetBinWidthY();};
    double GetBinArea() const {return GetHi2d()->GetBinArea();};
    double GetFullArea() const {return GetHi2d()->GetFullArea();};

    // get element
    double GetOvalElm(long ibin_xval, long ibin_yval) const;
    virtual double GetOvalSerrElm(long ibin_xval, long ibin_yval) const
        {MshpPrintErrVFunc; abort();};    
    
    double GetOvalElmAtXY(double xval, double yval) const;
    virtual double GetOvalSerrElmAtXY(double xval, double yval) const
        {MshpPrintErrVFunc; abort();};

    double GetXvalAtOvalMin() const;
    double GetXvalAtOvalMax() const;
    double GetYvalAtOvalMin() const;
    double GetYvalAtOvalMax() const;

    //
    // gen xval_arr, yval_arr, oval_arr
    //
    // By using GenXYvalArr() and GenOvalArr(),
    // orders of values in xval_arr[ibin], yval_arr[ibin], and oval_arr[ibin]
    // are the same, following ibin.
    //
    void GenXYvalArr(double** const xval_arr_ptr,
                     double** const yval_arr_ptr,
                     long* const nbin_ptr) const;
    void GenXYvalSerrArr(double** const xval_serr_arr_ptr,
                         double** const yval_serr_arr_ptr,
                         long* const nbin_ptr) const;
    void GenOvalArr(double** const oval_arr_ptr,
                    long* const nbin_ptr) const;
    virtual void GenOvalSerrArr(double** const oval_serr_arr_ptr,
                                long* const nbin_ptr) const
        {MshpPrintErrVFunc; abort();};

    double GetOvalIntPolLin(double xval, double yval) const;
    
    //
    // output
    //

    // format:
    //   x,y,z
    //   x,y,z,ze
    //   x,xe,y,ye,z,ze
    //   x,xe,y,ye,z
    //   x,y,z,ze+,ze-
    //   x,xe,y,ye,z,ze+,ze-
    //   x,xe+,xe-,y,ye+,ye-,z,ze+,ze-
    void Save(string outfile, string format,
              double offset_xval = 0.0,
              double offset_yval = 0.0,
              double offset_oval = 0.0) const;
    void SaveData(string outfile, string format,
                  double offset_xval = 0.0,
                  double offset_yval = 0.0,
                  double offset_oval = 0.0) const;
    void PrintInfo(FILE* fp) const;    
    virtual void PrintData(FILE* fp, string format,
                           double offset_xval,
                           double offset_yval,
                           double offset_oval) const = 0;

    // poisson error
    virtual void FillRandom(const MshpFunc* const func,
                            const double* const func_par,
                            int rand_seed)
        {MshpPrintErrVFunc; abort();};

    // gaussian error
    virtual void FillRandom(const MshpFunc* const func,
                            const double* const func_par,
                            const MshpFunc* const func_sigma,
                            const double* const func_par_sigma,
                            int rand_seed)
        {MshpPrintErrVFunc; abort();};    

    // poisson error
    virtual void FillRandom(const HistData2d* const hist_data,
                            int rand_seed)
        {MshpPrintErrVFunc; abort();};

    // generate events from a probability distribution
    void GenRandomEvtFromProbDist(int nevt,
                                  int rand_seed,
                                  double** xval_arr_ptr,
                                  double** yval_arr_ptr) const;
    
    virtual HistData2d* GenSubHist(long ibinx_st, long ibinx_ed,
                                   long ibiny_st, long ibiny_ed) const = 0;
    
    double GetOffsetXFromTag(string offset_tag) const;
    double GetOffsetYFromTag(string offset_tag) const;
    double GetOffsetOFromTag(string offset_tag) const;

    //
    // static
    //
    static void ReadInfo(string file, 
                         long* nbin_xval_ptr,
                         double* xval_lo_ptr,
                         double* xval_up_ptr,
                         long* nbin_yval_ptr,
                         double* yval_lo_ptr,
                         double* yval_up_ptr,
                         string* format_ptr);

protected:
    void NullHistData2d();
    void NewOvalArrAsDataArrayNerr1d();
    void NewOvalArrAsDataArraySerr1d();
    void NewHi2d();
    HistInfo2d* GetHi2dNonConst() const {return hi2d_;};
    DataArray1d* GetOvalArrNonConst() const {return oval_arr_;};
    void IsHi2dNotNull() const;
    void IsOvalArrNotNull() const;
    void IsValidIbinX(long ibin_xval) const;
    void IsValidIbinY(long ibin_yval) const;
    void IsValidRangeX(double xval) const;
    void IsValidRangeY(double yval) const;
    
private:
    // ibin_xval_ = 0, 1, ..., nbin_xval_
    // ibin_yval_ = 0, 1, ..., nbin_yval_
    // ibin = ibin_xval_ + nbin_xval_ * ibin_yval_
    
    HistInfo2d* hi2d_;
    DataArray1d* oval_arr_;
};

#endif // MXSIM_HELPER_HIST2D_H_

