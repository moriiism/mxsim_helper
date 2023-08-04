#ifndef MXSIM_HELPER_HIST1D_OPE_H_
#define MXSIM_HELPER_HIST1D_OPE_H_

#include "mshp_data1d_ope.h"
#include "mshp_hist1d_nerr.h"
#include "mshp_hist1d_serr.h"

namespace HistData1dOpe
{
    HistData1d* const GenHd1dByLoad(string file);

    DataArray1d** const GenDa1dArrNerr(const HistData1d* const* const hd1d_arr,
                                       int narr);
    DataArray1d** const GenDa1dArrSerr(const HistData1d* const* const hd1d_arr,
                                       int narr);
    void DelHd1dArr(HistData1d** const hd1d_arr, int narr);

    int IsFormatSame(const HistData1d* const data1,
                     const HistData1d* const data2);
    int IsFormatSame(const HistData1d* const* const data_arr,
                     int nhist);
    
} // namespace HistData1dOpe

#endif // MXSIM_HELPER_HIST1D_OPE_H_
