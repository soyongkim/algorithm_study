#include <iostream>
#include <vector>
using namespace std;

typedef struct block {
    int id, state;
    block() {}
    block(int id, int state) : id(id), state(state) {}
} block;

typedef struct order {
    int t, r, c;
    order() {}
    order(int t, int r, int c) : t(t), r(r), c(c) {}
} order;

int N, score, blocks;
vector<vector<block>> map;
vector<order> orders; 


bool isMove(int r, int c) { return r >= 0 && r < 10 && c >= 0 && c < 10; }


void putBlock(order cur) {
    pair<int,int> b[2];
    b[0].first = cur.r;
    b[0].second = cur.c;

    if(cur.t == 2) {
        b[1].first = cur.r;
        b[1].second = cur.c + 1;
    } else if(cur.t == 3) {
        b[1].first = cur.r + 1;
        b[1].second = cur.c;
    }

    // blue
    int curMinB, curMinG;
    curMinB = curMinG = -1;
    for(int i=0; i<2; i++) {
        int j = 0;
        while(isMove(b[i].first, b[i].second + j) 
            && map[b[i].first][b[i].second + j].state == 0) j++;
        if(curMinB == -1 || curMinB > j) {
            curMinB = j;
        }

        j = 0;
        while(isMove(b[i].first + j, b[i].second) 
            && map[b[i].first + j][b[i].second].state == 0) j++;
        if(curMinG == -1 || curMinG > j) {
            curMinG = j;
        }

        if(cur.t == 1) break;
    }

    for(int i=0; i<2; i++) {
        map[b[i].first][b[i].second + curMinB-1].state = 1;
        map[b[i].first + curMinG-1][b[i].second].state = 1;
        if(cur.t == 1) break;
    }

    // for(int i=0; i<10; i++) {
    //     for(int j=0; j<10; j++) {
    //         cout << map[i][j].state << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;

}

void removeLine() {
    int start, end;
    start = end = 9;
    while(start >= 6) {
        int isLine = 1;
        for(int i=0; i<4; i++) {
            if(map[i][end].state == 0) {
                isLine = 0;
                break;
            }
        }

        if(isLine) {
           end--;
        } else {
            if(start != end) {
                score += (start-end);
                for(int i=start; i>=5; i--) {
                    for(int j=0; j<4; j++) {
                        map[j][i].state = map[j][i-(start-end)].state;
                    }
                }
                end = start;
            } else {
                start--;
                end--;
            }
        }
    }

    start = end = 9;
    while(start >= 6) {
        int isLine = 1;
        for(int i=0; i<4; i++) {
            if(map[end][i].state == 0) {
                isLine = 0;
                break;
            }
        }

        if(isLine) {
           end--;
        } else {
            if(start != end) {
                score += (start-end);
                for(int i=start; i>=5; i--) {
                    for(int j=0; j<4; j++) {
                        map[i][j].state = map[i-(start-end)][j].state;
                    }
                }
                end = start;
            } else {
                start--;
                end--;
            }
        }
    }
}


void weakLine() {
    // 2칸 이동
    int didMove = 0;
    for(int i=0; i<4; i++) {
        if(map[4][i].state == 1) {
            for(int j=9; j>=4; j--) {
                for(int k=0; k<4; k++) {
                    map[j][k].state = map[j-2][k].state;
                }
            }
            break;
        }
    }

    for(int i=0; i<4; i++) {
        if(map[i][4].state == 1) {
            for(int j=9; j>=4; j--) {
                for(int k=0; k<4; k++) {
                    map[k][j].state = map[k][j-2].state;
                }
            }
            break;
        }
    }


    if(!didMove) {
        for(int i=0; i<4; i++) {
            if(map[5][i].state == 1) {
                for(int j=9; j>=4; j--) {
                    for(int k=0; k<4; k++) {
                        map[j][k].state = map[j-1][k].state;
                    }
                }
                break;
            }
        }

        for(int i=0; i<4; i++) {
            if(map[i][5].state == 1) {
                for(int j=9; j>=4; j--) {
                    for(int k=0; k<4; k++) {
                        map[k][j].state = map[k][j-1].state;
                    }
                }
                break;
            }
        }
    }
}



void simulate() {
    score = blocks = 0;
    for(int i=0; i<N; i++) {
        order cur = orders[i];
        // put the block
        putBlock(cur);

        // remove line
        removeLine();

        // weak line
        weakLine();
    }

    for(int i=0; i<10; i++) {
        for(int j=0; j<10; j++) {
            if(map[i][j].state == 1) {
                blocks++;
            }
        }
    }
}

int main() {
    cin >> N;

    int id;
    for(int i=0; i<11; i++) {
        map.push_back(vector<block>());
        for(int j=0; j<11; j++) {
            map[i].push_back(block(0, 0));
        }
    }

    for(int i=0; i<N; i++) {
        order in;
        cin >> in.t >> in.r >> in.c;
        orders.push_back(in);
    }

    simulate();
    cout << score << endl << blocks << endl;
    return 0;
}