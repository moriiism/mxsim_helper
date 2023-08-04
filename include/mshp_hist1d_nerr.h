#ifndef MXSIM_HELPER_HIST1D_NERR_H_
#define MXSIM_HELPER_HIST1D_NERR_H_

#include "mshp_hist1d.h"

class HistDataNerr1d : public HistData1d{
public:
    explicit HistDataNerr1d(string title = "") :
        HistData1d("HistDataNerr1d", title) {}
    virtual ~HistDataNerr1d() {
        NullHistData1d();
    }

    void Init(long nbin_xval,
              double xval_lo,
              double xval_up);
    void Init(const HistInfo1d* const hist_info);
    HistDataNerr1d* const Clone() const;
    void Load(string file);
    const DataArrayNerr1d* const GetOvalArr() const;
    void PrintData(FILE* fp, string format,
                   double offset_xval,
                   double offset_oval) const;
    HistDataNerr1d* const GenHd1MaxInBin(long nbin_new) const;
    void FillRandom(const MshpFunc* const func,
                     const double* const func_par,
                     int rand_seed);
    void FillRandom(const HistData1d* const hist_data,
                    int rand_seed);
    HistDataNerr1d* GenSubHist(long ibinx_st, long ibinx_ed) const;
};

#endif // MXSIM_HELPER_HIST1D_NERR_H_
