#include "mshp_str.h"
#include "mshp_iolib.h"
#include "mshp_hist1d_nerr.h"
//#include "mshp_qdp_tool.h"
//#include "mshp_func.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;


//class FuncTest : public MshpFunc{
//public:
//    explicit FuncTest(string title = "") :
//        MshpFunc("FuncTest", title)
//        {
//            SetNpar(3);
//            SetNdim(1);           
//        }
//    ~FuncTest() {
//        NullMshpFunc();
//    }
//
//    void Copy(const FuncTest* const org);
//    FuncTest* const Clone() const;
//    double Eval(const double* const xval,
//                const double* const par) const;
//};
//
//void FuncTest::Copy(const FuncTest* const org)
//{
//    if(this == org) {abort();}
//    if(NULL == org) {abort();}
//    
//    CopyTitle(org);
//    NullMshpFunc();
//    SetNpar(org->GetNpar());
//    SetNdim(org->GetNdim());
//}
//
//FuncTest* const FuncTest::Clone() const
//{
//    FuncTest* obj_new = new FuncTest;
//    obj_new->Copy(this);
//    return obj_new;
//}
//
//double FuncTest::Eval(const double* const xval,
//                      const double* const par) const
//{
//    double argx = xval[0];
//    double ans = par[0] + par[1] * argx + par[2] * pow(argx, 2.);
//    return ans;
//}


int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;

    {
        printf("--- test Init \n");
        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
        hd1d->Init(4, 0.0, 4.0);
        hd1d->PrintData(stdout, "x,y", 0.0, 0.0);
        delete hd1d;
        printf("=== \n");
    }

    {
        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
        hd1d->Init(4, 0.0, 4.0);
        double xval = 2.5;
        int ibin = hd1d->GetIbin(xval);
        printf("ibin = %d\n", ibin);
        double yval_in = 777.7;
        hd1d->SetOvalElm(ibin, yval_in);
        double yval_out = hd1d->GetOvalElmAtX(xval);
        printf("yval = %e\n", yval_out);
        hd1d->PrintData(stdout, "x,y", 0.0, 0.0);
        delete hd1d;
        printf("=== \n");
    }

    {
        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
        hd1d->Init(4, 0.0, 4.0);
        int nbin = hd1d->GetNbinX();
        printf("nbin = %d\n", nbin);
        delete hd1d;
        printf("=== \n");
    }

    {
        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
        hd1d->Init(4, 0.0, 4.0);
        hd1d->SetOvalElm(0, 10);
        hd1d->SetOvalElm(1, 20);
        hd1d->SetOvalElm(2, 30);
        hd1d->SetOvalElm(3, 5);

        printf("jjjj");
        int nevt = 1000;
        int rand_seed = 0;
        double* xval_arr = NULL;
        hd1d->GenRandomEvtFromProbDist(nevt, rand_seed,
                                       &xval_arr);
        delete hd1d;
        printf("=== \n");
    }
    
    



    

    
