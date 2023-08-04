#ifndef MXSIM_HELPER_HIST1D_SERR_H_
#define MXSIM_HELPER_HIST1D_SERR_H_

#include "mshp_hist1d.h"

class HistDataSerr1d : public HistData1d{
public:
    explicit HistDataSerr1d(string title = "") :
        HistData1d("HistDataSerr1d", title) {}
    ~HistDataSerr1d() {
        NullHistData1d();
    }

    void Init(long nbin_xval,
              double xval_lo,
              double xval_up);
    void Init(const HistInfo1d* const hist_info);
    void SetOvalSerrArr(long ndata, const double* const val_serr);
    void SetOvalSerrArr(vector<double> val_serr);
    void SetOvalSerrElm(long ibin, double oval_serr);
    void FillByLarger(double xval,
                      double oval,
                      double oval_serr);
    void FillBySmaller(double xval,
                       double oval,
                       double oval_serr);
    void SetOvalErrArrByPoissonErr();
    HistDataSerr1d* const Clone() const;
    void Load(string file);

    const DataArraySerr1d* const GetOvalArr() const;
    double GetOvalSerrElm(long ibin) const;
    double GetOvalSerrElmAtX(double xval) const;

    void PrintData(FILE* fp, string format,
                   double offset_xval,
                   double offset_oval) const;

    HistDataSerr1d* const GenHd1MaxInBin(long nbin_new) const;

    // poisson error
    void FillRandom(const MshpFunc* const func,
                    const double* const func_par,
                    int rand_seed);
    void FillRandom(const MshpFunc* const func,
                    const double* const func_par,
                    const MshpFunc* const func_sigma,
                    const double* const func_par_sigma,
                    int rand_seed);
    void FillRandom(const HistData1d* const hist_data,
                    int rand_seed);
    HistDataSerr1d* GenSubHist(long ibinx_st, long ibinx_ed) const;
};

#endif // MXSIM_HELPER_HIST1D_SERR_H_

