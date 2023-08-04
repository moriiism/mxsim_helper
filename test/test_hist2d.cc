#include "mshp_str.h"
#include "mshp_iolib.h"
#include "mshp_hist2d_nerr.h"
#include "mshp_qdp_tool.h"
//#include "mshp_func.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;

    {
        printf("--- test Init \n");
        HistDataNerr2d* hd2d = new HistDataNerr2d("hd2d");
        hd2d->Init(4, 0.0, 4.0, 2, 0.0, 2.0);
        hd2d->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);
        delete hd2d;
        printf("=== \n");
    }

    {
        HistDataNerr2d* hd2d = new HistDataNerr2d("hd2d");
        hd2d->Init(4, 0.0, 4.0, 2, 0.0, 2.0);
        double xval = 2.5;
        double yval = 1.3;
        int ibinx = hd2d->GetHi2d()->GetIbinXFromX(xval);
        int ibiny = hd2d->GetHi2d()->GetIbinYFromY(yval);
        printf("ibinx = %d\n", ibinx);
        printf("ibiny = %d\n", ibiny);

        double oval_in = 777.7;
        hd2d->SetOvalElm(ibinx, ibiny, oval_in);
        double oval_out = hd2d->GetOvalElmAtXY(xval, yval);
        printf("oval = %e\n", oval_out);
        hd2d->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);
        delete hd2d;
        printf("=== \n");
    }

    {
        HistDataNerr2d* hd2d = new HistDataNerr2d("hd2d");
        hd2d->Init(4, 0.0, 4.0, 2, 0.0, 2.0);
        int nbinx = hd2d->GetNbinX();
        int nbiny = hd2d->GetNbinY();
        printf("nbinx = %d\n", nbinx);
        printf("nbiny = %d\n", nbiny);
        delete hd2d;
        printf("=== \n");
    }

    {
        HistDataNerr2d* hd2d = new HistDataNerr2d("hd2d");
        hd2d->Init(4, 0.0, 4.0, 2, 0.0, 2.0);

        int ibinx = 2;
        double xval_lo = hd2d->GetHi2d()->GetHistInfoX()
            ->GetBinLo(ibinx);
        double xval_up = hd2d->GetHi2d()->GetHistInfoX()
            ->GetBinUp(ibinx);
        printf("xval_lo = %e\n", xval_lo);
        printf("xval_up = %e\n", xval_up);
        delete hd2d;
        printf("=== \n");
    }

    {
        HistDataNerr2d* hd2d = new HistDataNerr2d("hd2d");
        hd2d->Init(1, 0.0, 1.0, 2, 0.0, 2.0);        
        hd2d->SetOvalElm(0, 0, 3);
        hd2d->SetOvalElm(0, 1, 7);

        double* xval_arr = NULL;
        double* yval_arr = NULL;
        int nevt = 10000;
        int rand_seed = 0;
        hd2d->GenRandomEvtFromProbDist(nevt, rand_seed,
                                       &xval_arr, &yval_arr);
        for(int ievt = 0; ievt < nevt; ievt++){
            printf("%e, %e\n", xval_arr[ievt], yval_arr[ievt]);
        }


        HistDataNerr1d* hd1d = new HistDataNerr1d;
        hd1d->Init(2, 0.0, 2.0);
        for(int ievt = 0; ievt < nevt; ievt++){
            hd1d->Fill(yval_arr[ievt]);
        }
        MshpQdpTool::MkQdp(hd1d, "temp.qdp", "x,y");
        delete hd1d;
        delete hd2d;
        printf("=== \n");
    }

    // projection
    {
        HistDataNerr2d* hd2d = new HistDataNerr2d("hd2d");
        hd2d->Init(1, 0.0, 1.0, 2, 0.0, 2.0);        
        hd2d->SetOvalElm(0, 0, 3);
        hd2d->SetOvalElm(0, 1, 7);

        HistDataNerr1d* hd1d = new HistDataNerr1d;
        HistData2dOpe::GetProjectX(hd2d, 0, 1,
                                   "add", hd1d);

        printf("jjjjj");
        
        MshpQdpTool::MkQdp(hd1d, "temp_proj.qdp", "x,y");
        delete hd1d;
        delete hd2d;
        printf("=== \n");
    }

    // upper edge, lower edge
    {
        printf("--- test Init \n");
        HistDataNerr2d* hd2d = new HistDataNerr2d("hd2d");
        hd2d->Init(4, 0.0, 4.0, 2, 0.0, 2.0);

        int ibinx = 2;
        double xval_lo = hd2d->GetHi2d()->GetHistInfoX()
            ->GetBinLo(ibinx);
        double xval_up = hd2d->GetHi2d()->GetHistInfoX()
            ->GetBinUp(ibinx);
        printf("xval_lo = %e\n", xval_lo);
        printf("xval_up = %e\n", xval_up);

        delete hd2d;
        printf("=== \n");
    }

    
    
    
    
    return status_prog;
}
