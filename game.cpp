/*
规则：
    游戏机制: 
        当你的五个文件全部被删除，视为你被淘汰。
        当你有一个文件处于别人的目录下时，你才能操作这个目录上的文件。
        当仅剩一个玩家存活时，这个玩家获胜。
    游戏流程: 
        准备阶段：每人拿四张牌，将每人的五个文件放至玩家的根目录。
        从 1 号玩家轮流: 
            摸牌阶段: 摸 4 张牌。
            出牌阶段: 可以出任意张牌
                cd: 跳转到当前文件目录下任意文件夹内
                mkdir: 在当前目录创建一个文件夹
                mv: 将任意一个文件移动到当前目录
                rm: 删除当前目录下的一个文件
                echo: 重新新建你被删除的文件
                sudo: 使用 sudo rm 删除的文件不能被 echo 回来，使用 sudo 可抵消非 sudo 命令
            弃牌阶段: 手中只保留 你的文件个数 张牌。
 */
#include <bits/stdc++.h>
#include <windows.h>
#include "_data/MiniLinux.h"
using namespace std;

const string serial_num[10]={"0","①","②","③","④","⑤","⑥","⑦","⑧","⑨"};

int player_sum=4;//player sum
list<string> player_card[5];//players' card
int player_index[5];//players' index
deque<int> player_path[5];//players' path
directory dire;// directory
int fordle_tot=0;

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
                cout<<"└──"<<dire.name[dire.dire[player_index[player_id]][i]]<<endl;
            }
            else
            {
                cout<<"├──"<<dire.name[dire.dire[player_index[player_id]][i]]<<endl;
            }
        }
        cout<<"请选择路径编号（如要后退输入..）：";
        string temp;
        cin>>temp;
        if(temp=="")
        {
            
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
            dire.print();
            while(1)
            {
                //print player's path
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