#ifndef MXSIM_HELPER_PLOT_CONF_H_
#define MXSIM_HELPER_PLOT_CONF_H_

#include "mshp_base.h"
#include "mshp_iolib.h"

//
// plot configuration
//

// format:
//
// lo_str  up_str   offset_tag   scale  !  label
//
// lo_str: value or "none"
// up_str: value or "none"
//         value: after offset subtraction
// offset_tag: value or "st", "md", "ed", "no"
// scale: "lin" or "log"
// label: any string, which can contain space.
//

class MshpPlotConf : public MshpObject{
public:
    explicit MshpPlotConf(string title = "") :
        MshpObject("MshpPlotConf", title),
        ndim_(0),
        lo_str_(NULL),
        up_str_(NULL),
        offset_tag_(NULL),
        scale_(NULL),
        label_(NULL) {}
    ~MshpPlotConf(){
        Null();
    }

    void Init(int ndim);
    void Load(string file);
    void SetIdimElm(int idim, string lo_str, string up_str,
                    string offset_tag, string scale, string label);
    void Copy(const MshpPlotConf* const org);
    MshpPlotConf* const Clone() const;

    // const func
    void Print(FILE* fp) const;
    
    int GetNdim() const {return ndim_;};
    const string* const GetLoStr() const {return lo_str_;};
    const string* const GetUpStr() const {return up_str_;};
    const string* const GetOffsetTag() const {return offset_tag_;};    
    const string* const GetScale() const {return scale_;};
    const string* const GetLabel() const {return label_;};
    string GetLoStrElm(int idim) const {return lo_str_[idim];};
    string GetUpStrElm(int idim) const {return up_str_[idim];};
    string GetOffsetTagElm(int idim) const {return offset_tag_[idim];};    
    string GetScaleElm(int idim) const {return scale_[idim];};
    string GetLabelElm(int idim) const {return label_[idim];};

    //
    // static
    //

    //              lo_str  up_str   offset_tag   scale  !  label
    // xval
    // yval
    // diff_val
    // diff_chi
    // diff_ratio

    static void GenPlotConf2(const MshpPlotConf* const plot_conf,
                             MshpPlotConf** const plot_conf_val_ptr,
                             MshpPlotConf** const plot_conf_ratio_ptr);
    static void GenPlotConf3(const MshpPlotConf* const plot_conf,
                             MshpPlotConf** const plot_conf_val_ptr,
                             MshpPlotConf** const plot_conf_chi_ptr,
                             MshpPlotConf** const plot_conf_ratio_ptr);
    
private:
    int ndim_;
    string* lo_str_;
    string* up_str_;
    string* offset_tag_;
    string* scale_;
    string* label_;

    void Null();
};


#endif // MXSIM_HELPER_PLOT_CONF_H_
