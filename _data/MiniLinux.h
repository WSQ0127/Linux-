#ifndef MiniLinux_H
#define MiniLinux_H
#include <bits/stdc++.h>
using namespace std;

class directory
{
    struct node
    {
        int id,dep;
    };
public:
    bool type[100];//player's id, 0-folder
    vector<int> dire[100];
    int dire_tot=0;
    void mkdir(int idx)
    {
        dire[idx].push_back(++dire_tot);
        type[dire_tot]=0;
    }
    void echo(int idx,int player_id)
    {
        dire[idx].push_back(++dire_tot);
        type[dire_tot]=player_id;
    }
    void rm(int idx,bool sudo)
    {

    }
    void mv(int idxs,int idxe)
    {
        
    }
    void print(int player_id)
    {
        cout<<"当前目录: "<<endl;
        cout<<"Home"<<endl;
        for(int i=1;i<=4;i++)
        {
            if(i==4)
            {
                cout<<"  └player"<<i<<endl;
            }
            else
            {
                cout<<"  ├player"<<i<<endl;
            }
            if(i==player_id)
            {
                queue<node> q;
                for(int j=0;j<dire[player_id].size();j++)
                {
                    q.push({dire[player_id][j],1});
                }
                while(!q.empty())
                {
                    node t=q.front();
                    int now=t.id,dep=t.dep;
                    q.pop();
                    for(int j=0;j<dep;j++)
                        cout<<"  |";
                    cout<<"  ├";
                    if(type[now])
                    {
                        cout<<"file"<<type[now]<<endl;
                    }
                    else
                    {
                        cout<<"folder"<<now<<endl;
                        for(int j=0;j<dire[now].size();j++)
                        {
                            q.push({dire[now][j],dep+1});
                        }
                    }
                }
            }
            else
            {
                cout<<"  |  └***"<<endl;
            }
        }
    }
};
#endif