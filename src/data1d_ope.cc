#include "mshp_data1d_ope.h"

DataArray1d* const DataArray1dOpe::GenDa1dByLoad(string file, string format)
{
    DataArray1d* da1d = NULL;
    if("x" == format){
        da1d = new DataArrayNerr1d;
    } else if("x,xe" == format){
        da1d = new DataArraySerr1d;
    } else {
        MshpPrintErr("bad format");
        abort();
    }
    da1d->Load(file);
    return da1d;
}

void DataArray1dOpe::DelDa1dArr(DataArray1d** const da1d_arr, int narr)
{
    for(int iarr = 0; iarr < narr; iarr ++){
        delete da1d_arr[iarr];
    }
    delete [] da1d_arr;
}

int DataArray1dOpe::IsFormatSame(const DataArray1d* const data_array1,
                                 const DataArray1d* const data_array2)
{
    if(data_array1->GetNdata() != data_array2->GetNdata()){
        char msg[kLineSize];
        sprintf(msg, "ndata of data1 and data2 are different: %ld, %ld",
                data_array1->GetNdata(), data_array2->GetNdata());
        MshpPrintErr(msg);
        abort();
    }
    return 1;
}


int DataArray1dOpe::IsFormatSame(const DataArray1d* const* const data_array_arr,
                                 int ndata_array)
{
    if(ndata_array < 2){
        char msg[kLineSize];
        sprintf(msg, "nata_array(=%d) < 2", ndata_array);
        MshpPrintWarn(msg);
        MshpPrintWarn("skip check.");
        return 1;
    }
    for(int idata_array = 1; idata_array < ndata_array; idata_array ++){
        if(data_array_arr[idata_array]->GetNdata()
           != data_array_arr[0]->GetNdata()){
            char msg[kLineSize];
            sprintf(msg, "ndata of data[%d] and data[0] are different: %ld, %ld",
                    idata_array,
                    data_array_arr[idata_array]->GetNdata(),
                    data_array_arr[0]->GetNdata());
            MshpPrintErr(msg);
            abort();
        }
    }
    return 1;
}
