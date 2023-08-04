#include "mshp_data1d_ope.h"
#include "mshp_hist1d_ope.h"

DataArray1d** const HistData1dOpe::GenDa1dArrNerr(
    const HistData1d* const* const hd1d_arr,
    int narr)
{
    DataArray1d** da1d_arr = new DataArray1d* [narr];
    for(int iarr = 0; iarr < narr; iarr ++){
        da1d_arr[iarr] = new DataArrayNerr1d;
        da1d_arr[iarr]->Copy(hd1d_arr[iarr]->GetOvalArr());
    }
    return da1d_arr;
}

DataArray1d** const HistData1dOpe::GenDa1dArrSerr(
    const HistData1d* const* const hd1d_arr,
    int narr)
{
    DataArray1d** da1d_arr = new DataArray1d* [narr];
    for(int iarr = 0; iarr < narr; iarr ++){
        da1d_arr[iarr] = new DataArraySerr1d;
        da1d_arr[iarr]->Copy(hd1d_arr[iarr]->GetOvalArr());
    }
    return da1d_arr;
}

void HistData1dOpe::DelHd1dArr(HistData1d** const hd1d_arr, int narr)
{
    for(int iarr = 0; iarr < narr; iarr ++){
        delete hd1d_arr[iarr];
    }
    delete [] hd1d_arr;
}

int HistData1dOpe::IsFormatSame(const HistData1d* const data1,
                                const HistData1d* const data2)
{
    if(data1->GetNbinX() != data2->GetNbinX() ||
       fabs(data1->GetXvalLo() - data2->GetXvalLo()) > DBL_EPSILON ||
       fabs(data1->GetXvalUp() - data2->GetXvalUp()) > DBL_EPSILON ){
        MshpPrintErr("format of data1 and data2 are diffenret.");
        char msg[kLineSize];
        sprintf(msg, "data1: (GetNbinX(), GetXvalLo(), GetXvalUp())"
                "= (%ld, %e, %e)",
                data1->GetNbinX(),
                data1->GetXvalLo(),
                data1->GetXvalUp());
        MshpPrintErr(msg);
        sprintf(msg, "data2: (GetNbinX(), GetXvalLo(), GetXvalUp())"
                "= (%ld, %e, %e)",
                data2->GetNbinX(),
                data2->GetXvalLo(),
                data2->GetXvalUp());
        MshpPrintErr(msg);
        abort();
    }
    return 1;
}

int HistData1dOpe::IsFormatSame(const HistData1d* const* const data_arr,
                                int nhist)
{
    if(nhist < 2){
        char msg[kLineSize];
        sprintf(msg, "nhist(=%d) < 2\n", nhist);
        MshpPrintWarn(msg);
        MshpPrintWarn("skip check");
        return 0;
    }
    for(int ihist = 1; ihist < nhist; ihist++){
        if(data_arr[0]->GetNbinX()  != data_arr[ihist]->GetNbinX()  ||
           fabs(data_arr[0]->GetXvalLo() - data_arr[ihist]->GetXvalLo())
           > DBL_EPSILON ||
           fabs(data_arr[0]->GetXvalUp() - data_arr[ihist]->GetXvalUp())
           > DBL_EPSILON ){
            char msg[kLineSize];
            sprintf(msg, "format of data_arr[0] and data_arr[%d] are diffenret",
                    ihist);
            MshpPrintErr(msg);
            sprintf(msg, "data_arr[0]: (GetNbinX(), GetXvalLo(), GetXvalUp())"
                    "= (%ld, %e, %e)",
                    data_arr[0]->GetNbinX(),
                    data_arr[0]->GetXvalLo(),
                    data_arr[0]->GetXvalUp());
            MshpPrintErr(msg);            
            sprintf(msg, "data_arr[%d]: (GetNbinX(), GetXvalLo(), GetXvalUp())"
                    "= (%ld, %e, %e)",
                    ihist,
                    data_arr[ihist]->GetNbinX(),
                    data_arr[ihist]->GetXvalLo(),
                    data_arr[ihist]->GetXvalUp());
            MshpPrintErr(msg);            
            sprintf(
                msg,
                "data_arr[0]->GetXvalLo() - data_arr[%d]->GetXvalLo() = %e\n",
                ihist,
                fabs(data_arr[0]->GetXvalLo()
                     - data_arr[ihist]->GetXvalLo()));
            MshpPrintErr(msg);            
            sprintf(
                msg,
                "data_arr[0]->GetXvalUp() - data_arr[%d]->GetXvalUp() = %e\n",
                ihist,
                fabs(data_arr[0]->GetXvalUp() - data_arr[ihist]->GetXvalUp()));
            abort();
        }
    }
    return 1;
}
