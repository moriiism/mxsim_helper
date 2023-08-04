#ifndef MXSIM_HELPER_QDP_TOOL_H_
#define MXSIM_HELPER_QDP_TOOL_H_

#include "mshp_plot_conf.h"
#include "mshp_hist1d_nerr.h"
#include "mshp_hist1d_serr.h"
#include "mshp_hist1d_ope.h"
#include "mshp_hist2d_nerr.h"
#include "mshp_hist2d_serr.h"
#include "mshp_hist2d_ope.h"

namespace MshpQdpTool
{
    void GetRangeQdp(double min, double max,
                     double* const low_ptr, double* const up_ptr);
    
    void PrintQdpRead(FILE* fp, string format);
    void PrintQdpCmdStd(FILE* fp);
    void PrintQdpAxisRescale(FILE* fp, string xy,
                             double val_lo, double val_up);
    void PrintQdpAxisTitle(FILE* fp, string xy,
                           string title,
                           double offset);
    void PrintQdpScale(FILE* fp, string xy, string scale);
    void PrintQdpCmdDiffPlot(FILE* fp,
                             double xval_lo_data, double xval_up_data,
                             double oval_lo_w1_data, double oval_up_w1_data,
                             double oval_lo_w2_data, double oval_up_w2_data,
                             double offset_xval,
                             double offset_oval,
                             double offset_oval_res,
                             string title_xval,
                             string title_oval,
                             string title_oval_res,
                             string scale_xval,
                             string scale_oval,
                             string scale_oval_res);
    void PrintQdpCmdDiffPlot(FILE* fp,
                             double xval_lo_data, double xval_up_data,
                             double oval_lo_w1_data, double oval_up_w1_data,
                             double oval_lo_w2_data, double oval_up_w2_data,
                             double offset_xval,
                             double offset_oval,
                             double offset_oval_res,
                             const MshpPlotConf* const plot_conf);

    // format: index  data
    void MkQdpMode1(const DataArray1d* const data_array,
                    string qdpout,
                    string title_oval = "",
                    double offset_oval = 0.0,
                    string scale_xval = "lin",
                    string scale_oval = "lin");
    void MkQdpMode1(const DataArray1d* const data_array,
                    string qdpout,
                    const MshpPlotConf* const plot_conf);

    // format: data  1.0
    void MkQdpMode2(const DataArray1d* const data_array,
                    string qdpout,
                    string title_xval = "",
                    double offset_xval = 0.0,
                    string scale_xval = "lin");
    void MkQdpMode2(const DataArray1d* const data_array,
                    string qdpout,
                    const MshpPlotConf* const plot_conf);

    void MkQdp(const HistData1d* const hist_data,
               string outqdp,
               string format,
               string title_xval = "",
               string title_oval = "",
               double offset_xval = 0.0,
               double offset_oval = 0.0,
               string scale_xval = "lin",
               string scale_oval = "lin");
    void MkQdp(const HistData1d* const hist_data,
               string outqdp,
               string format,
               const MshpPlotConf* const plot_conf);

    void MkQdp(const MshpFunc* const func, const double* const par,
               int npoint, double xval_lo, double xval_up,
               string outqdp,
               string title_xval = "",
               string title_oval = "",
               double offset_xval = 0.0,
               double offset_oval = 0.0,
               string scale_xval = "lin",
               string scale_oval = "lin");
    void MkQdp(const MshpFunc* const func, const double* const par,
               int npoint, double xval_lo, double xval_up,
               string outqdp,
               const MshpPlotConf* const plot_conf);

    void MkQdpDiff(const HistData1d* const hist_data,
                   const HistData1d* const hist_model,
                   const HistData1d* const hist_res,
                   string qdpout,
                   string format,
                   string title_xval = "",
                   string title_oval = "",
                   string title_oval_res = "",
                   double offset_xval = 0.0,
                   double offset_oval = 0.0,
                   double offset_oval_res = 0.0,
                   string scale_xval = "lin",
                   string scale_oval = "lin",
                   string scale_oval_res = "lin");
    void MkQdpDiff(const HistData1d* const hist_data,
                   const HistData1d* const hist_model,
                   const HistData1d* const hist_res,
                   string qdpout,
                   string format,
                   const MshpPlotConf* const plot_conf);

