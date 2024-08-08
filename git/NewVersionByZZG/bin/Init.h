#include<bits/stdc++.h>
using namespace std;

void CardInit(vector<string >&card) {
    ifstream input("./_data/card.txt");
    // ofstream ouput;
    int n;
    input >> n;
    for(int i = 1; i <= n; i++) {
        int num;
        string type;
        input >> num >> type;
        for(int i = 1; i <= num; i++) {
            card.push_back(type);
        }
    }
}