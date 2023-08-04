#ifndef MXSIM_HELPER_DATA1D_NERR_H_
#define MXSIM_HELPER_DATA1D_NERR_H_

#include "mshp_data1d.h"

class DataArrayNerr1d : public DataArray1d{
public:
    explicit DataArrayNerr1d(string title = "") :
        DataArray1d("DataArrayNerr1d", title) {}
    ~DataArrayNerr1d() {
        NullDataArray1d();
    }

    void Init(long ndata);
    void Fill(long idata);
    void Fill(long idata, double weight);
    void FillByLarger(long idata, double val);
    void FillBySmaller(long idata, double val);
    void SetConst(double constant);
    DataArrayNerr1d* const Clone() const;
    void Load(string file);
    void Sort();

    //
    // const functions
    //
    double GetValSerrElm(long idata) const {return 0.0;};
    
    double GetValAndErrMin() const;
    double GetValAndErrMax() const;
    
    void PrintData(FILE* fp, int mode,
                   double offset_val) const;

    double GetOffsetValFromTag(string offset_tag) const;
};


#endif // MXSIM_HELPER_DATA1D_NERR_H_

