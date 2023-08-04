#ifndef MXSIM_HELPER_HIST2D_SERR_H_
#define MXSIM_HELPER_HIST2D_SERR_H_

#include "mshp_hist1d_serr.h"
#include "mshp_hist2d.h"

class HistDataSerr2d : public HistData2d{
public:
    explicit HistDataSerr2d(string title = "") :
        HistData2d("HistDataSerr2d", title) {}
    ~HistDataSerr2d() {
        NullHistData2d();
    }

    void Init(long nbin_xval, double xval_lo, double xval_up,
              long nbin_yval, double yval_lo, double yval_up);
    void Init(const HistInfo2d* const hist_info);
    void SetOvalSerrArr(long ndata, const double* const val_serr);
    void SetOvalSerrArr(vector<double> val_serr);
    void SetOvalSerrElm(long ibin_xval, long ibin_yval, double oval_serr);

    void FillByLarger(double xval, double yval,
                      double oval,
                      double oval_serr);
    void FillBySmaller(double xval, double yval,
                       double oval,
                       double oval_serr);
    void SetOvalErrArrByPoissonErr();
    HistDataSerr2d* const Clone() const;
    // void Load(string file);

    const DataArraySerr1d* const GetOvalArr() const;
    double GetOvalSerrElm(long ibin_xval, long ibin_yval) const;
    double GetOvalSerrElmAtXY(double xval, double yval) const;
    void GenOvalSerrArr(double** const oval_serr_arr_ptr,
                        long* const nbin_ptr) const;

    //
    // output
    //
    void PrintData(FILE* fp, string format,
                   double offset_xval,
                   double offset_yval,
                   double offset_oval) const;
    // poisson error
    void FillRandom(const MshpFunc* const func,
                    const double* const func_par,
                    int rand_seed);

    // gaussian error
    void FillRandom(const MshpFunc* const func,
                    const double* const func_par,
                    const MshpFunc* const func_sigma,
                    const double* const func_par_sigma,
                    int rand_seed);

    // poisson error
    void FillRandom(const HistData2d* const hist_data,
                    int rand_seed);

    HistDataSerr2d* GenSubHist(long ibinx_st, long ibinx_ed,
                               long ibiny_st, long ibiny_ed) const;
};

#endif // MXSIM_HELPER_HIST2D_SERR_H_
