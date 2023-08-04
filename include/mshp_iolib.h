#ifndef MXSIM_HELPER_IOLIB_H_
#define MXSIM_HELPER_IOLIB_H_

#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <cstdarg>

#include <iostream>
#include <fstream>
#include <sstream>

using std::istringstream;
using std::ifstream;
using std::stringstream;

#include "mshp_str.h"

namespace MshpIolib
{
    int GenReadFile(string file,
                    double** const valx_arr_ptr,
                    long* const nline_ptr);

    int GenReadFile(string file,
                    double** const valx1_arr_ptr,
                    double** const valx2_arr_ptr,
                    long* const nline_ptr);

    int GenReadFile(string file,
                    double** const valx1_arr_ptr,
                    double** const valx2_arr_ptr,
                    double** const valx3_arr_ptr,
                    long* const nline_ptr);

    int GenReadFile(string file,
                    string** const lines_ptr,
                    long* const nline_ptr);
    
    int GenReadFileSkipComment(string file,
                               string** const lines_ptr,
                               long* const nline_ptr);

    int GenReadFileComment(string file,
                           string** const lines_ptr,
                           long* const nline_ptr);

    int GenRowsByReadFileSkipComment(string file,
                                     vector<long> sel_row_list_vec,
                                     string** const lines_ptr,
                                     long* const nline_ptr);

    void DelReadFile(double* val_arr);
    void DelReadFile(string* line_arr);

    // read file containing one row
    int GenReadFileOfHeadLine(string file,
                              string** const str_arr_ptr,
                              int* const nstr_ptr,
                              const char* const delim = " \t");

    int TestFileExist(string fname);

    int Printf2(FILE* fp_log, const char* const format, ...);

}  // namespace MshpIolib

#endif // MXSIM_HELPER_IOLIB_H_
