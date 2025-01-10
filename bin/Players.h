#ifndef PLAYERS_H
#define PLAYERS_H
#include <windows.h>
#include <bits/stdc++.h>
#include "MiniLinux.h"
using namespace std;

const string serial_num[10] = {"0", "①", "②", "③", "④", "⑤", "⑥", "⑦", "⑧", "⑨"};

class Player
{
private:
    int id;
    int current_index;
    int folder_tot = 0;
    list<string> cards;
    deque<int> path;

    void player_init_directory(directory &dire)
    {
        string temp = "player";
        temp += to_string(id);
        current_index = dire.mkdir(1, temp);
        path.push_back(1);
        path.push_back(current_index);
    }

    void player_init_files(directory &dire)
    {
        for (int j = 1; j <= 5; j++)
        {
            string temp = "player" + to_string(id) + "_file" + to_string(j);
            dire.echo(current_index, id, temp);
        }
    }

public:
    Player() {}

    Player(int _id, directory &dire) {
        id = _id;
        player_init_directory(dire);
        player_init_files(dire);
    }

    int get_id() const { return id; }

    void display_current_directory(directory &dire)
    {
        cout << dire.name[current_index] << endl;
        for (int i = 0; i < dire.dire[current_index].size(); i++)
        {
            cout << (i == dire.dire[current_index].size() - 1 ? "└──" : "├──")
                 << serial_num[i + 1] << dire.name[dire.dire[current_index][i]] << endl;
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

    void display_cards()
    {
        wostringstream temp_message;
        temp_message << L"玩家 " << id << L" 的手牌: \n";
        wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        for (auto i = cards.begin(); i != cards.end(); i++)
            temp_message << L"  " << converter.from_bytes(*i);
        wostringstream temp_title;
        temp_title << L"玩家手牌";
        MessageBoxW(NULL, temp_message.str().c_str(), temp_title.str().c_str(), MB_OK);
    }

    void display_game_progress(directory &dire)
    {
        dire.print();
        cout << id << " 号玩家当前路径: Home";
        for (int j : path)
            cout << "/" << dire.name[j];
        cout << endl;
    }

    bool play_card(const string &card, directory &dire)
    {
        auto it = find(cards.begin(), cards.end(), card);
        if (it == cards.end())
        {
            cout << "您没有 " << card << " 这张牌哦。" << endl;
            return false;
        }
        cards.erase(it);
        if (card == "cd")
        {
            display_current_directory(dire);
            while (true)
            {
                cout << "请选择路径编号（如要后退输入..）：";
                string temp;
                cin >> temp;
                if (temp == ".." && path.size() > 1)
                {
                    path.pop_back();
                    current_index = path.back();
                    break;
                }
                int folder_id = stoi(temp) - 1;
                if (folder_id >= 0 && folder_id < dire.dire[current_index].size())
                {
                    path.push_back(dire.dire[current_index][folder_id]);
                    current_index = path.back();
                    break;
                }
                cout << "无效路径，请重新选择。" << endl;
            }
        }
        else if (card == "mkdir")
        {
            string temp = "folder" + to_string(++folder_tot);
            dire.mkdir(current_index, temp);
        }
        else if (card == "rm")
        {
            display_current_directory(dire);
            cout << "请输入要删除的文件编号：";
            int idx;
            cin >> idx;
            dire.rm(current_index, idx - 1);
        }
        else if (card == "mv")
        {
            display_current_directory(dire);
            cout << "请输入要移动的文件编号：";
            int idx;
            cin >> idx;
            cout << "请输入目标文件夹编号：";
            int target;
            cin >> target;
            dire.mv(current_index, idx - 1, target);
        }
        else if (card == "echo")
        {
            string temp = "player" + to_string(id) + "_file" + to_string(rand() % 100);
            dire.echo(current_index, id, temp);
        }
        else
        {
            cout << "未知的操作牌: " << card << endl;
            return false;
        }
        return true;
    }

    void discard_excess_cards()
    {
        while (cards.size() > 5)
            cards.pop_back();
    }

    bool is_eliminated() const
    {
        return cards.empty();
    }
};

#endif