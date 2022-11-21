#include <iostream>
#include <vector>

using namespace std;

int R,C,T;
vector<pair<int,int>> cleaner;
int map[2][1000][1000];

int Ans, phase;
int ccw[4][2] = { {-1,0}, {0,1}, {1,0}, {0,-1} };
int cw[4][2] = { {1,0}, {0,1}, {-1,0}, {0,-1} };


bool canSpread(int r, int c) {
    return r >= 0 && r < R && c >= 0 && c < C;
}

bool locationCleaner(int r, int c) {
    return r == cleaner[0].first && c == cleaner[0].second
        || r == cleaner[1].first && c == cleaner[1].second;
}


void switchPhase() {
    if(phase) 
        phase = 0;
    else
        phase = 1;
}

void printm() {
    cout << endl;
    for(int i=0; i<R; i++) {
        for(int j=0; j<C; j++) {
            cout << map[!phase][i][j] << " ";
        }
        cout << endl;
    }
}

void simulate() {
    switchPhase();

    // 확산
    for(int i=0; i<R; i++) {
        for(int j=0; j<C; j++) {
            if(map[phase][i][j] != 0) {
                int spreadValue = (map[phase][i][j])/5;
                for(int k=0; k<4; k++) {
                    if(canSpread(i + ccw[k][0], j + ccw[k][1]) && 
                       !locationCleaner(i + ccw[k][0], j + ccw[k][1])) {
                        map[!phase][i + ccw[k][0]][j + ccw[k][1]] 
                            += spreadValue;
                        map[phase][i][j] -= spreadValue;
                    }
                }
                map[!phase][i][j] += map[phase][i][j];
            }
        }
    }

    //printm();

    // 회전(위): 반시계   
    pair<int,int> cur = cleaner[0];
    cur.first += ccw[0][0];
    map[!phase][cur.first][cur.second] = 0;

    for(int i=0; i<4; i++) {
        while(canSpread(cur.first + ccw[i][0], cur.second + ccw[i][1]) &&
              !locationCleaner(cur.first + ccw[i][0], cur.second + ccw[i][1]) &&
              cur.first + ccw[i][0] <= cleaner[0].first) {
            map[!phase][cur.first][cur.second] 
                = map[!phase][cur.first + ccw[i][0]][cur.second + ccw[i][1]];
            map[!phase][cur.first + ccw[i][0]][cur.second + ccw[i][1]] = 0;
            cur.first += ccw[i][0];
            cur.second += ccw[i][1];
            //cout << i << ", " << cur.first << ", " << cur.second << endl;
        }
    }

    //printm();

    // 회전(아래): 시계
    cur = cleaner[1];
    cur.first += cw[0][0];
    map[!phase][cur.first][cur.second] = 0;

    for(int i=0; i<4; i++) {
        while(canSpread(cur.first + cw[i][0], cur.second + cw[i][1]) &&
              !locationCleaner(cur.first + cw[i][0], cur.second + cw[i][1]) &&
              cur.first + cw[i][0] >= cleaner[1].first) {
            map[!phase][cur.first][cur.second] 
                = map[!phase][cur.first + cw[i][0]][cur.second + cw[i][1]];
            map[!phase][cur.first + cw[i][0]][cur.second + cw[i][1]] = 0;
            cur.first += cw[i][0];
            cur.second += cw[i][1];
        }
    }

    //printm();

    for(int i=0; i<R; i++) {
        for(int j=0; j<C; j++) {
            map[phase][i][j] = 0;
        }
    }
}




int main() {
    cin >> R >> C >> T;

    for(int i=0; i<R; i++) {
        for(int j=0; j<C; j++) {
            cin >> map[0][i][j];
            if(map[0][i][j] == -1) {
                cleaner.push_back(pair<int,int>(i, j));
            }
        }
    }

    phase = 1;
    for(int i=0; i<T; i++) {
        simulate();
    }


    for(int i=0; i<R; i++) {
        for(int j=0; j<C; j++) {
            if(map[!phase][i][j] > 0)
                Ans += map[!phase][i][j];
        }
    }

    cout << Ans << endl;
    return 0;
}