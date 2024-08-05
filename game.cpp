/*
暂定规则：
    游戏机制: 
        当你的五个文件全部被删除，视为你被淘汰。
        当你有一个文件处于别人的目录下时，你才能操作这个目录上的文件。
        当仅剩一个玩家存活时，这个玩家获胜。
    游戏流程: 
        准备阶段：每人拿四张牌，并将目录设为根目录，将每人的五个文件放至根目录。
        从 1 号玩家轮流: 
            摸牌阶段: 摸 4 张牌。
            出牌阶段: 可以出任意张牌，知道输入 0 结束。
                cd: 跳转到挡墙文件目录下任意文件夹内
                mkdir: 在当前目录创建一个文件夹
                mv: 将任意一个文件移动到当前目录
                rm: 删除当前目录下的一个文件
                echo: 重新新建你被删除的文件
                sudo: 使用 sudo rm 删除的文件不能被 echo 回来，使用 sudo 可抵消非 sudo 
            弃牌阶段: 手中只保留 你的文件个数 张牌。
 */
#include <bits/stdc++.h>
#include <windows.h>
#include "_data/MiniLinux.h"
using namespace std;

int player_sum=4;
vector<string> player_card[5];
int player_dire[5];
int dire_tot;
directory dire;

void init()//init directory
{
    for(int i=1;i<=4;i++)
    {
        dire.mkdir(1);
        for(int j=1;j<=5;j++)
        {
            dire.echo(i+1,i);
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

void play()//main
{
    while(player_sum)//if more than one player survives
    {
        for(int i=1;i<=4;i++)
        {
            while(1)
            {
                system("cls");
                wostringstream temp_massage;
                temp_massage<<L"请除 "<<i<<L" 号以外玩家背身";
                wostringstream temp_title;
                temp_title<<i<<L" 号玩家出牌阶段";
                MessageBoxW(NULL,temp_massage.str().c_str(),temp_title.str().c_str(),MB_OK);
                cout<<i<<" 号玩家的手牌: "<<endl;
                for(int j=0;j<player_card[i].size();j++)
                    cout<<"  "<<player_card[i][j]<<endl;
                dire.print(i);
                cout<<"您要打出（输入 0 结束回合）: ";
                string temp;
                cin>>temp;
                if(temp=="0")
                    break;
                if(temp=="cd")
                {
                    
                }
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