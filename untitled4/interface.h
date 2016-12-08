#ifndef INTERFACE_H
#define INTERFACE_H

#include "naivedb.h"
#include <string>
#include <cstring>
#include <cstdlib>
using namespace std;
class interface
{
public:
    interface(){}
    virtual bool insert(char* insertData, int dataLen, int pagenum,int pageposition)=0;
    virtual bool update(char* insertData, int dataLen, int prepagenum, int prepageposition, int pagenum, int pageposition)=0;
    virtual bool remove(char* insertData, int dataLen, int pagenum, int pageposition)=0;
    virtual bool find(string input, int &pagenum,int &pageposition)=0;
};
class naivedbinterface : public interface
{
public:
    naivedb naive;

    bool insert(char* insertData, int dataLen, int pagenum,int pageposition);
    bool update(char* insertData, int dataLen, int prepagenum, int prepageposition, int pagenum, int pageposition);
    bool remove(char* insertData, int dataLen, int pagenum, int pageposition);
    bool find(string input, int &pagenum,int &pageposition);
};

#endif // INTERFACE_H
