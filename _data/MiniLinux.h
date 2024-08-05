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
    void print_dfs(int idx,int dep)
    {
        for(int i=0;i<dire[idx].size();i++)
        {
            int now=dire[idx][i];
            for(int j=1;j<=dep;j++)
                cout<<"|  ";
            if(!type[now])
            {
                if(i==dire[idx].size()-1)
                {
                    cout<<"└──folder"<<now<<endl;
                }
                else
                {
                    cout<<"├──folder"<<now<<endl;
                }
                print_dfs(now,dep+1);
            }
            else
            {
                if(i==dire[idx].size()-1)
                {
                    cout<<"└──file"<<now<<endl;
                }
                else
                {
                    cout<<"├──file"<<now<<endl;
                }
            }
        }
    }
public:
    bool type[100];//player's id, 0-folder
    vector<int> dire[100];
    int dire_tot=1;
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
                cout<<"└──player"<<i<<endl;
            }
            else
            {
                cout<<"├──player"<<i<<endl;
            }
            if(i==player_id)
            {
                print_dfs(i,1);
            }
            else
            {
                if(i==4)
                {
                    cout<<"   └──***"<<endl;
                }
                else
                {
                    cout<<"|  └──***"<<endl;
                }
            }
        }
    }
};
#endif