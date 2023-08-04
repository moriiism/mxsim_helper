#include "mshp_plot_conf.h"

// public

void MshpPlotConf::Init(int ndim)
{
    Null();
    
    ndim_ = ndim;
    lo_str_ = new string [ndim];
    up_str_ = new string [ndim];
    offset_tag_ = new string [ndim];
    scale_  = new string [ndim];
    label_  = new string [ndim];
    for(int idim = 0; idim < ndim; idim++){
        lo_str_[idim] = "";
        up_str_[idim] = "";
        offset_tag_[idim] = "";        
        scale_[idim]  = "";
        label_[idim]  = "";
    }
}

void MshpPlotConf::Load(string file)
{
    Null();

    string* line_arr = NULL;
    long ndim = 0;
    MshpIolib::GenReadFileSkipComment(file, &line_arr, &ndim);
    Init(ndim);
    for(long idim = 0; idim < ndim; idim ++){
        int ncolumn = MshpStr::GetNcolumn(line_arr[idim]);
        if(6 > ncolumn){
            char msg[kLineSize];
            sprintf(msg, "ncolumn < 6: "
                    "format: lo_str  up_str  offset_tag  scale  !  label");
            MshpPrintErr(msg);
        }
        char lo_char[kLineSize];
        char up_char[kLineSize];
        char offset_tag_char[kLineSize];
        char scale_char[kLineSize];
        sscanf(line_arr[idim].c_str(), "%s  %s  %s  %s",
               lo_char, up_char, offset_tag_char, scale_char);
        
        string line_str = line_arr[idim];
        int ipos_delim = line_str.find("!");
        string label_str = line_str.substr(ipos_delim + 1);
        MshpStr::RmStEdSpace(&label_str);
        SetIdimElm(idim, lo_char, up_char,
                   offset_tag_char, scale_char, label_str);
    }
    MshpIolib::DelReadFile(line_arr);
}


void MshpPlotConf::SetIdimElm(int idim, string lo_str, string up_str,
                             string offset_tag, string scale, string label)
{
    if(idim >= GetNdim()){
        char msg[kLineSize];
        sprintf(msg, "bad idim (=%d) for ndim (=%d)",
                idim, GetNdim());
        MshpPrintErr(msg);
        abort();
    }
    lo_str_[idim] = lo_str;
    up_str_[idim] = up_str;
    offset_tag_[idim] = offset_tag;
    scale_[idim] = scale;
    label_[idim] = label;
}

void MshpPlotConf::Copy(const MshpPlotConf* const org)
{
    if(this == org) {abort();}
    if(NULL == org) {abort();}
    
    CopyTitle(org);
    Init(org->GetNdim());
    for(int idim = 0; idim < org->GetNdim(); idim++){
        lo_str_[idim] = org->lo_str_[idim];
        up_str_[idim] = org->up_str_[idim];
        offset_tag_[idim] = org->offset_tag_[idim];
        scale_[idim] = org->scale_[idim];
        label_[idim] = org->label_[idim];
    }
}

MshpPlotConf* const MshpPlotConf::Clone() const
{
    MshpPlotConf* obj_new = new MshpPlotConf;
    obj_new->Copy(this);
    return obj_new;
}

void MshpPlotConf::Print(FILE* fp) const
{
    fprintf(fp, "%s: ndim = %d\n", GetClassName().c_str(), GetNdim());
    for(int idim = 0; idim < GetNdim(); idim ++){
        fprintf(fp, "%s: lo_str_[%d] = %s\n",
                GetClassName().c_str(), idim, GetLoStrElm(idim).c_str());
        fprintf(fp, "%s: up_str_[%d] = %s\n",
               GetClassName().c_str(), idim, GetUpStrElm(idim).c_str());
        fprintf(fp, "%s: offset_tag_[%d] = %s\n",
                GetClassName().c_str(), idim, GetOffsetTagElm(idim).c_str());
        fprintf(fp, "%s: scale_[%d] = %s\n",
                GetClassName().c_str(), idim, GetScaleElm(idim).c_str());
        fprintf(fp, "%s: label_[%d] = %s\n",
                GetClassName().c_str(), idim, GetLabelElm(idim).c_str());
    }
}

