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
void naivedbinterface::findall(string input, vector<pair<int, int> > *res)
{

}
bool naivemultidbinterface::insert(char *insertData, int dataLen, int pagenum, int pageposition)
{
    string temp(insertData,dataLen);
    auto tempdata = make_pair(temp,make_pair(pagenum,pageposition));
    for (auto c = naive.data.begin();c<naive.data.end();c++)
    {
        if (*c == tempdata)
            return false;
    }
    naive.data.push_back(tempdata);
    return true;
}
bool naivemultidbinterface::remove(char *insertData, int dataLen, int pagenum, int pageposition)
{
    string temp(insertData,dataLen);
    auto tempdata = make_pair(temp,make_pair(pagenum,pageposition));
    for (auto c = naive.data.begin();c<naive.data.end();c++)
    {
        if (*c == tempdata)
        {
            naive.data.erase(c);
            return true;
        }

    }
    return false;
}
bool naivemultidbinterface::update(char *insertData, int dataLen, int prepagenum, int prepageposition, int pagenum, int pageposition)
{
    string temp(insertData,dataLen);
    auto tempdata = make_pair(temp,make_pair(prepagenum,prepageposition));
    auto resdata = make_pair(temp,make_pair(pagenum,pageposition));
    for (auto c = naive.data.begin();c<naive.data.end();c++)
    {
        if (*c == resdata)
        {
            return false;
        }

    }
    for (auto c = naive.data.begin();c<naive.data.end();c++)
    {
        if (*c == tempdata)
        {
            (*c).second.first = pagenum;
            (*c).second.second = pageposition;
            return true;
        }

    }
    return false;
}
bool naivemultidbinterface::find(string input, int &pagenum, int &pageposition)
{
    return false;
}
void naivemultidbinterface::findall(string input, vector<pair<int, int> > *res)
{
    for (auto c = naive.data.begin();c<naive.data.end();c++)
    {
        if ((*c).first == input)
        {
            res->push_back((*c).second);
        }

    }
}
