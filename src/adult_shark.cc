#include <iostream>
#include <vector>
using namespace std;

typedef struct shark {
    int r, c, d;
    int** pri;
    shark() {}
    shark(int r, int c, int** pri) : r(r), c(c), pri(pri) {}
} shark;

typedef struct block {
    int who, smell, time;
    block() {}
    block(int who, int smell, int time) : who(who), smell(smell), time(time) {} 
} block;

vector<shark> sharks;
vector<vector<block>> map;
int N, M, k;
int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };


int simulate() {
    int ans = 0;
    while(ans >= 1000) {
        ans++;
        // 남은 시간 17분: 1초 동시 처리필요
        // 맵을 매초 새로 그리든, 아니면 상어에 상태를 표시하든 해야할듯

    }



    return ans > 1000? -1 : ans;
}



int main() {
    cin >> N >> M >> k;

    for(int i=0; i<=M; i++) {
        sharks.push_back(shark());
    }

    for(int i=0; i<N; i++) {
        map.push_back(vector<block>());
        for(int j=0; j<N; j++) {
            int who;
            cin >> who;
            map[i].push_back(block(who, 0, 0));

            if(who > 0) {
                sharks[who].r = i;
                sharks[who].c = j;
            }
        }
    }

    for(int i=1; i<=M; i++) {
        cin >> sharks[i].d;
    }


    int** pri;
    for(int i=1; i<=M; i++) {
        pri = new int*[4];
        for(int j=0; j<4; j++) {
            pri[j] = new int[4];
            for(int k=0; k<4; k++) {
                cin >> pri[j][k];
                pri[j][k]--; 
            }
        }
        sharks[i].pri = pri;
    }

    cout << simulate() << endl;
    return 0;
}