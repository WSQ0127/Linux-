/*
暂定规则：
    游戏机制: 
        当你的五个文件全部被删除，视为你被淘汰
        你只能看到你自己的目录结构以及有你文件的目录结构
    游戏流程: 
        准备阶段：每人拿四张牌，并将目录设为根目录，将每人的五个文件放至根目录。
        出牌阶段：从1号玩家开始轮流出牌，每回合摸3张牌
            cd: 跳转到挡墙文件目录下任意文件夹内
            mkdir: 在当前目录创建一个文件夹
            mv: 将任意一个文件移动到当前目录
            rm: 删除当前目录下的一个文件
            echo: 重新新建你被删除的文件
            sudo: 使用 sudo rm 删除的文件不能被 echo 回来
 */
#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

int player_sum=4;

void init()//init directory
{
    
}

void dispense()//dispense card
{
    for(int i=1;i<=4;i++)
    {
        ifstream infile("_data/_card.txt");
        ostringstream player_file_name;
        player_file_name<<"_data/player/player"<<i<<"_card.txt";
        ofstream outfile(player_file_name.str());
        for(int i=1;i<=4;i++)
        {
            string temp;
            int n,m;
            infile>>n>>m;
            int id=rand()%(m+1)+1;
            for(int j=1;j<=n;j++)
            {
                int l,r;
                string name;
                infile>>l>>r>>name;
                if(l<=id&&id<=r)
                    outfile<<name<<endl;
            }
            infile.seekg(0,std::ios::beg);
        }
        infile.close();
        outfile.close();
    }
}

void dire_print()//print directory
{

}

void cd()
{
    
}

void play()//main
{
    while(player_sum)//if ore than one player survives
    {
        for(int i=1;i<=4;i++)
        {
            wostringstream temp_massage;
            temp_massage<<L"请除 "<<i<<L" 号以外玩家背身";
            wostringstream temp_title;
            temp_title<<i<<L" 号玩家出牌阶段";
            MessageBoxW(NULL,temp_massage.str().c_str(),temp_title.str().c_str(),MB_OK);
            cout<<i<<" 号玩家的手牌: "<<endl;
            ostringstream player_file_name;
            player_file_name<<"_data/player/player"<<i<<"_card.txt";
            ifstream infile(player_file_name.str());
            string temp;
            string card[10];
            int tot=0;
            while(getline(infile,temp))
            {
                card[++tot]=temp;
                cout<<"\t"<<temp<<endl;
            }
            while(1)
            {
                system("cls");
                dire_print();
                cout<<"您要打出（输入 0 结束回合）: ";
                cin>>temp;
                if(temp=="0")
                    break;
                if(temp=="cd")
                {
                    cd();
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