//
// static
//

void MshpPlotConf::GenPlotConf2(const MshpPlotConf* const plot_conf,
                               MshpPlotConf** const plot_conf_val_ptr,
                               MshpPlotConf** const plot_conf_ratio_ptr)
{
    if(4 != plot_conf->GetNdim()){
        MshpPrintErr("bad plot_conf (ndim of plot_conf is not 4)");
        abort();
    }
    MshpPlotConf* plot_conf_val = new MshpPlotConf;
    MshpPlotConf* plot_conf_ratio = new MshpPlotConf;
    plot_conf_val->Init(3);
    plot_conf_ratio->Init(3);

    int idim = 0;
    plot_conf_val->SetIdimElm(idim,
                              plot_conf->GetLoStrElm(idim),
                              plot_conf->GetUpStrElm(idim),
                              plot_conf->GetOffsetTagElm(idim),
                              plot_conf->GetScaleElm(idim),
                              plot_conf->GetLabelElm(idim));
    plot_conf_ratio->SetIdimElm(idim,
                                plot_conf->GetLoStrElm(idim),
                                plot_conf->GetUpStrElm(idim),
                                plot_conf->GetOffsetTagElm(idim),
                                plot_conf->GetScaleElm(idim),
                                plot_conf->GetLabelElm(idim));
    idim = 1;
    plot_conf_val->SetIdimElm(idim,
                              plot_conf->GetLoStrElm(idim),
                              plot_conf->GetUpStrElm(idim),
                              plot_conf->GetOffsetTagElm(idim),
                              plot_conf->GetScaleElm(idim),
                              plot_conf->GetLabelElm(idim));
    plot_conf_ratio->SetIdimElm(idim,
                                plot_conf->GetLoStrElm(idim),
                                plot_conf->GetUpStrElm(idim),
                                plot_conf->GetOffsetTagElm(idim),
                                plot_conf->GetScaleElm(idim),
                                plot_conf->GetLabelElm(idim));
    idim = 2;
    int idim_val = 2;
    int idim_ratio = 3;
    plot_conf_val->SetIdimElm(idim,
                              plot_conf->GetLoStrElm(idim_val),
                              plot_conf->GetUpStrElm(idim_val),
                              plot_conf->GetOffsetTagElm(idim_val),
                              plot_conf->GetScaleElm(idim_val),
                              plot_conf->GetLabelElm(idim_val));
    plot_conf_ratio->SetIdimElm(idim,
                                plot_conf->GetLoStrElm(idim_ratio),
                                plot_conf->GetUpStrElm(idim_ratio),
                                plot_conf->GetOffsetTagElm(idim_ratio),
                                plot_conf->GetScaleElm(idim_ratio),
                                plot_conf->GetLabelElm(idim_ratio));

    *plot_conf_val_ptr = plot_conf_val;
    *plot_conf_ratio_ptr = plot_conf_ratio;    
}