    // hist_data, func
    void MkQdpDiff3Serr(const HistData1d* const hist_data,
                        const MshpFunc* const func, const double* const par,
                        int npoint_func,
                        string outdir, string qdpout_head,
                        string title_xval = "",
                        string title_oval = "",
                        double offset_xval = 0.0,
                        double offset_oval = 0.0,
                        string scale_xval = "lin",
                        string scale_oval = "lin");
    void MkQdpDiff3Serr(const HistData1d* const hist_data,
                        const MshpFunc* const func, const double* const par,
                        int npoint_func,
                        string outdir, string qdpout_head,
                        const MshpPlotConf* const plot_conf);

    void MkQdpDiff2Terr(const HistData1d* const hist_data,
                        const MshpFunc* const func, const double* const par,
                        int npoint_func,
                        string outdir, string qdpout_head,
                        string title_xval = "",
                        string title_oval = "",
                        double offset_xval = 0.0,
                        double offset_oval = 0.0,
                        string scale_xval = "lin",
                        string scale_oval = "lin");
    void MkQdpDiff2Terr(const HistData1d* const hist_data,
                        const MshpFunc* const func, const double* const par,
                        int npoint_func,
                        string outdir, string qdpout_head,
                        const MshpPlotConf* const plot_conf);

    // plot N HistData in one qdp file
    void MkQdpNhist(const HistData1d* const* const hist_arr, int nhist,
                    string qdpout,
                    double offset_xval = 0.0);

    void MkQdpProj(const MshpFunc* const func, const double* const par,
                   double xval_lo, double xval_up, double yval_lo, double yval_up,
                   string outdir, string qdpout_head, string calc_mode,
                   int npoint_func,
                   string title_xval = "",
                   string title_yval = "",
                   string title_oval = "",
                   double offset_xval = 0.0,
                   double offset_yval = 0.0,
                   double offset_oval = 0.0,
                   string scale_xval = "lin",
                   string scale_yval = "lin",
                   string scale_oval = "lin");
    void MkQdpProj(const MshpFunc* const func, const double* const par,
                   double xval_lo, double xval_up, double yval_lo, double yval_up,
                   string outdir, string qdpout_head, string calc_mode,
                   int npoint_func,
                   const MshpPlotConf* const plot_conf_projx,
                   const MshpPlotConf* const plot_conf_projy);
    
    void MkQdpDiffProjSerr(const HistData2d* const hist_data,
                           const MshpFunc* const func, const double* const par,
                           string outdir, string qdpout_head,
                           string add_mode, string error_mode,
                           string title_xval = "",
                           string title_yval = "",
                           string title_oval = "",                              
                           double offset_xval = 0.0,
                           double offset_yval = 0.0,
                           double offset_oval = 0.0,
                           string scale_xval = "lin",
                           string scale_yval = "lin",
                           string scale_oval = "lin");
    void MkQdpDiffProjSerr(const HistData2d* const hist_data,
                           const MshpFunc* const func, const double* const par,
                           string outdir, string qdpout_head,
                           string add_mode, string error_mode,
                           const MshpPlotConf* const plot_conf_projx,
                           const MshpPlotConf* const plot_conf_projy);
    void MkQdpDiffProjTerr(const HistData2d* const hist_data,
                           const MshpFunc* const func, const double* const par,
                           string outdir, string qdpout_head,
                           string add_mode, string error_mode,
                           string title_xval = "",
                           string title_yval = "",
                           string title_oval = "",                              
                           double offset_xval = 0.0,
                           double offset_yval = 0.0,
                           double offset_oval = 0.0,
                           string scale_xval = "lin",
                           string scale_yval = "lin",
                           string scale_oval = "lin");
    void MkQdpDiffProjTerr(const HistData2d* const hist_data,
                           const MshpFunc* const func, const double* const par,
                           string outdir, string qdpout_head,
                           string add_mode, string error_mode,
                           const MshpPlotConf* const plot_conf_projx,
                           const MshpPlotConf* const plot_conf_projy);
}

#endif // MXSIM_HELPER_QDP_TOOL_H_