////    virtual void Init(const HistInfo1d* const hist_info) = 0;
//    {
//        printf("--- test Init \n");
//        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
//        HistInfo1d* hi1d = new HistInfo1d;
//        hi1d->InitSetByNbin(0.0, 4.0, 4);
//        hd1d->Init(hi1d);
//        hd1d->PrintData(stdout, "x,y", 0.0, 0.0);
//
//        delete hi1d;
//        delete hd1d;
//        printf("=== \n");
//    }
//
////    void SetOvalArr(const DataArray1d* const oval_arr);
//    {
//        printf("--- test  SetOvalArr(const DataArray1d* const oval_arr)\n");
//        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
//        hd1d->Init(4, 0.0, 4.0);
//
//        DataArrayNerr1d* da1d = new DataArrayNerr1d;
//        da1d->Init(4);
//        da1d->SetValElm(0, 0.1);
//        da1d->SetValElm(1, 0.2);
//        da1d->SetValElm(2, 0.3);
//        da1d->SetValElm(3, 0.4);
//        hd1d->SetOvalArr(da1d);
//        hd1d->PrintData(stdout, "x,y", 0.0, 0.0);
//        
//        delete da1d;
//        delete hd1d;
//        printf("=== \n");
//    }
//    
////    void SetOvalArr(long ndata, const double* const val);
//    {
//        printf("--- test  SetOvalArr(long ndata, const double* const val)\n");
//        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
//        hd1d->Init(4, 0.0, 4.0);
//
//        double val[4];
//        val[0] = 0.1;
//        val[1] = 0.2;
//        val[2] = 0.3;
//        val[3] = 0.4;
//        hd1d->SetOvalArr(4, val);
//        hd1d->PrintData(stdout, "x,y", 0.0, 0.0);
//
//        delete hd1d;
//        printf("=== \n");
//    }
//    
////    void SetOvalArr(vector<double> val);
//    {
//        printf("--- test  SetOvalArr(vector<double> val)\n");
//        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
//        hd1d->Init(4, 0.0, 4.0);
//
//        vector<double> val(4);
//        val[0] = 0.1;
//        val[1] = 0.2;
//        val[2] = 0.3;
//        val[3] = 0.4;
//        hd1d->SetOvalArr(val);
//        hd1d->PrintData(stdout, "x,y", 0.0, 0.0);
//
//        delete hd1d;
//        printf("=== \n");
//    }
//
////    void SetOvalElm(long ibin, double oval);
//    {
//        printf("--- test  SetOvalElm(long ibin, double oval)\n");
//        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
//        hd1d->Init(4, 0.0, 4.0);
//        hd1d->SetOvalElm(0, 0.1);
//        hd1d->SetOvalElm(1, 0.2);
//        hd1d->SetOvalElm(2, 0.3);
//        hd1d->SetOvalElm(3, 0.4);        
//        hd1d->PrintData(stdout, "x,y", 0.0, 0.0);
//        hd1d->Save("temp.dat", "x,y");
//        delete hd1d;
//        printf("=== \n");
//    }
//
////    void Fill(double xval);
//    {
//        printf("--- test  Fill(double xval)\n");
//        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
//        hd1d->Init(4, 0.0, 4.0);
//        hd1d->Fill(3.7);
//        hd1d->PrintData(stdout, "x,y", 0.0, 0.0);
//
//        delete hd1d;
//        printf("=== \n");
//    }
//    
////    void Fill(double xval, double weight);
//    {
//        printf("--- test  Fill(double xval, double weight)\n");
//        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
//        hd1d->Init(4, 0.0, 4.0);
//        hd1d->Fill(3.7, 4.0);
//        hd1d->PrintData(stdout, "x,y", 0.0, 0.0);
//
//        delete hd1d;
//        printf("=== \n");
//    }
//   
////    void FillByLarger(double xval, double oval);
//    {
//        printf("--- test  FillByLarger(double xval, double oval)\n");
//        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
//        hd1d->Init(4, 0.0, 4.0);
//        hd1d->FillByLarger(3.7, 4.0);
//        hd1d->PrintData(stdout, "x,y", 0.0, 0.0);
//
//        printf("--- \n");
//        hd1d->FillByLarger(3.7, 2.0);
//        hd1d->PrintData(stdout, "x,y", 0.0, 0.0);
//
//        printf("--- \n");        
//        hd1d->FillByLarger(3.7, 5.0);
//        hd1d->PrintData(stdout, "x,y", 0.0, 0.0);        
//
//        delete hd1d;
//        printf("=== \n");
//    }
//    
////    void FillBySmaller(double xval, double oval);
//    {
//        printf("--- test  FillBySmaller(double xval, double oval)\n");
//        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
//        hd1d->Init(4, 0.0, 4.0);
//        hd1d->FillBySmaller(3.7, -4.0);
//        hd1d->PrintData(stdout, "x,y", 0.0, 0.0);
//
//        printf("--- \n");
//        hd1d->FillBySmaller(3.7, 2.0);
//        hd1d->PrintData(stdout, "x,y", 0.0, 0.0);
//
//        printf("--- \n");        
//        hd1d->FillBySmaller(3.7, -5.0);
//        hd1d->PrintData(stdout, "x,y", 0.0, 0.0);        
//
//        delete hd1d;
//        printf("=== \n");
//    }
//    
////    void SetConst(double constant);
//    {
//        printf("--- test  SetConst(double constant)\n");
//        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
//        hd1d->Init(4, 0.0, 4.0);
//        hd1d->SetConst(2.0);
//        hd1d->PrintData(stdout, "x,y", 0.0, 0.0);        
//
//        delete hd1d;
//        printf("=== \n");
//    }
//    
////    void SetOneAtInterval(const Interval* const interval);
//    {
//        printf("--- test  SetOneAtInterval(const Interval* const interval)\n");
//        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
//        hd1d->Init(4, 0.0, 4.0);
//        hd1d->SetConst(2.0);
//        hd1d->PrintData(stdout, "x,y", 0.0, 0.0);        
//        Interval* interval = new Interval;
//        interval->InitSet(1.3, 2.4);
//        hd1d->SetOneAtInterval(interval);
//        hd1d->PrintData(stdout, "x,y", 0.0, 0.0);        
//
//        delete hd1d;
//        delete interval;
//        printf("=== \n");
//    }
//    
////    void SetByFunc(const MshpFunc* const func, const double* const par);
//    {
//        printf("--- test  SetByFunc\n");
//        FuncTest* func = new FuncTest;
//        double par[3] = {100.0, 2.0, 3.0};
//
//        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
//        hd1d->Init(4, 0.0, 4.0);
//        hd1d->SetByFunc(func, par);
//        hd1d->PrintData(stdout, "x,y", 0.0, 0.0);        
//        MshpQdpTool::MkQdp(hd1d, "temp.qdp", "x,y");
//        delete func;
//        delete hd1d;
//        printf("=== \n");
//    }
//   
////    void Copy(const HistData1d* const org);
//    {
//        printf("--- test  Copy\n");
//        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
//        hd1d->Init(4, 0.0, 4.0);
//        hd1d->SetOvalElm(0, 0.1);
//        hd1d->SetOvalElm(1, 0.2);
//        hd1d->SetOvalElm(2, 0.3);
//        hd1d->SetOvalElm(3, 0.4);
//        hd1d->PrintData(stdout, "x,y", 0.0, 0.0);
//
//        printf("--- \n");
//        HistDataNerr1d* hd1d_new = new HistDataNerr1d;
//        hd1d_new->Copy(hd1d);
//        hd1d_new->PrintData(stdout, "x,y", 0.0, 0.0);
//
//        delete hd1d;
//        delete hd1d_new;
//        printf("=== \n");
//    }
//    
////    virtual void Load(string file) = 0;
//    {
//        printf("--- test  Load\n");
//        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
//        hd1d->Load("data/test_hist1d.dat");
//        hd1d->PrintInfo(stdout);
//        hd1d->PrintData(stdout, "x,y", 0.0, 0.0);
//        hd1d->Save("temp.txt", "x,y");
//        delete hd1d;
//        printf("=== \n");
//    }
//    
////    const HistInfo1d* const GetHi1d() const {return hi1d_;};
//    {
//        printf("--- test  GetHi1d()\n");
//        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
//        hd1d->Init(4, 0.0, 4.0);
//        hd1d->SetOvalElm(0, 0.1);
//        hd1d->SetOvalElm(1, 0.2);
//        hd1d->SetOvalElm(2, 0.3);
//        hd1d->SetOvalElm(3, 0.4);
//
//        hd1d->GetHi1d()->Print(stdout);
//
//        delete hd1d;
//
//        printf("=== \n");
//    }
//
//   
////    virtual const DataArray1d* const GetOvalArr() const = 0;
//    {
//        printf("--- test  GetOvalArr()\n");
//        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
//        hd1d->Init(4, 0.0, 4.0);
//        hd1d->SetOvalElm(0, 0.1);
//        hd1d->SetOvalElm(1, 0.2);
//        hd1d->SetOvalElm(2, 0.3);
//        hd1d->SetOvalElm(3, 0.4);
//
//        for(long ibin = 0; ibin < hd1d->GetNbinX(); ibin ++){
//            printf("hd1d->GetOvalArr()->GetValElm(%ld) = %e\n",
//                   ibin, hd1d->GetOvalArr()->GetValElm(ibin));
//        }                
//
//        delete hd1d;
//
//        printf("=== \n");
//    }
//
//
////    long GetNbinX() const {return GetHi1d()->GetNbin();};
////    double GetXvalLo() const {return GetHi1d()->GetLo();};
////    double GetXvalUp() const {return GetHi1d()->GetUp();};
////    double GetXvalMd() const {return GetHi1d()->GetMd();};
////    double GetXvalFullWidth() const {return GetHi1d()->GetFullWidth();};
////    double GetXvalBinWidth() const {return GetHi1d()->GetBinWidth();};
//    {
//        printf("--- test GetNbinX() \n");
//        printf("--- test GetXvalLo() \n");
//        printf("--- test GetXvalUp() \n");
//        printf("--- test GetXvalMd() \n");
//        printf("--- test GetXvalFullWidth() \n");
//        printf("--- test GetXvalBinWidth() \n");
//        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
//        hd1d->Init(4, 0.0, 4.0);
//        hd1d->SetOvalElm(0, 0.1);
//        hd1d->SetOvalElm(1, 0.2);
//        hd1d->SetOvalElm(2, 0.3);
//        hd1d->SetOvalElm(3, 0.4);
//
//        printf("hd1d->GetNbinX() = %ld\n", hd1d->GetNbinX());
//        printf("hd1d->GetXvalLo() = %e\n", hd1d->GetXvalLo());
//        printf("hd1d->GetXvalUp() = %e\n", hd1d->GetXvalUp());
//        printf("hd1d->GetXvalMd() = %e\n", hd1d->GetXvalMd());
//        printf("hd1d->GetXvalFullWidth() = %e\n", hd1d->GetXvalFullWidth());
//        printf("hd1d->GetXvalBinWidth() = %e\n", hd1d->GetXvalBinWidth());
//
//        delete hd1d;
//
//        printf("=== \n");
//    }
//
////    double GetOvalElm(long ibin) const;
////    double GetOvalElmAtX(double xval) const;
//    {
//        printf("--- test GetOvalElm(long ibin) \n");
//        printf("--- test GetOvalElmAtX(double xval) \n");
//        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
//        hd1d->Init(8, 0.0, 4.0);
//        hd1d->SetOvalElm(0, 0.1);
//        hd1d->SetOvalElm(1, 0.2);
//        hd1d->SetOvalElm(2, 0.3);
//        hd1d->SetOvalElm(3, 0.4);
//        hd1d->SetOvalElm(4, 0.5);
//        hd1d->SetOvalElm(5, 0.6);
//        hd1d->SetOvalElm(6, 0.7);
//        hd1d->SetOvalElm(7, 0.8);
//
//        printf("hd1d->GetOvalElm(3) = %e\n",
//               hd1d->GetOvalElm(3));
//        printf("hd1d->GetOvalElmAtX(1.2) = %e\n",
//               hd1d->GetOvalElmAtX(1.2));
//
//        delete hd1d;
//
//        printf("=== \n");
//    }
//    
////    double GetXvalAtOvalMin() const;
////    double GetXvalAtOvalMax() const;
//    {
//        printf("--- test GetXvalAtOvalMin() \n");
//        printf("--- test GetXvalAtOvalMax() \n");
//
//        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
//        hd1d->Init(4, 0.0, 4.0);
//        hd1d->SetOvalElm(0, 0.1);
//        hd1d->SetOvalElm(1, 0.2);
//        hd1d->SetOvalElm(2, 0.3);
//        hd1d->SetOvalElm(3, 0.4);
//
//        printf("hd1d->GetXvalAtOvalMin() = %e\n", hd1d->GetXvalAtOvalMin());
//        printf("hd1d->GetXvalAtOvalMax() = %e\n", hd1d->GetXvalAtOvalMax());
//
//        delete hd1d;
//
//        printf("=== \n");
//    }
//
////    void GenXvalArr(double** const xval_arr_ptr,
////                    long* const nbin_ptr) const;
////    void GenXvalSerrArr(double** const xval_serr_arr_ptr,
////                        long* const nbin_ptr) const;
////    void GenOvalArr(double** const oval_arr_ptr,
////                    long* const nbin_ptr) const;
//    {
//        printf("--- test GenXvalArr \n");
//        printf("--- test GenXvalSerrArr \n");
//        printf("--- test GenOvalArr \n");
//
//        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
//        hd1d->Init(4, 0.0, 4.0);
//        hd1d->SetOvalElm(0, 0.1);
//        hd1d->SetOvalElm(1, 0.2);
//        hd1d->SetOvalElm(2, 0.3);
//        hd1d->SetOvalElm(3, 0.4);
//
//        long nbin = 0;
//        double* xval_arr = NULL;
//        double* xval_serr_arr = NULL;
//        double* oval_arr = NULL;
//        
//        hd1d->GenXvalArr(&xval_arr, &nbin);
//        printf("nbin = %ld\n", nbin);
//        for(long ibin = 0; ibin < nbin; ibin ++){
//            printf("xval_arr[%ld] = %e\n", ibin, xval_arr[ibin]);
//        }
//
//        printf("--- \n");
//        hd1d->GenXvalSerrArr(&xval_serr_arr, &nbin);
//        printf("nbin = %ld\n", nbin);
//        for(long ibin = 0; ibin < nbin; ibin ++){
//            printf("xval_serr_arr[%ld] = %e\n", ibin, xval_serr_arr[ibin]);
//        }
//
//        printf("--- \n");        
//        hd1d->GenOvalArr(&oval_arr, &nbin);
//        printf("nbin = %ld\n", nbin);
//        for(long ibin = 0; ibin < nbin; ibin ++){
//            printf("oval_arr[%ld] = %e\n", ibin, oval_arr[ibin]);
//        }
//
//        delete hd1d;
//        delete [] xval_arr;
//        delete [] xval_serr_arr;
//        delete [] oval_arr;
//
//        printf("=== \n");
//    }
//
////    long GetIbin(double xval) const;
////    double GetBinCenter(long ibin) const;
////    double GetBinLo(long ibin) const;
////    double GetBinUp(long ibin) const;
////    long GetIbin_WithHalfBinShifted(double val) const;
////    double GetOvalIntPolLin(double xval) const;
//    {
//        printf("--- test GetIbin(double xval)\n");
//        printf("--- test GetBinCenter(long ibin)\n");
//        printf("--- test GetBinLo(long ibin)\n");
//        printf("--- test GetBinUp(long ibin)\n");
//        printf("--- test GetIbin_WithHalfBinShifted(double val)\n");
//        printf("--- test GetOvalIntPolLin(double xval)\n");
//
//        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
//        hd1d->Init(4, 0.0, 4.0);
//        hd1d->SetOvalElm(0, 0.1);
//        hd1d->SetOvalElm(1, 0.2);
//        hd1d->SetOvalElm(2, 0.3);
//        hd1d->SetOvalElm(3, 0.4);
//
//        printf("hd1d->GetIbin(1.3) = %ld\n", hd1d->GetIbin(1.3));
//        printf("hd1d->GetBinCenter(2) = %e\n", hd1d->GetBinCenter(2));
//        printf("hd1d->GetBinLo(1) = %e\n", hd1d->GetBinLo(1));
//        printf("hd1d->GetBinUp(1) = %e\n", hd1d->GetBinUp(1));
//        printf("hd1d->GetIbin_WithHalfBinShifted(2.4) = %ld\n",
//               hd1d->GetIbin_WithHalfBinShifted(2.4));
//        // 2.4 --> 1
//        printf("hd1d->GetIbin_WithHalfBinShifted(0.3) = %ld\n",
//               hd1d->GetIbin_WithHalfBinShifted(0.3));
//        // 0.3 --> -1
//        
//        printf("hd1d->GetOvalIntPolLin(1.0) = %e\n",
//               hd1d->GetOvalIntPolLin(1.0));
//        // 1.0 --> 0.15
//
//        delete hd1d;
//
//        printf("=== \n");
//    }
//
////    void Save(string outfile, string format,
////              double offset_xval = 0.0,
////              double offset_oval = 0.0) const;
//    {
//        printf("--- test Save\n");
//
//        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
//        hd1d->Init(4, 0.0, 4.0);
//        hd1d->SetOvalElm(0, 0.1);
//        hd1d->SetOvalElm(1, 0.2);
//        hd1d->SetOvalElm(2, 0.3);
//        hd1d->SetOvalElm(3, 0.4);
//
//        hd1d->Save("temp.txt", "x,y");
//
//        delete hd1d;
//
//        printf("=== \n");
//    }
//    
////    void SaveData(string outfile, string format,
////                  double offset_xval = 0.0,
////                  double offset_oval = 0.0) const;
//    {
//        printf("--- test SaveData\n");
//
//        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
//        hd1d->Init(4, 0.0, 4.0);
//        hd1d->SetOvalElm(0, 0.1);
//        hd1d->SetOvalElm(1, 0.2);
//        hd1d->SetOvalElm(2, 0.3);
//        hd1d->SetOvalElm(3, 0.4);
//
//        hd1d->SaveData("temp.txt", "x,y");
//
//        delete hd1d;
//
//        printf("=== \n");
//    }
//    
////    void PrintInfo(FILE* fp) const;
//    {
//        printf("--- test PrintInfo\n");
//
//        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
//        hd1d->Init(4, 0.0, 4.0);
//        hd1d->SetOvalElm(0, 0.1);
//        hd1d->SetOvalElm(1, 0.2);
//        hd1d->SetOvalElm(2, 0.3);
//        hd1d->SetOvalElm(3, 0.4);
//
//        hd1d->PrintInfo(stdout);
//
//        delete hd1d;
//
//        printf("=== \n");
//    }
//   
////    virtual void PrintData(FILE* fp, string format,
////                           double offset_xval,
////                           double offset_oval) const = 0;
//    {
//        printf("--- test PrintData\n");
//
//        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
//        hd1d->Init(4, 0.0, 4.0);
//        hd1d->SetOvalElm(0, 0.1);
//        hd1d->SetOvalElm(1, 0.2);
//        hd1d->SetOvalElm(2, 0.3);
//        hd1d->SetOvalElm(3, 0.4);
//
//        hd1d->PrintData(stdout, "x,y", 0.0, 0.0);
//
//        delete hd1d;
//
//        printf("=== \n");
//    }
//
//    
////    void SaveRoot(string outfile,
////                  double offset_xval = 0.0,
////                  double offset_oval = 0.0) const;
//    {
//        printf("--- test SaveRoot\n");
//
//        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
//        hd1d->Init(4, 0.0, 4.0);
//        hd1d->SetOvalElm(0, 0.1);
//        hd1d->SetOvalElm(1, 0.2);
//        hd1d->SetOvalElm(2, 0.3);
//        hd1d->SetOvalElm(3, 0.4);
//
//        hd1d->SaveRoot("temp.root");
//
//        delete hd1d;
//
//        printf("=== \n");
//    }
//   
//
////    Interval* const GenIntervalAboveThreshold(double threshold) const;
//    {
//        printf("--- test GenIntervalAboveThreshold(double threshold)\n");
//
//        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
//        hd1d->Init(4, 0.0, 4.0);
//        hd1d->SetOvalElm(0, 0.1);
//        hd1d->SetOvalElm(1, 0.2);
//        hd1d->SetOvalElm(2, 0.3);
//        hd1d->SetOvalElm(3, 0.4);
//
//        Interval* interval = hd1d->GenIntervalAboveThreshold(0.25);
//        interval->Print(stdout);
//
//        delete hd1d;
//        delete interval;
//
//        printf("=== \n");
//    }
//    
////    Interval* const GenIntervalBelowThreshold(double threshold) const;
//    {
//        printf("--- test GenIntervalBelowThreshold(double threshold)\n");
//
//        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
//        hd1d->Init(4, 0.0, 4.0);
//        hd1d->SetOvalElm(0, 0.1);
//        hd1d->SetOvalElm(1, 0.2);
//        hd1d->SetOvalElm(2, 0.3);
//        hd1d->SetOvalElm(3, 0.4);
//
//        Interval* interval = hd1d->GenIntervalBelowThreshold(0.25);
//        interval->Print(stdout);
//
//        delete hd1d;
//        delete interval;
//
//        printf("=== \n");
//    }
//
////    // offset_tag = "st", "md", "ed", "no"
////    double GetOffsetXFromTag(string offset_tag) const;
//    {
//        printf("--- test GetOffsetXFromTag(string offset_tag)\n");
//
//        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
//        hd1d->Init(4, 0.0, 4.0);
//        hd1d->SetOvalElm(0, 0.1);
//        hd1d->SetOvalElm(1, 0.2);
//        hd1d->SetOvalElm(2, 0.3);
//        hd1d->SetOvalElm(3, 0.4);
//
//        printf("st = %e\n", hd1d->GetOffsetXFromTag("st"));
//        printf("md = %e\n", hd1d->GetOffsetXFromTag("md"));
//        printf("ed = %e\n", hd1d->GetOffsetXFromTag("ed"));
//        printf("no = %e\n", hd1d->GetOffsetXFromTag("no"));
//        printf("val = %e\n", hd1d->GetOffsetXFromTag("7.77"));        
//
//        delete hd1d;
//
//
//        printf("=== \n");
//    }
//
//
////    double GetOffsetOFromTag(string offset_tag) const;
//    {
//        printf("--- test GetOffsetOFromTag(string offset_tag)\n");
//
//        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
//        hd1d->Init(4, 0.0, 4.0);
//        hd1d->SetOvalElm(0, 0.1);
//        hd1d->SetOvalElm(1, 0.2);
//        hd1d->SetOvalElm(2, 0.3);
//        hd1d->SetOvalElm(3, 0.4);
//
//        printf("st = %e\n", hd1d->GetOffsetOFromTag("st"));
//        printf("md = %e\n", hd1d->GetOffsetOFromTag("md"));
//        printf("ed = %e\n", hd1d->GetOffsetOFromTag("ed"));
//        printf("no = %e\n", hd1d->GetOffsetOFromTag("no"));
//        printf("val = %e\n", hd1d->GetOffsetOFromTag("7.77"));        
//
//        delete hd1d;
//
//
//        printf("=== \n");
//    }
//    
////    static void ReadInfo(string file, 
////                         long* nbin_xval_ptr,
////                         double* xval_lo_ptr,
////                         double* xval_up_ptr,
////                         string* format_ptr);
//    {
//        printf("--- test ReadInfo\n");
//        
//        long nbin_xval = 0;
//        double xval_lo = 0.0;
//        double xval_up = 0.0;
//        string format = "";
//        
//        HistData1d::ReadInfo("data/test_hist1d.dat",
//                             &nbin_xval, &xval_lo, &xval_up, &format);
//        printf("nbin_xval = %ld\n", nbin_xval);
//        printf("xval_lo = %e\n", xval_lo);
//        printf("xval_up = %e\n", xval_up);        
//        printf("format = %s\n", format.c_str());                                     
//
//        printf("=== \n");
//    }

    return status_prog;
}
