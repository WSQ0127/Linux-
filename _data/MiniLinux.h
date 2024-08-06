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
                    cout<<"└──"<<name[now]<<endl;
                }
                else
                {
                    cout<<"├──"<<name[now]<<endl;
                }
                print_dfs(now,dep+1);
            }
            else
            {
                if(i==dire[idx].size()-1)
                {
                    cout<<"└──"<<name[now]<<endl;
                }
                else
                {
                    cout<<"├──"<<name[now]<<endl;
                }
            }
        }
    }
    int dire_tot=1;
public:
    bool type[100];//player's id, 0-folder
    vector<int> dire[100];
    string name[100];
    int mkdir(int idx,string nam)
    {
        dire[idx].push_back(++dire_tot);
        type[dire_tot]=0;
        name[dire_tot]=nam;
        return dire_tot;
    }
    void echo(int idx,int player_id,string nam)
    {
        dire[idx].push_back(++dire_tot);
        type[dire_tot]=player_id;
        name[dire_tot]=nam;
    }
    void rm(int idx,bool sudo)
    {

    }
    void mv(int idxs,int idxe)
    {
        
    }
    void print()
    {
        cout<<"当前目录: "<<endl;
        print_dfs(1,0);
    }
};
#endif