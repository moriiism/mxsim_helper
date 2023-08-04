#ifndef MXSIM_HELPER_DATA1D_OPE_H_
#define MXSIM_HELPER_DATA1D_OPE_H_

#include "mshp_data1d_nerr.h"
#include "mshp_data1d_serr.h"

namespace DataArray1dOpe
{
    DataArray1d* const GenDa1dByLoad(string file, string format);

    void DelDa1dArr(DataArray1d** const da1d_arr, int narr);

    int IsFormatSame(const DataArray1d* const data_array1,
                     const DataArray1d* const data_array2);
    int IsFormatSame(const DataArray1d* const* const data_array_arr,
                     int ndata_array);
    
} // namespace DataArray1dOpe

#endif // MXSIM_HELPER_DATA1D_OPE_H_
