#ifndef MXSIM_HELPER_DATA1D_SERR_H_
#define MXSIM_HELPER_DATA1D_SERR_H_

#include "mshp_data1d.h"

class DataArraySerr1d : public DataArray1d{
public:
    explicit DataArraySerr1d(string title = "") :
        DataArray1d("DataArraySerr1d", title),
        val_serr_(NULL) {}
    ~DataArraySerr1d() {
        NullDataArray1d();
        NullDataArraySerr1d();
    }

    void Init(long ndata);
    void SetValSerr(long ndata,
                    const double* const val_serr);
    void SetValSerr(vector<double> val_serr);
    void SetValSerrElm(long idata, double val_serr);
  
    void Fill(long idata);
    void Fill(long idata, double weight);

    // poisson error
    void FillByLarger(long idata, double val);
    void FillByLarger(long idata,
                      double val,
                      double val_serr);
    void FillBySmaller(long idata, double val);
    void FillBySmaller(long idata,
                       double val,
                       double val_serr);

    void SetConst(double constant);
    void SetValErrByPoissonErr();
    DataArraySerr1d* const Clone() const;
    void Load(string file);
    void Sort();

    //
    // const functions
    //
    const double* const GetValSerr() const {return val_serr_;};
    double GetValSerrElm(long idata) const;
    double GetValAndErrMin() const;
    double GetValAndErrMax() const;
    void PrintData(FILE* fp, int mode,
                   double offset_val) const;
    double GetOffsetValFromTag(string offset_tag) const;
    
private:
    double* val_serr_;  // >= 0
    
    void NullDataArraySerr1d();
    void InitDataArraySerr1d(long ndata);
    void IsValSerrNotNull() const;
};


#endif // MXSIM_HELPER_DATA1D_SERR_H_

