#include <iostream>
#include <vector>

using namespace std;

typedef struct room {
    int color;
    vector<int> stack;
    room() {}
    room(int color) : color(color) {}
} room;

int N, K, ans;
vector<vector<room>> map;
vector<pair<int, pair<int,int>>> horses;
int dir[4][2] = { {0, 1}, {0, -1}, {-1, 0}, {1, 0} };


bool isInMap(int r, int c) { return r >=0 && r < N && c >= 0 && c < N; }

void simulate() {
    ans = -1;
    for(int i=0; i<1000; i++) {
        for(int j=0; j<K; j++) {
            int nr = horses[i].second.first + dir[horses[i].first][0];
            int nc = horses[i].second.second + dir[horses[i].first][0];

            if(isInMap(nr, nc)) {
                
            }

            int color = map[nr][nc].color;
            switch (color) {
            case 0:
                
                break;
            case 1:
                break;
            case 2:
                break;
            }
        }
    }
}


int main() {
    cin >> N >> K;

    for(int i=0; i<N; i++) {
        map.push_back(vector<room>());
        for(int j=0; j<N; j++) {
            room cur;
            cin >> cur.color;
            
            map[i].push_back(cur);
        }
    }

    int r, c, d;
    for(int i=0; i<K; i++) {
        cin >> r >> c >> d;
        map[r-1][c-1].stack.push_back(i);
        horses.push_back(pair<int,pair<int,int>>(d-1, pair<int,int>(r-1, c-1))); 
    }

    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            cout << map[i][j].color << " ";
        }
        cout << endl;
    }
    cout << endl;



    return 0;
}