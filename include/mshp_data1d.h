#ifndef MXSIM_HELPER_DATA1D_H_
#define MXSIM_HELPER_DATA1D_H_

#include "mshp_base.h"
#include "mshp_iolib.h"
#include "mshp_str.h"
#include "mshp_sort.h"
#include "mshp_math.h"

class DataArrayNerr1d;
class DataArraySerr1d;

class DataArray1d : public MshpObject{
public:
    DataArray1d(string class_name, string title) :
        MshpObject(class_name, title),
        ndata_(0),
        val_(NULL),
        flag_val_sorted_(0) {}
    virtual ~DataArray1d() {}

    // Init
    virtual void Init(long ndata) = 0;

    // Set
    void SetVal(long ndata, const double* const val);
    void SetVal(vector<double> val);
    void SetFlagValSorted(int flag_val_sorted)
        {flag_val_sorted_ = flag_val_sorted;};

    // DataArraySerr1d
    virtual void SetValSerr(long ndata,
                            const double* const val_serr)
        {MshpPrintErrVFunc; abort();};
    virtual void SetValSerr(vector<double> val_serr)
        {MshpPrintErrVFunc; abort();};

    // Set element
    void SetValElm(long idata, double val);
    virtual void SetValSerrElm(long idata, double val_serr)
        {MshpPrintErrVFunc; abort();};
    
    virtual void Fill(long idata) = 0;
    // add an event on the idata-bin of the data
    virtual void Fill(long idata, double weight) = 0;
    // add weight events on the idata-bin of the data

    // poisson error
    virtual void FillByLarger(long idata, double val) = 0;
    virtual void FillByLarger(long idata,
                              double val,
                              double val_serr)
        {MshpPrintErrVFunc; abort();};
    virtual void FillByLarger(long idata,
                              double val,
                              double val_terr_plus,
                              double val_terr_minus)
        {MshpPrintErrVFunc; abort();};

    virtual void FillBySmaller(long idata, double val) = 0;
    virtual void FillBySmaller(long idata,
                               double val,
                               double val_serr)
        {MshpPrintErrVFunc; abort();};
    virtual void FillBySmaller(long idata,
                               double val,
                               double val_terr_plus,
                               double val_terr_minus)
        {MshpPrintErrVFunc; abort();};
    
    virtual void SetConst(double constant) = 0;

    virtual void SetValErrByPoissonErr()
        {MshpPrintErrVFunc; abort();};
    
    void Copy(const DataArray1d* const org);
    virtual void Load(string file) = 0;

    // operation
    virtual void Sort() = 0;

    //
    // const functions
    //

    // get
    long GetNdata() const {return ndata_;};
    const double* const GetVal() const {return val_;};
    double GetValElm(long idata) const;
    int GetFlagValSorted() const {return flag_val_sorted_;};
    
    virtual const double* const GetValSerr() const
        {MshpPrintErrVFunc; abort(); return NULL;};
    virtual double GetValSerrElm(long idata) const = 0;

    // terr --> serr by average
    virtual double* const GenValSerr() const
        {MshpPrintErrVFunc; abort(); return NULL;};

    double GetValMin() const;
    double GetValMax() const;
    long GetLocValMin() const;
    long GetLocValMax() const;
    virtual double GetValAndErrMin() const = 0;
    virtual double GetValAndErrMax() const = 0;

    
    // output
    // mode: 0, 1, 2
    //    0: data
    //    1: index data
    //    2: data   1.0
    void Save(string outfile, int mode, double offset_val) const;
    void SaveData(string outfile, int mode, double offset_val) const;
    void PrintInfo(FILE* fp) const;
    virtual void PrintData(FILE* fp, int mode,
                           double offset_val) const = 0;

    // Is functions
    int IsAllOne() const;

    // offset_tag = "st", "md", "ed", "no", value
    double GetOffsetIndexFromTag(string offset_tag) const;
    virtual double GetOffsetValFromTag(string offset_tag) const = 0;

    //
    // static
    //
    static void ReadInfo(string file, int* flag_val_sorted_ptr);


protected:
    void NullDataArray1d();
    void InitDataArray1d(long ndata);
    void IsValNotNull() const;
    void IsValidRange(long idata) const;
    void IsValSerrPlus(double val_serr) const;
    
private:
    long ndata_;
    double* val_;
    int flag_val_sorted_; // -1: not sorted, 0: not checked, 1: sorted
};

#endif // MXSIM_HELPER_DATA1D_H_
