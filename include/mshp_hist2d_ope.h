#ifndef MXSIM_HELPER_HIST2D_OPE_H_
#define MXSIM_HELPER_HIST2D_OPE_H_

#include "mshp_data1d_ope.h"
#include "mshp_hist1d_nerr.h"
#include "mshp_hist1d_serr.h"
#include "mshp_hist2d_nerr.h"
#include "mshp_hist2d_serr.h"

namespace HistData2dOpe
{
    HistData2d* const GenHd2dByLoad(string file);

    DataArray1d** const GenDa1dArrNerr(
        const HistData2d* const* const hd2d_arr,
        int narr);
    DataArray1d** const GenDa1dArrSerr(
        const HistData2d* const* const hd2d_arr,
        int narr);
    void DelHd2dArr(HistData2d** const hd2d_arr, int narr);

    int IsFormatSame(const HistData2d* const data1,
                     const HistData2d* const data2);
    int IsFormatSame(const HistData2d* const* const data_arr,
                     int nhist);

    // calc_mode : "add", "integral", "amean", "min", "max",  "stddev"
    // error_mode: gauss, poisson, zero    
    void GetProjectX(const HistData2d* const in,
                     long ibin_ylo, long ibin_yup,
                     string calc_mode,
                     HistDataNerr1d* const out);
    void GetProjectX(const HistData2d* const in,
                     long ibin_ylo, long ibin_yup,
                     string calc_mode, string error_mode,
                     HistDataSerr1d* const out);

    void GetProjectY(const HistData2d* const in,
                     long ibin_xlo, long ibin_xup,
                     string calc_mode,
                     HistDataNerr1d* const out);
    void GetProjectY(const HistData2d* const in,
                     long ibin_xlo, long ibin_xup,
                     string calc_mode, string error_mode,
                     HistDataSerr1d* const out);

    // calc_mode: "add", "integral", "amean", "min", "max", "stddev"
    // error_mode: gauss, poisson, zero    
    void GetProject(long ndata,
                    const double* const array,
                    string calc_mode, double bin_width,
                    double* const val_proj_ptr);
    void GetProject(long ndata,
                    const double* const array,
                    const double* const array_err,
                    string calc_mode, string error_mode,
                    double bin_width,
                    double* const val_proj_ptr,
                    double* const val_proj_err_ptr);
    
} // namespace HistData2dOpe


#endif // MXSIM_HELPER_HIST2D_OPE_H_
