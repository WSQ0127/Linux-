#include <bits/stdc++.h>
using namespace std;

class Player {
    private:
        vector<int > filePos[5];
        vector<int > NowPos;
        vector<string >PlayerCard;
        vector<int > die;
    public:
        void Move(int id, vector<int >v) {
            filePos[id] = v;
        }
        void CDplayer(int id = -1) {
            if(id == -1) {
                NowPos.pop_back();
            }
            else {
                NowPos.push_back(id);
            }
        }
        vector<int > RetFilePos(int id) {
            return filePos[id];
        }
        vector<int > RetPlayerPos() {
            return NowPos;
        }
        void GotCard(vector<string >&card, int num) {
            for(int i = 1; i <= num; i++) {
                PlayerCard.push_back(*card.begin());
                card.push_back(*card.begin());
                card.erase(card.begin());
            }
        }
        void PlayerShowCard() {
            cout << "您手中的卡牌有：\n";
            for(auto &p : PlayerCard) {
                cout << p << "\n";
            }
        }
        bool isdie() {
            return die.size() == 5;
        }
        bool Play() {
            cls;
        }
}; 

void PlayerTimeStartMessage(int id) {
    wostringstream temp_massage;
    temp_massage << L"请除 " << id << L" 号以外玩家背身";
    wostringstream temp_title;
    temp_title << id << L" 号玩家出牌阶段";
    MessageBoxW(NULL, temp_massage.str().c_str(), temp_title.str().c_str(), MB_OK | MB_ICONINFORMATION);
}

void Win(int id) {
    wostringstream temp_massage;
    temp_massage << L"除 " << id << L" 号以外玩家全部死亡！" << id << L" 号玩家胜利！";
    wostringstream temp_title;
    temp_title << id << L" 号玩家胜利！";
    MessageBoxW(NULL, temp_massage.str().c_str(), temp_title.str().c_str(), MB_OK | MB_ICONINFORMATION);
}