#include <QCoreApplication>
#include "interface.h"
#include <iostream>
#include <bitset>
#include <unordered_map>
using namespace std;

#define MAX_SIZE 20000
#define KEY_RANGE 2000
#define WZ_RANGE 200

unordered_multimap<string,pair<int,int>> data;
#define BANERRORUPDATE false

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
int stringtoint(string temp)
{
    int te;
    memcpy(&te,temp.data(),4);
    return te;
}
void beginmultitest(interface* thistest)
{
    char tac[500];
    data.clear();
    for (int i=0;i<MAX_SIZE;i++)
    {
        auto tempstring = randomstring(rand()*rand()%KEY_RANGE);
        auto w1=rand()%WZ_RANGE,w2=rand()%WZ_RANGE;
        memcpy(tac,tempstring.data(),tempstring.length());
        int ss = 0;
        auto range = data.equal_range(tempstring);
        for (auto x=range.first; x!=range.second; x++)
        {
            if (x->second.first == w1 && x->second.second == w2)
                ss = 1;
        }
        if (ss == 0)data.insert(make_pair(tempstring,make_pair(w1,w2)));
        //nowdata[make_pair(tempstring,make_pair(w1,w2))] = 1;
        thistest->insert(tac,tempstring.length(),w1,w2);
    }

    //    for (auto& x: data)
    //        cout<<x.first<<' '<<x.second.first<<' '<<x.second.second<<endl;

    //    auto range = data.equal_range(randomstring(0));
    //    for_each(range.first,range.second,[](unordered_multimap<string,pair<int,int>>::value_type & x)
    //    {
    //        cout<<x.first<<' '<<x.second.first<<' '<<x.second.second<<endl;
    //    }
    //    );

    cout<<"insert end"<<endl;

    int rightcommand = 0;
    int errorcommand = 0;
    int firsterror = -1;
    int errornum = -1;

    int k; int w1,w2; int ss;
    bool can;
    string sk;
    vector<pair<int,int>> res1,res2;
    auto range = data.equal_range("");
    auto x = range.first;

    for (int i=0;i<200000;i++)
    {
        if (i%1000==0)
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
            k=rand()*rand()%KEY_RANGE;
            w1 = rand()%WZ_RANGE;
            w2 = rand()%WZ_RANGE;
            sk = randomstring(k);
            memcpy(tac,sk.data(),sk.length());
            can=thistest->insert(tac,sk.length(),w1,w2);

            range = data.equal_range(sk);
            ss = 0;
            for (x=range.first; x!=range.second; x++)
            {
                if (x->second.first == w1 && x->second.second == w2)
                    ss = 1;
            }
            //int ss = nowdata.count(make_pair(sk,make_pair(w1,w2)));

            if ((ss == 0 && can) || (ss == 1 && !can)) rightcommand++;
            else
            {
                cout<<k<<' '<<w1<<' '<<w2<<endl;
                errorcommand++;
                if (firsterror==-1)
                {
                    firsterror = i;
                    errornum = 0;
                }
            }
            if (ss==0)
                //nowdata[make_pair(sk,make_pair(w1,w2))] = 1;
                data.insert(make_pair(sk,make_pair(w1,w2)));
            break;
        case 1:
            //cout<<"remove"<<endl;
            k=rand()*rand()%KEY_RANGE;
            w1 = rand()%WZ_RANGE;
            w2 = rand()%WZ_RANGE;
            sk = randomstring(k);
            memcpy(tac,sk.data(),sk.length());
            can=thistest->remove(tac,sk.length(),w1,w2);

            range = data.equal_range(sk);
            ss = 0;

            for (x = range.first;x!=range.second;x++)
            {
                if (x->second.first == w1 && x->second.second == w2)
                {
                    ss = 1;
                    data.erase(x);
                    break;
                }
                //cout<<x.first<<' '<<x.second.first<<' '<<x.second.second<<endl;
            }
            //int ss = nowdata.count(make_pair(sk,make_pair(w1,w2)));

            if ((ss == 1 && can) || (ss == 0 && !can)) rightcommand++;
            else
            {
                cout<<k<<' '<<w1<<' '<<w2<<endl;
                errorcommand++;
                if (firsterror==-1)
                {
                    firsterror = i;
                    errornum = 1;
                }
            }
            break;
        case 2:
            //cout<<"update"<<endl;
            k=rand()*rand()%KEY_RANGE;
            w1 = rand()%WZ_RANGE;
            w2 = rand()%WZ_RANGE;
            sk = randomstring(k);
            memcpy(tac,sk.data(),sk.length());


            range = data.equal_range(sk);
            ss = 0;
            for (x = range.first;x!=range.second;x++)
            {
                if (x->second.first == w1+1 && x->second.second == w2+1)
                {
                    ss = -1;
                }
                //cout<<x.first<<' '<<x.second.first<<' '<<x.second.second<<endl;
            }
            if (ss==-1 && BANERRORUPDATE)
            {
                i--;
                break;
            }
            if (ss!=-1)
            {
            for (x = range.first;x!=range.second;x++)
            {
                if (x->second.first == w1 && x->second.second == w2)
                {
                    ss = 1;
                    x->second.first ++;
                    x->second.second ++;
                }
                //cout<<x.first<<' '<<x.second.first<<' '<<x.second.second<<endl;
            }
            } else
            {
                //cout<<"error update occured"<<endl;
                ss = 0;
            }
            //int ss = nowdata.count(make_pair(sk,make_pair(w1,w2)));
            can=thistest->update(tac,sk.length(),w1,w2,w1+1,w2+1);
            if ((ss == 1 && can) || (ss == 0 && !can)) rightcommand++;
            else
            {
                cout<<k<<' '<<w1<<' '<<w2<<endl;
                errorcommand++;
                if (firsterror==-1)
                {
                    firsterror = i;
                    errornum = 2;
                }
            }
            break;
        case 3:
            //cout<<"find"<<endl;
            k=rand()*rand()%KEY_RANGE;
            res1.clear();
            res2.clear();
            sk = randomstring(k);
            thistest->findall(sk,&res1);
            range = data.equal_range(sk);
            ss = 0;
            for (x = range.first;x!=range.second;x++)
            {
                res2.push_back(make_pair(x->second.first,x->second.second));
                //cout<<x.first<<' '<<x.second.first<<' '<<x.second.second<<endl;
            }
            sort(res1.begin(),res1.end());
            sort(res2.begin(),res2.end());

            if (res1.size() != res2.size())
            {
                errorcommand++;
                if (firsterror==-1)
                {
                    firsterror = i;
                    errornum = 30;
                }
            } else
            {
                bool ofcan = true;
                for (int i=0;i<res1.size();i++)
                    if (res1[i].first!=res2[i].first || res1[i].second!=res2[i].second)
                        ofcan=false;
                if (!ofcan)
                {
                    firsterror = i;
                    errornum = 31;
                } else
                    rightcommand ++;
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
//    vector<string> sst;
//    char tempss[4];
//    for (int i=0;i<1000;i++)
//    {
//        bitset<32> tb(i);
//        memcpy(tempss,&tb,4);
//        string so(tempss,4);
//        sst.push_back(so.data());
//    }
//    sort(sst.begin(),sst.end());
//    for (int i=0;i<1000;i++)
//    {
//        bitset<32> sb;
//        memcpy(&sb,sst[i].data(),4);
//        cout<<sb.to_ulong()<<endl;
//    }



    //freopen("d:\\output.txt","w",stdout);
//    interface* thistest = new naivedbinterface();

//    begintest(thistest);
    interface* test2 = new naivemultidbinterface();
    beginmultitest(test2);

//    delete thistest;
    delete test2;

    return 0;
}
