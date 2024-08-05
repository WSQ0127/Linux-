#include <bits/stdc++.h>
using namespace std;

class directory
{
public:
    bool type[100];//0:folder 1:file
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
    
};