void MshpPlotConf::GenPlotConf3(const MshpPlotConf* const plot_conf,
                               MshpPlotConf** const plot_conf_val_ptr,
                               MshpPlotConf** const plot_conf_chi_ptr,
                               MshpPlotConf** const plot_conf_ratio_ptr)
{
    if(5 != plot_conf->GetNdim()){
        MshpPrintErr("bad plot_conf (ndim of plot_conf is not 5)");
        abort();
    }
    MshpPlotConf* plot_conf_val = new MshpPlotConf;
    MshpPlotConf* plot_conf_chi = new MshpPlotConf;
    MshpPlotConf* plot_conf_ratio = new MshpPlotConf;
    plot_conf_val->Init(3);
    plot_conf_chi->Init(3);
    plot_conf_ratio->Init(3);

    int idim = 0;
    plot_conf_val->SetIdimElm(idim,
                              plot_conf->GetLoStrElm(idim),
                              plot_conf->GetUpStrElm(idim),
                              plot_conf->GetOffsetTagElm(idim),
                              plot_conf->GetScaleElm(idim),
                              plot_conf->GetLabelElm(idim));
    plot_conf_chi->SetIdimElm(idim,
                              plot_conf->GetLoStrElm(idim),
                              plot_conf->GetUpStrElm(idim),
                              plot_conf->GetOffsetTagElm(idim),
                              plot_conf->GetScaleElm(idim),
                              plot_conf->GetLabelElm(idim));
    plot_conf_ratio->SetIdimElm(idim,
                                plot_conf->GetLoStrElm(idim),
                                plot_conf->GetUpStrElm(idim),
                                plot_conf->GetOffsetTagElm(idim),
                                plot_conf->GetScaleElm(idim),
                                plot_conf->GetLabelElm(idim));
    idim = 1;
    plot_conf_val->SetIdimElm(idim,
                              plot_conf->GetLoStrElm(idim),
                              plot_conf->GetUpStrElm(idim),
                              plot_conf->GetOffsetTagElm(idim),
                              plot_conf->GetScaleElm(idim),
                              plot_conf->GetLabelElm(idim));
    plot_conf_chi->SetIdimElm(idim,
                              plot_conf->GetLoStrElm(idim),
                              plot_conf->GetUpStrElm(idim),
                              plot_conf->GetOffsetTagElm(idim),
                              plot_conf->GetScaleElm(idim),
                              plot_conf->GetLabelElm(idim));
    plot_conf_ratio->SetIdimElm(idim,
                                plot_conf->GetLoStrElm(idim),
                                plot_conf->GetUpStrElm(idim),
                                plot_conf->GetOffsetTagElm(idim),
                                plot_conf->GetScaleElm(idim),
                                plot_conf->GetLabelElm(idim));
    idim = 2;
    int idim_val = 2;
    int idim_chi = 3;
    int idim_ratio = 4;
    plot_conf_val->SetIdimElm(idim,
                              plot_conf->GetLoStrElm(idim_val),
                              plot_conf->GetUpStrElm(idim_val),
                              plot_conf->GetOffsetTagElm(idim_val),
                              plot_conf->GetScaleElm(idim_val),
                              plot_conf->GetLabelElm(idim_val));
    plot_conf_chi->SetIdimElm(idim,
                              plot_conf->GetLoStrElm(idim_chi),
                              plot_conf->GetUpStrElm(idim_chi),
                              plot_conf->GetOffsetTagElm(idim_chi),
                              plot_conf->GetScaleElm(idim_chi),
                              plot_conf->GetLabelElm(idim_chi));
    plot_conf_ratio->SetIdimElm(idim,
                                plot_conf->GetLoStrElm(idim_ratio),
                                plot_conf->GetUpStrElm(idim_ratio),
                                plot_conf->GetOffsetTagElm(idim_ratio),
                                plot_conf->GetScaleElm(idim_ratio),
                                plot_conf->GetLabelElm(idim_ratio));

    *plot_conf_val_ptr = plot_conf_val;
    *plot_conf_chi_ptr = plot_conf_chi;
    *plot_conf_ratio_ptr = plot_conf_ratio;    
}

// private

void MshpPlotConf::Null()
{
    ndim_ = 0;
    if(NULL != lo_str_) {delete [] lo_str_; lo_str_ = NULL;}
    if(NULL != up_str_) {delete [] up_str_; up_str_ = NULL;}
    if(NULL != offset_tag_) {delete [] offset_tag_; offset_tag_ = NULL;}
    if(NULL != scale_) {delete [] scale_; scale_ = NULL;}
    if(NULL != label_) {delete [] label_; label_ = NULL;}
}
