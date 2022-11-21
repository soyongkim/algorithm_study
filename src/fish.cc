#include <iostream>
#include <vector>

using namespace std;

typedef struct shark {
    int r, c, s, d, z, live, turn;
    shark() {}
    shark(int r, int c, int s, int d, int z) : r(r-1), c(c-1), s(s), d(d-1), z(z) { live = 1; turn = 0; }
} shark;

int R, C, M, Ans;
int dir[4][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };
int map[100][100];
vector<shark> sharks;


bool isMove(int r, int c) { return r >=0 && r < R && c >=0 && c < C; }

void simulate() {
    for(int man=0; man<C; man++) {
        // 상어 잡기
        for(int down=0; down<R; down++) {
            if(map[down][man] != -1) {
                Ans += sharks[map[down][man]].z;
                sharks[map[down][man]].live = 0;
                break;
            }
        }
        //상어 이동
        for(int i=0; i<M; i++) {
            if(sharks[i].live == 1) {
                // 이동 전
                sharks[i].turn++;
                if(map[sharks[i].r][sharks[i].c] == i) {
                    // 이번 회차에 누군가 움직여서 
                    // 이 자리에 다른 상어가 존재하지 않는다면
                    map[sharks[i].r][sharks[i].c] = -1;
                }

                // 속력만큼 이동
                int mod_speed;
                if(sharks[i].d == 0 || sharks[i].d == 1) {
                    mod_speed = (sharks[i].s)%((R-1)*2);
                } else {
                    mod_speed = (sharks[i].s)%((C-1)*2);
                }

                for(int j=0; j<mod_speed; j++) {
                    if(!isMove(sharks[i].r + dir[sharks[i].d][0], 
                                sharks[i].c + dir[sharks[i].d][1])) {
                        // 방향 전환
                        switch(sharks[i].d) {
                            case 0:
                                sharks[i].d = 1;
                                break;
                            case 1:
                                sharks[i].d = 0;
                                break;
                            case 2:
                                sharks[i].d = 3;
                                break;
                            case 3:
                                sharks[i].d = 2;
                                break;
                        }
                    }
                    // 이동
                    sharks[i].r += dir[sharks[i].d][0];
                    sharks[i].c += dir[sharks[i].d][1];
                }

                // 이동 후 위치가 아무것도 없었다면
                // or 이동 후 상어가 있었는데 이전 회차였다면
                if(map[sharks[i].r][sharks[i].c] == -1 ||
                    sharks[map[sharks[i].r][sharks[i].c]].turn < sharks[i].turn) {
                    map[sharks[i].r][sharks[i].c] = i;
                } else {
                    // 이동 후 이번 턴에 이동한 상어가 있었다면
                    if(sharks[map[sharks[i].r][sharks[i].c]].z < sharks[i].z) {
                        sharks[map[sharks[i].r][sharks[i].c]].live = 0;
                        map[sharks[i].r][sharks[i].c] = i;
                    } else {
                        sharks[i].live = 0;
                    }
                }
            }
        }
    }
}

int main() {
    cin >> R >> C >> M;
    for(int i=0; i<R; i++) {
        for(int j=0; j<C; j++) {
            map[i][j] = -1;
        }
    }
    int r, c, s, d, z;
    for(int i=0; i<M; i++) {
        cin >> r >> c >> s >> d >> z;
        sharks.push_back(shark(r, c, s, d, z));
        map[sharks.back().r][sharks.back().c] = i;
    }

    simulate();

    cout << Ans << endl;
    return 0;
}