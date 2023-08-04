#ifndef MXSIM_HELPER_HIST1D_H_
#define MXSIM_HELPER_HIST1D_H_

#include "mshp_rand.h"
#include "mshp_data1d_nerr.h"
#include "mshp_data1d_serr.h"
#include "mshp_hist_info.h"
#include "mshp_func.h"

class HistDataNerr1d;
class HistDataSerr1d;

class HistData1d : public MshpObject{
public:
    HistData1d(string class_name, string title) :
        MshpObject(class_name, title),
        hi1d_(NULL),
        oval_arr_(NULL) {}
    virtual ~HistData1d() {}
   
    virtual void Init(long nbin_xval,
                      double xval_lo,
                      double xval_up) = 0;
    virtual void Init(const HistInfo1d* const hist_info) = 0;
    void SetOvalArr(const DataArray1d* const oval_arr);
    void SetOvalArr(long ndata, const double* const val);
    void SetOvalArr(vector<double> val);    
    virtual void SetOvalSerrArr(long ndata, const double* const val_serr)
        {MshpPrintErrVFunc; abort();};
    virtual void SetOvalSerrArr(vector<double> val_serr)
        {MshpPrintErrVFunc; abort();};
    
    void SetOvalElm(long ibin, double oval);
    virtual void SetOvalSerrElm(long ibin, double oval_serr)
        {MshpPrintErrVFunc; abort();};

    void Fill(double xval);
    void Fill(double xval, double weight);
    void FillByLarger(double xval, double oval);
    virtual void FillByLarger(double xval,
                              double oval,
                              double oval_serr)
        {MshpPrintErrVFunc; abort();};
    
    void FillBySmaller(double xval, double oval);
    virtual void FillBySmaller(double xval,
                               double oval,
                               double oval_serr)
        {MshpPrintErrVFunc; abort();};
    
    void SetConst(double constant);

    virtual void SetOvalErrArrByPoissonErr()
        {MshpPrintErrVFunc; abort();};
    
    void SetByFunc(const MshpFunc* const func, const double* const par);

    void Copy(const HistData1d* const org);
    virtual void Load(string file) = 0;

    //
    // const functions
    //

    // get
    const HistInfo1d* const GetHi1d() const {return hi1d_;};
    virtual const DataArray1d* const GetOvalArr() const = 0;
    
    long GetNbinX() const {return GetHi1d()->GetNbin();};
    double GetXvalLo() const {return GetHi1d()->GetLo();};
    double GetXvalUp() const {return GetHi1d()->GetUp();};
    double GetXvalMd() const {return GetHi1d()->GetMd();};
    double GetXvalFullWidth() const {return GetHi1d()->GetFullWidth();};
    double GetXvalBinWidth() const {return GetHi1d()->GetBinWidth();};

    // get element
    double GetOvalElm(long ibin) const;
    double GetOvalElmAtX(double xval) const;
    virtual double GetOvalSerrElm(long ibin) const
        {MshpPrintErrVFunc; abort();};
    virtual double GetOvalSerrElmAtX(double xval) const
        {MshpPrintErrVFunc; abort();};
    
    double GetXvalAtOvalMin() const;
    double GetXvalAtOvalMax() const;

    void GenXvalArr(double** const xval_arr_ptr,
                    long* const nbin_ptr) const;
    void GenXvalSerrArr(double** const xval_serr_arr_ptr,
                        long* const nbin_ptr) const;
    void GenOvalArr(double** const oval_arr_ptr,
                    long* const nbin_ptr) const;
    virtual void GenOvalSerrArr(double** const oval_serr_arr_ptr,
                                long* const nbin_ptr) const
        {MshpPrintErrVFunc; abort();};

    long GetIbin(double xval) const;
    double GetBinCenter(long ibin) const;
    double GetBinLo(long ibin) const;
    double GetBinUp(long ibin) const;
    long GetIbin_WithHalfBinShifted(double val) const;
    double GetOvalIntPolLin(double xval) const;
    double GetIntegral(double xval_lo, double xval_up) const;

    
    //
    // output
    //
    void Save(string outfile, string format,
              double offset_xval = 0.0,
              double offset_oval = 0.0) const;
    void SaveData(string outfile, string format,
                  double offset_xval = 0.0,
                  double offset_oval = 0.0) const;
    void PrintInfo(FILE* fp) const;
    virtual void PrintData(FILE* fp, string format,
                           double offset_xval,
                           double offset_oval) const = 0;

    virtual HistData1d* const GenHd1MaxInBin(long nbin_new) const = 0;

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
    virtual void FillRandom(const HistData1d* const hist_data,
                            int rand_seed)
        {MshpPrintErrVFunc; abort();};
    

    // generate events from histogram with poisson statistic
    DataArrayNerr1d* const GenRandomEvt(int rand_seed) const;

    // generate events from a probability distribution
    void GenRandomEvtFromProbDist(int nevt,
                                  int rand_seed,
                                  double** xval_arr_ptr) const;
    
    virtual HistData1d* GenSubHist(long ibinx_st, long ibinx_ed) const = 0;

    // offset_tag = "st", "md", "ed", "no"
    double GetOffsetXFromTag(string offset_tag) const;
    double GetOffsetOFromTag(string offset_tag) const;

    //
    // static 
    //
    static void ReadInfo(string file, 
                         long* nbin_xval_ptr,
                         double* xval_lo_ptr,
                         double* xval_up_ptr,
                         string* format_ptr);

protected:
    void NullHistData1d();
    void NewOvalArrAsDataArrayNerr1d();
    void NewOvalArrAsDataArraySerr1d();
    void NewHi1d();
    HistInfo1d* GetHi1dNonConst() const {return hi1d_;};
    DataArray1d* GetOvalArrNonConst() const {return oval_arr_;};
    void IsHi1dNotNull() const;
    void IsOvalArrNotNull() const;
    void IsValidIbin(long ibin) const;
    void IsValidRange(double val) const;
    
private:
    HistInfo1d* hi1d_;
    DataArray1d* oval_arr_;
};

#endif // MXSIM_HELPER_HIST1D_H_
