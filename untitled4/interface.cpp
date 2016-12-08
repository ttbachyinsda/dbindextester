#include "interface.h"

bool naivedbinterface::insert(char *insertData, int dataLen, int pagenum, int pageposition)
{
    string input(insertData,dataLen);
    if (naive.data.count(input) != 0) return false;
    char s[200];
    memcpy(s,&pagenum,4);
    memcpy(s+4,&pageposition,4);
    string inputdata(s,8);
    naive.data[input]=inputdata;
    return true;
}
bool naivedbinterface::remove(char *insertData, int dataLen, int pagenum, int pageposition)
{
    string input(insertData,dataLen);
    if (naive.data.count(input) == 0) return false;
    naive.data.erase(naive.data.find(input));
    return true;
}
bool naivedbinterface::update(char *insertData, int dataLen, int prepagenum, int prepageposition, int pagenum, int pageposition)
{
    string input(insertData,dataLen);
    if (naive.data.count(input) == 0) return false;
    char s[200];
    memcpy(s,&pagenum,4);
    memcpy(s+4,&pageposition,4);
    string inputdata(s,8);
    naive.data[input]=inputdata;
    return true;
}
bool naivedbinterface::find(const string input, int &pagenum, int &pageposition)
{
    if (naive.data.count(input) == 0) return false;
    string temp = naive.data[input];
    memcpy(&pagenum,temp.data(),4);
    memcpy(&pageposition,temp.data()+4,4);
    return true;
}
