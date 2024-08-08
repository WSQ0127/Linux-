#define cls system("cls")  // define clean the screen
#include <bits/stdc++.h>   // bits
#include <windows.h>       // use some windows api
#include <random>          // random function
#include "bin/Player.h"    // Player Class
#include "bin/Init.h"      // init function
#include "bin/Directory.h" // Directory Class
using namespace std;


vector<string >cardArr;    // Cards
Player player[10];         // Players
// bool die[10];

int main() {
    system("chcp 65001");  // Set cmd can output chinese
    CardInit(cardArr);     // Init Cards
    random_shuffle(cardArr.begin(), cardArr.end());
    // random shuffle set Array to random
    for(int i = 1; i <= 4; i++) {
        player[i].GotCard(cardArr, 4);
        // 4 cards for each player when game is starting
    }
    while(1) { // while game is running
        for(int i = 1; i <= 4; i++) {
            cls;        // clean the screen 
            player[i].GotCard(cardArr, 3);
            // 3 cards for each player when game is running
            PlayerTimeStartMessage(i);
            player[i].PlayerShowCard();
            // Show their card to each player
            while(player[i].Play()) ;
            // Is it Win?
            int cnt = 0, flag = 0;
            for(int j = 1; j <= 4; j++) {
                if(player[i].isdie()) {
                    cnt++;
                }
                else {
                    flag = i;
                }
            }
            if(cnt == 3) {
                Win(flag);
                break;
            }
        }
    }
    return 0;
}