#ifndef MINILINUX_H
#define MINILINUX_H
#include <bits/stdc++.h>
using namespace std;

class directory
{
private:
    struct node
    {
        int id, dep;
    };
    void print_dfs(int idx, int dep)
    {
        for (int i = 0; i < dire[idx].size(); i++)
        {
            int now = dire[idx][i];
            for (int j = 1; j <= dep; j++)
                cout << "|  ";
            if (!type[now])
            {
                cout << (i == dire[idx].size() - 1 ? "└──" : "├──") << name[now] << endl;
                print_dfs(now, dep + 1);
            }
            else
            {
                cout << (i == dire[idx].size() - 1 ? "└──" : "├──") << name[now] << endl;
            }
        }
    }

    int dire_tot = 1;

public:
    bool type[100]; // 0-folder, player_id-file
    vector<int> dire[100];
    string name[100];

    int mkdir(int idx, const string &nam)
    {
        dire[idx].push_back(++dire_tot);
        type[dire_tot] = 0;
        name[dire_tot] = nam;
        return dire_tot;
    }

    void echo(int idx, int player_id, const string &nam)
    {
        dire[idx].push_back(++dire_tot);
        type[dire_tot] = player_id;
        name[dire_tot] = nam;
    }

    void rm(int idx, int file_idx)
    {
        if (file_idx < 0 || file_idx >= dire[idx].size())
        {
            cout << "Invalid file index." << endl;
            return;
        }
        dire[idx].erase(dire[idx].begin() + file_idx);
        cout << "File/Folder removed successfully." << endl;
    }

    void mv(int idxs, int file_idx, int idxe)
    {
        if (file_idx < 0 || file_idx >= dire[idxs].size())
        {
            cout << "Invalid file index." << endl;
            return;
        }
        int target = dire[idxs][file_idx];
        dire[idxe].push_back(target);
        dire[idxs].erase(dire[idxs].begin() + file_idx);
        cout << "File moved successfully." << endl;
    }

    void print()
    {
        cout << "当前目录: " << endl;
        print_dfs(1, 0);
    }
};

#endif