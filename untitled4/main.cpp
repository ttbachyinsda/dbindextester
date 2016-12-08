#include <QCoreApplication>
#include "interface.h"
#include <iostream>


#define MAX_SIZE 600000

bool v[MAX_SIZE];
string s[MAX_SIZE];
int wz1[MAX_SIZE];
int wz2[MAX_SIZE];

string randomstring(int i)
{
    char s[4];
    memcpy(s,&i,4);
    string t(s,4);
    return t;
}

void begintest(interface* thistest)
{
    char tac[500];

    for (int i=0;i<MAX_SIZE;i++)
    {
        v[i]=true;
        s[i]=randomstring(i);
        wz1[i]=rand();
        wz2[i]=rand();
        memcpy(tac,s[i].data(),s[i].length());
        thistest->insert(tac,s[i].length(),wz1[i],wz2[i]);
    }

    int rightcommand = 0;
    int errorcommand = 0;
    int firsterror = -1;
    int errornum = -1;

    int k; bool can;
    int pn,pp;
    int s1,s2;

    for (int i=0;i<20000000;i++)
    {
        if (i%100000==0)
        {
            cout<<"now test: "<<i<<endl;
            cout<<"first error == "<<firsterror<<endl;
            cout<<"right command == "<<rightcommand<<endl;
            cout<<"error command == "<<errorcommand<<endl;
            cout<<"error num == "<<errornum<<endl;
        }
        int sss = rand()%4;
        switch(sss)
        {
        case 0:
            //cout<<"insert"<<endl;
            k=rand()*rand()%MAX_SIZE;
            memcpy(tac,s[k].data(),s[k].length());
            can=thistest->insert(tac,s[k].length(),wz1[k],wz2[k]);
            if (can ^ v[k]) rightcommand++;
            else
            {
                cout<<s[k].length()<<' '<<k<<' '<<wz1[k]<<' '<<wz2[k]<<endl;
                errorcommand++;
                if (firsterror==-1)
                {
                    firsterror = i;
                    errornum = 0;
                }
            }
            v[k]=true;
            break;
        case 1:
            //cout<<"remove"<<endl;
            k=rand()*rand()%MAX_SIZE;
            memcpy(tac,s[k].data(),s[k].length());
            can=thistest->remove(tac,s[k].length(),wz1[k],wz2[k]);
            if (can ^ (~v[k])) rightcommand++;
            else
            {
                errorcommand++;
                if (firsterror==-1)
                {
                    firsterror = i;
                    errornum = 1;
                }
            }
            v[k]=false;
            break;
        case 2:
            //cout<<"update"<<endl;
            k=rand()*rand()%MAX_SIZE;
            s1 = wz1[k] + 1;
            s2 = wz2[k] + 1;
            memcpy(tac,s[k].data(),s[k].length());
            can=thistest->update(tac,s[k].length(),wz1[k],wz2[k],s1,s2);
            if (can ^ (~v[k])) rightcommand++;
            else
            {
                errorcommand++;
                if (firsterror==-1)
                {
                    firsterror = i;
                    errornum = 2;
                }
            }
            wz1[k]++;
            wz2[k]++;
            break;
        case 3:
            //cout<<"find"<<endl;
            k=rand()*rand()%MAX_SIZE;
            can=thistest->find(s[k],pn,pp);
            if (can ^ (~v[k]))
            {
                if (!can || (pn==wz1[k] && pp==wz2[k]))
                {
                    rightcommand++;
                }
                else
                {
                    errorcommand++;
                    if (firsterror==-1)
                    {
                        cout<<pn<<' '<<pp<<' '<<wz1[k]<<' '<<wz2[k]<<endl;
                        firsterror = i;
                        errornum = 32;
                    }
                }
            }
            else
            {
                errorcommand++;
                if (firsterror==-1)
                {
                    firsterror = i;
                    errornum = 31;
                }
            }
            break;
        }
        if (firsterror != -1) break;
    }
    cout<<"test result:"<<endl;
    cout<<"first error == "<<firsterror<<endl;
    cout<<"right command == "<<rightcommand<<endl;
    cout<<"error command == "<<errorcommand<<endl<<endl<<endl;
    cout<<"error num == "<<errornum<<endl;
    if (firsterror == -1)
        cout<<"successful"<<endl;
    else
        cout<<"fail"<<endl;
}

int main(int argc, char *argv[])
{

    //freopen("d:\\output.txt","w",stdout);
    interface* thistest = new naivedbinterface();

    begintest(thistest);

    return 0;
}
