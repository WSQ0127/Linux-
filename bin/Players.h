#ifndef Players_H
#define Players_H
#include <windows.h>
#include <bits/stdc++.h>
#include "MiniLinux.h"
using namespace std;

const string serial_num[10]={"0","①","②","③","④","⑤","⑥","⑦","⑧","⑨"};

class Player
{
private:
    int id;
    int current_index;
    int folder_tot=0;
    list<string> cards;
    deque<int> path;
    void player_init_directory(directory dire)
    {
        string temp="player";
        temp+='0'+id;
        cout<<temp<<endl;
        current_index=dire.mkdir(1,temp);
        path.push_back(1);
        path.push_back(current_index);
    }
    void player_init_files(directory dire)
    {
        for(int j=1;j<=5;j++)
        {
            string temp;
            temp+="player";
            temp+=to_string(id);
            temp+="_file";
            temp+=('0'+j);
            dire.echo(id+1,id,temp);
        }
    }
public:
    Player(){}
    Player(int _id,directory dire)
    {
        id=_id;
        player_init_directory(dire);
        player_init_files(dire);
    }
    void display_current_directory(directory dire)
    {
        cout<<dire.name[current_index]<<endl;
        for(int i=0;i<dire.dire[current_index].size();i++)
        {
            if(i==dire.dire[current_index].size()-1)
            {
                cout<<"└──"<<serial_num[i+1]<<dire.name[dire.dire[current_index][i]]<<endl;
            }
            else
            {
                cout<<"├──"<<serial_num[i+1]<<dire.name[dire.dire[current_index][i]]<<endl;
            }
        }
    }
    void load_cards(int num)
    {
        ifstream infile("_data/_card.txt");
        for(int i=1;i<=num;i++)
        {
            int n,m;
            infile>>n>>m;
            int temp=rand()%(m+1)+1;
            for(int j=1;j<=n;j++)
            {
                int l,r;
                string name;
                infile>>l>>r>>name;
                if(l<=temp&&temp<=r)
                {
                    cards.push_back(name);
                    break;
                }
            }
            infile.seekg(0,ios::beg);
        }
        infile.close();
    }
    void display(directory dire)
    {
        dire.print();
        cout<<id<<" 号玩家当前路径: "<<endl;
        cout<<"Home";
        for(int j=1;j<path.size();j++)
        {
            cout<<"/"<<dire.name[path[j]];
        }
        cout<<endl;

        cout<<id<<" 号玩家的手牌: "<<endl;
        for(auto j=cards.begin();j!=cards.end();j++)
        {
            cout<<"  "<<*j<<endl;
        }
    }
    //card
    void cd(directory dire)
    {
        auto t=find(cards.begin(),cards.end(),"cd");
        if(t!=cards.end())
        {
            cards.erase(t);
            display_current_directory(dire);
            while(1)
            {
                cout<<"请选择路径编号（如要后退输入..）：";
                string temp;
                cin>>temp;
                if(temp=="..")
                {
                    path.pop_back();
                    break;
                }
                int folder_id=temp[0]-'0';
                if(folder_id>dire.dire[current_index].size())
                {
                    wostringstream temp_massage;
                    temp_massage<<L"没有这个路径哦";
                    wostringstream temp_title;
                    temp_title<<id<<L" 号玩家出牌阶段";
                    MessageBoxW(NULL,temp_massage.str().c_str(),temp_title.str().c_str(),MB_OK);
                }
                path.push_back(dire.dire[current_index][folder_id-1]);
                current_index=dire.dire[current_index][folder_id-1];
                break;
            }
        }
        else
        {
            wostringstream temp_massage;
            temp_massage<<L"您没有 cd 这张牌哦";
            wostringstream temp_title;
            temp_title<<id<<L" 号玩家出牌阶段";
            MessageBoxW(NULL,temp_massage.str().c_str(),temp_title.str().c_str(),MB_OK);
        }
    }

    void mkdir(directory dire)
    {
        auto t=find(cards.begin(),cards.end(),"mkdir");
        if(t!=cards.end())
        {
            cards.erase(t);
            string temp="folder";
            temp+='0'+(++folder_tot);
            dire.mkdir(current_index,temp);
        }
        else
        {
            wostringstream temp_massage;
            temp_massage<<L"您没有 mkdir 这张牌哦";
            wostringstream temp_title;
            temp_title<<id<<L" 号玩家出牌阶段";
            MessageBoxW(NULL,temp_massage.str().c_str(),temp_title.str().c_str(),MB_OK);
        }
    }
};
#endif