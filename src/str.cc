#include "mshp_str.h"

//
// If the string buf is composed of only ' ' and '\t',
// this returns 1.
// If the string buf is "", this returns also 1.
// In the other cases, this returns 0.
//
int MshpStr::IsSpace(string buf)
{
    int flag_only_space = 1;
    int nsize = buf.size();
    for(int ichar = 0; ichar < nsize; ichar++){
        if(0 == isspace(buf[ichar])){
            flag_only_space = 0;
            break;
        }
    }
    return flag_only_space;
}

//
// If the string buf contains '\n' at the last point,
// this remove the '\n'.
//

int MshpStr::Chomp(char* const buf)
{
    int ret = kRetNormal;
    int len = strlen(buf);
    if(len > 0 && buf[len - 1] == '\n')
        buf[len - 1] = '\0';
    return ret;
}

int MshpStr::Chomp(string* const buf_ptr)
{
    int ret = kRetNormal;
    int len = buf_ptr->size();
    if(len > 0 && '\n' == buf_ptr->at(len - 1)){
        buf_ptr->erase(len - 1);
    }
    return ret;
}

void MshpStr::RmStSpace(string* const buf_ptr)
{
    if(1 == IsSpace(*buf_ptr)){
        buf_ptr->erase(0);
    } else {
        // remove st spase
        int nchar = buf_ptr->size();
        int index = 0;
        for(int ichar = 0; ichar < nchar; ichar++){
            if(0 == isspace(buf_ptr->at(ichar))){
                index = ichar;
                break;
            }
        }
        if(index > 0){
            buf_ptr->erase(0, index);
        }
    }
}


void MshpStr::RmEdSpace(string* const buf_ptr)
{
    if(1 == IsSpace(*buf_ptr)){
        buf_ptr->erase(0);
    } else {
        // remove ed spase
        int nchar = buf_ptr->size();
        int index = nchar;
        for(int ichar = nchar - 1; ichar >= 0; ichar--){
            if(0 == isspace(buf_ptr->at(ichar))){
                index = ichar;
                break;
            }
        }
        if(index < nchar - 1){
            buf_ptr->erase(index + 1);
        }
    }
}

void MshpStr::RmStEdSpace(string* const buf_ptr)
{
    RmStSpace(buf_ptr);
    RmEdSpace(buf_ptr);
}

void MshpStr::GenSplit(string str_in, int* nsplit_ptr, string** split_arr_ptr,
                       const char* const delim)
{
    int nlength = str_in.length();
    char* line = new char[nlength + 1];
    strcpy(line, str_in.c_str());

    vector<string> split_vec;
    char* strtok_ptr = line;
    char* line_ptr = NULL;
    while(NULL != (line_ptr = strtok(strtok_ptr, delim) ) ){
        split_vec.push_back(line_ptr);
        strtok_ptr = NULL;
    }
    int nsplit = split_vec.size();
    string* split_arr = new string [nsplit];
    for(int ivec = 0; ivec < nsplit; ivec++){
        split_arr[ivec] = split_vec[ivec].c_str();
    }
    delete [] line;
    
    *nsplit_ptr = nsplit;
    *split_arr_ptr = split_arr;
}

void MshpStr::DelSplit(string* split_arr)
{
    delete [] split_arr;
}

int MshpStr::GetNcolumn(string str_in, const char* const delim)
{
    int nlength = str_in.length();
    char* line = new char[nlength + 1];
    strcpy(line, str_in.c_str());

    vector<string> split_vec;
    char* strtok_ptr = line;
    char* line_ptr = NULL;
    while(NULL != (line_ptr = strtok(strtok_ptr, delim) ) ){
        split_vec.push_back(line_ptr);
        strtok_ptr = NULL;
    }
    int nsplit = split_vec.size();
    delete [] line;
    return nsplit;
}
