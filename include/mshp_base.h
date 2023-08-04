#ifndef MXSIM_HELPER_BASE_H_
#define MXSIM_HELPER_BASE_H_

#include "mshp_par.h"

#define MshpPrintErr(msg)       (printf("ERROR: %s: %u: %s(): %s\n", \
                             __FILE__, __LINE__, __func__, msg))
#define MshpPrintWarn(msg)      (printf("WARNING: %s: %u: %s(): %s\n", \
                             __FILE__, __LINE__, __func__, msg))
#define MshpPrintInfo(msg)      (printf("INFO: %s: %u: %s(): %s\n", \
                             __FILE__, __LINE__, __func__, msg))
#define MshpPrintErrClass(msg)  (printf("ERROR: %s: %u: %s::%s():%s: %s\n", \
                             __FILE__, __LINE__, GetClassName().c_str(), \
                             __func__, GetTitle().c_str(), msg))
#define MshpPrintWarnClass(msg) (printf("WARNING: %s: %u: %s::%s():%s: %s\n", \
                             __FILE__, __LINE__, GetClassName().c_str(), \
                             __func__, GetTitle().c_str(), msg))
#define MshpPrintInfoClass(msg) (printf("INFO: %s: %u: %s::%s():%s: %s\n", \
                             __FILE__, __LINE__, GetClassName().c_str(), \
                             __func__, GetTitle().c_str(), msg))
#define MshpPrintErrVFunc       (MshpPrintErr("Wrong virtual function call."))

#include <string.h>
#include <typeinfo>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>

using std::vector;
using std::map;
using std::multimap;
using std::make_pair;
using std::pair;
using std::type_info;
using std::istringstream;
using std::stringstream;

#include <getopt.h>

// see effective C++ section 6
class Uncopyable{
protected:
    Uncopyable(){}
    ~Uncopyable(){}
private:
    Uncopyable(const Uncopyable &);
    Uncopyable& operator=(const Uncopyable &);
};

class MshpObject: private Uncopyable{
public:
    MshpObject(string class_name, string title) :
        class_name_(class_name),
        title_(title) {}
    virtual ~MshpObject() {
        NullMshpObject();
    }

    virtual MshpObject* const Clone() const = 0;
    
    string GetClassName() const {return class_name_;};
    string GetTitle() const {return title_;};

    void SetTitle(string title) {title_ = title;};
    // There is no SetClassName function, because
    // class_name_ should be set at the initialization.

protected:
    void CopyTitle(const MshpObject* const org);
    
private:
    string class_name_;  
    string title_;

    void NullMshpObject();
};

class MshpArgBase: private Uncopyable{
public:
    MshpArgBase() {}
    virtual ~MshpArgBase() {}
    
    virtual void Init(int argc, char* argv[]) = 0;
    virtual void Print(FILE* fp) const = 0;

private:
    virtual void Null() = 0;
    virtual void SetOption(int argc, char* argv[],
			   option* long_options) = 0;
    virtual void Usage(FILE* fp) const = 0;
};

namespace MshpBase
{
    void IsValidArray(long narr, const int* const val_arr,
                      string err_msg = "");
    void IsValidArray(long narr, const double* const val_arr,
                      string err_msg = "");

    // vector --> arrray
    void GenArray(vector<double> vec,
                  long* narr_ptr,
                  double** val_arr_ptr);
    double* GenArray(vector<double> vec);
    void DelArray(double* val_arr);
}

#endif // MXSIM_HELPER_BASE_H_
