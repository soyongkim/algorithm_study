#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, M, ans;
int map[50][50];
int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

typedef struct state {
    int r, c, t;
    state() {}
    state(int r, int c ,int t) : r(r), c(c), t(t) {}
} state;

vector<pair<int,int>> virus;

bool inMap(int r, int c) { return r >= 0 && r < N && c >=0 && c < N; }

void simulate(vector<int> picked) {
    int copyMap[N][N];
    int clean = 0;
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            copyMap[i][j] = map[i][j];
            if(copyMap[i][j] == 0) {
                clean++;
            }
        }
    }

    if(clean == 0) {
        ans = 0;
        return;
    }

    queue<state> q;
    for(int i=0; i<M; i++) {
        q.push(state(virus[picked[i]].first, virus[picked[i]].second, 0));
        copyMap[q.front().r][q.front().c] = 3;
    }

    while(!q.empty()) {
        state cur = q.front(); q.pop();
        //cout << cur.t << " ";
        if(cur.t >= ans && ans != -1) {
            break;
        }

        //copyMap[cur.r][cur.c] = (cur.t)+5;
        for(int i=0; i<4; i++) {
            int nr = cur.r + dir[i][0];
            int nc = cur.c + dir[i][1];

            if(inMap(nr, nc)) {
                if(copyMap[nr][nc] == 0 || copyMap[nr][nc] == 2) {
                    if(copyMap[nr][nc] == 0) {
                        if(--clean == 0) {
                            if(cur.t+1 < ans || ans == -1) {
                                ans = cur.t+1;
                            }
                            return;
                        }
                    }
                    copyMap[nr][nc] = 3;
                    q.push(state(nr, nc, (cur.t)+1));
                }
            }
        }
    }
}

void dfs(vector<int> picked, int curPick) {
    if(picked.size() == M) {
        simulate(picked);
        return;
    }

    for(int i=curPick; i<virus.size(); i++) {
        picked.push_back(i);
        dfs(picked, i+1);
        picked.pop_back();
    }
}


int main() {
    cin >> N >> M;
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            cin >> map[i][j];
            if(map[i][j] == 2) {
                virus.push_back(pair<int,int>(i, j));
            }
        }
    }

    ans = -1;
    vector<int> picked;
    dfs(picked, 0);
    cout << ans << endl;

    return 0;
}