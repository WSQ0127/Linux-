#ifndef MiniLinux_H
#define MiniLinux_H
#include <bits/stdc++.h>
using namespace std;

class directory
{
public:
    bool type[100];//player's id, 0-folder
    vector<int> dire[100];
    vector<int> file[100];
    int dire_tot=0;
    void mkdir(int idx)
    {
        dire[idx].push_back(++dire_tot);
        type[dire_tot]=0;
    }
    void echo(int idx)
    {
        dire[idx].push_back(++dire_tot);
        type[dire_tot]=0;
    }
    void rm(int idx,bool sudo)
    {

    }
    void mv(int idxs,int idxe)
    {
        
    }
    void print()
    {
        cout<<"Home"<<endl;
        for(int i=1;i<=4;i++)
        {
            cout<<"  ├player"<<i<<endl;
            queue<int> q,dep;
            while(!q.empty())
            {
                int t=q.front();
                int space=dep.front();
                q.pop();dep.pop();
                for(int j=1;j<=space;j++)
                    cout<<"  ";
                if(type[t])
                {
                    cout<<"file"<<type[t]<<endl;
                }
                else
                {
                    cout<<"folder"<<t<<endl;
                    for(int j=0;j<dire[t].size();j++)
                    {
                        q.push(dire[t][j]);
                    }
                }
            }
        }
    }
};
#endif