#include <bits/stdc++.h>
#include <windows.h>
#include "bin/MiniLinux.h"
using namespace std;

const string serial_num[10]={"0","①","②","③","④","⑤","⑥","⑦","⑧","⑨"};

int player_sum=4;//player sum
list<string> player_card[5];//players' card
int player_index[5];//players' index
deque<int> player_path[5];//players' path
directory dire;// directory
int folder_tot=0;

void init()//init directory
{
    dire.name[1]="Home";
    for(int i=1;i<=4;i++)
    {
        string temp;temp="player";temp+='0'+i;
        cout<<temp<<endl;
        int id=dire.mkdir(1,temp);//players' fordle
        player_index[i]=id;
        player_path[i].push_back(1);
        player_path[i].push_back(id);
    }
    for(int i=1;i<=4;i++)
    {
        for(int j=1;j<=5;j++)
        {
            string temp;
            temp+="player";temp+=(char)('0'+i);temp+="_file";temp+=('0'+j);
            dire.echo(i+1,i,temp);//players' file
        }
    }
}

void dispense()//dispense card
{
    for(int i=1;i<=4;i++)
    {
        ifstream infile("_data/_card.txt");
        for(int i=1;i<=4;i++)
        {
            int n,m;
            infile>>n>>m;
            int id=rand()%(m+1)+1;
            for(int j=1;j<=n;j++)
            {
                int l,r;
                string name;
                infile>>l>>r>>name;
                if(l<=id&&id<=r)
                    player_card[i].push_back(name);
            }
            infile.seekg(0,std::ios::beg);
        }
        infile.close();
    }
}

void cd(int player_id)
{
    auto t=find(player_card[player_id].begin(),player_card[player_id].end(),"cd");
    if(t!=player_card[player_id].end())
    {
        player_card[player_id].erase(t);
        cout<<dire.name[player_index[player_id]]<<endl;
        for(int i=0;i<dire.dire[player_index[player_id]].size();i++)
        {
            if(i==dire.dire[player_index[player_id]].size()-1)
            {
                cout<<"└──"<<serial_num[i+1]<<dire.name[dire.dire[player_index[player_id]][i]]<<endl;
            }
            else
            {
                cout<<"├──"<<serial_num[i+1]<<dire.name[dire.dire[player_index[player_id]][i]]<<endl;
            }
        }
        while(1)
        {
            cout<<"请选择路径编号（如要后退输入..）：";
            string temp;
            cin>>temp;
            if(temp=="..")
            {
                player_path[player_id].pop_back();
                break;
            }
            int folder_id=temp[0]-'0';
            if(folder_id>dire.dire[player_index[player_id]].size())
            {
                wostringstream temp_massage;
                temp_massage<<L"没有这个路径哦";
                wostringstream temp_title;
                temp_title<<player_id<<L" 号玩家出牌阶段";
                MessageBoxW(NULL,temp_massage.str().c_str(),temp_title.str().c_str(),MB_OK);
            }
            player_path[player_id].push_back(dire.dire[player_index[player_id]][folder_id-1]);
            player_index[player_id]=dire.dire[player_index[player_id]][folder_id-1];
            break;
        }
    }
    else
    {
        wostringstream temp_massage;
        temp_massage<<L"您没有 cd 这张牌哦";
        wostringstream temp_title;
        temp_title<<player_id<<L" 号玩家出牌阶段";
        MessageBoxW(NULL,temp_massage.str().c_str(),temp_title.str().c_str(),MB_OK);
    }
}

void mkdir(int player_id)
{
    auto t=find(player_card[player_id].begin(),player_card[player_id].end(),"mkdir");
    if(t!=player_card[player_id].end())
    {
        player_card[player_id].erase(t);
        string temp="foldler";temp+='0'+(++folder_tot);
        dire.mkdir(player_index[player_id],temp);
    }
    else
    {
        wostringstream temp_massage;
        temp_massage<<L"您没有 mkdir 这张牌哦";
        wostringstream temp_title;
        temp_title<<player_id<<L" 号玩家出牌阶段";
        MessageBoxW(NULL,temp_massage.str().c_str(),temp_title.str().c_str(),MB_OK);
    }
}

void play()//main
{
    while(player_sum)//if more than one player survives
    {
        for(int i=1;i<=4;i++)
        {
            system("cls");//clean the screen
            //pop up window
            wostringstream temp_massage;
            temp_massage<<L"请除 "<<i<<L" 号以外玩家背身";
            wostringstream temp_title;
            temp_title<<i<<L" 号玩家出牌阶段";
            MessageBoxW(NULL,temp_massage.str().c_str(),temp_title.str().c_str(),MB_OK);
            while(1)
            {
                //print player's path
                dire.print();
                cout<<i<<" 号玩家当前路径: "<<endl;
                cout<<"Home";
                for(int j=1;j<player_path[i].size();j++)
                    cout<<"/"<<dire.name[player_path[i][j]];
                cout<<endl;
                //print player's card
                cout<<i<<" 号玩家的手牌: "<<endl;
                for(auto j=player_card[i].begin();j!=player_card[i].end();j++)
                    cout<<"  "<<*j<<endl;
                    
                //play a hand
                cout<<"您要打出（输入 0 结束回合）: ";
                wstring temp;
                wcin>>temp;
                if(temp==L"0")
                    break;
                if(temp==L"cd")
                    cd(i); 
                if(temp==L"mkdir")
                    mkdir(i);    
            }
        }
    }
}

int main()
{
    system("chcp 65001");
    srand(time(0));
    init();
    dispense();
    play();
    return 0;
}