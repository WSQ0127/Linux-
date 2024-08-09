#include <bits/stdc++.h>
#include <windows.h>
#include "bin/MiniLinux.h"
#include "bin/Players.h"
using namespace std;

int player_sum=4;//player sum
directory dire;// directory
Player players[5];

void init()//init directory
{
    dire.name[1]="Home";
    for(int i=1;i<=4;i++)
    {
        players[i]=Player(i,dire);
    }
}

void dispense()//dispense card
{
    ifstream infile("_data/_card.txt");
    for(int i=1;i<=4;i++)
    {
        players[i].load_cards(infile,5);
        infile.seekg(0,std::ios::beg);
    }
    infile.close();
}

void play()//main
{
    while(player_sum)//if more than one player survives
    {
        for(int player_id=1;player_id<=4;player_id++)
        {
            system("cls");//clean the screen
            wostringstream temp_massage;
            temp_massage<<L"请除 "<<player_id<<L" 号以外玩家背身";
            wostringstream temp_title;
            temp_title<<player_id<<L" 号玩家出牌阶段";
            MessageBoxW(NULL,temp_massage.str().c_str(),temp_title.str().c_str(),MB_OK);
            Player& player=players[player_id];
            while(1)
            {
                player.display(dire);
                cout<<"您要打出（输入 0 结束回合）: ";
                wstring temp;
                wcin>>temp;
                if(temp==L"0")
                    break;
                if(temp==L"cd")
                    player.cd(dire);
                if(temp==L"mkdir")
                    player.mkdir(dire);
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
