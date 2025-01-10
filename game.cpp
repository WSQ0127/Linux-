#include <bits/stdc++.h>
#include "bin/MiniLinux.h"
#include "bin/Players.h"
using namespace std;

void game_loop()
{
    directory dire;
    vector<Player> players;
    int player_count;

    cout << "请输入玩家数量: ";
    cin >> player_count;

    // 初始化玩家和文件系统
    for (int i = 1; i <= player_count; ++i)
    {
        players.emplace_back(i, dire);
    }
    for(int i=1;i<=player_count;i++)
        players[i].load_cards(5);
    // 游戏主循环
    int current_player_index = 0;
    while (true)
    {
        Player &current_player = players[current_player_index];

        cout << "\n当前轮到玩家 " << current_player_index + 1 << "\n";
        current_player.display_game_progress(dire);
        current_player.display_cards();

        string chosen_card;
        cout << "请选择要出的牌（输入 skip 表示跳过本回合）：";
        cin >> chosen_card;

        if (chosen_card == "skip")
        {
            cout << "玩家 " << current_player_index + 1 << " 跳过了本回合。\n";
        }
        else if (!current_player.play_card(chosen_card, dire))
        {
            cout << "无效操作，本回合结束。\n";
        }

        current_player.discard_excess_cards();

        // 检查玩家是否被淘汰
        if (current_player.is_eliminated())
        {
            cout << "玩家 " << current_player_index + 1 << " 已被淘汰！\n";
            players.erase(players.begin() + current_player_index);
            if (players.size() == 1)
            {
                cout << "游戏结束，玩家 " << players[0].get_id() << " 获胜！\n";
                break;
            }
            continue; // 当前玩家已被淘汰，跳到下一个玩家
        }

        // 切换到下一个玩家
        current_player_index = (current_player_index + 1) % players.size();
    }
}

int main()
{
    system("chcp 65001");
    srand(time(0));
    game_loop();
    return 0;
}