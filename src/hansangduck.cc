#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, cmin, cmax;
int dir[8][2] = { {-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1} };
vector<pair<int,int>> link;
vector<int> sorting;
vector<vector<int>> map;
vector<vector<int>> cMap;
vector<int> minV, maxV;


bool isInMap(int r, int c) { return r >= 0 && r < N && c >= 0 && c < N; }

void dfs(int r, int c) {
    cMap[r][c]++;
    for(int i=0; i<8; i++) {
        int nr = r + dir[i][0];
        int nc = c + dir[i][1];
        if(isInMap(nr, nc) && cMap[nr][nc] > 0 && cMap[nr][nc] < 2) {
            //cout << nr << " " << nc << endl;
            dfs(nr, nc);
        }
    }
}

int simulate(int min, int max) {
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            if(map[i][j] >= min && map[i][j] <= max) {
                cMap[i][j] = 1;
            } else {
                cMap[i][j] = 0;
            }
        }
    }

    dfs(link[0].first, link[0].second);

    int find = 1;
    for(int i=0; i<link.size(); i++) {
        if(cMap[link[i].first][link[i].second] != 2) {
            find = -1;
            break;
        }
    }

    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            cMap[i][j] = 0;
        }
    }

    return find;
}

int findAnswer() {
    int cand, ans;
    ans = -1;
    for(int i=0; i<minV.size(); i++) {
        if(ans != -1 && maxV[0] - minV[i] > ans) break;
        for(int j=0; j<maxV.size(); j++) {
            if((cand = simulate(minV[i], maxV[j])) > 0) {
                if(ans == -1 || ans > maxV[j] - minV[i]) {
                    ans = maxV[j] - minV[i];
                }
                break;
            }
        }
    }

    return ans;
}

int main() {
    //13:37
    cin >> N;
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            char c;
            cin >> c;
            if(c == 'P' || c == 'K') {
                link.push_back(pair<int,int>(i, j));
            }
        }
    }


    for(int i=0; i<N; i++) {
        map.push_back(vector<int>());
        cMap.push_back(vector<int>());
        for(int j=0; j<N; j++) {
            int tmp;
            cin >> tmp;
            map[i].push_back(tmp);
            cMap[i].push_back(0);
            sorting.push_back(tmp);
        }
    }

    sort(sorting.begin(), sorting.end());

    cmin = cmax = -1;
    for(int i=0; i<link.size(); i++) {
        if(cmin == -1 || cmin > map[link[i].first][link[i].second]) {
            cmin = map[link[i].first][link[i].second];
        }

        if(cmax == -1 || cmax < map[link[i].first][link[i].second]) {
            cmax = map[link[i].first][link[i].second];
        }
    }

    int prevMin, prevMax;
    prevMin = prevMax = -1;
    for(int i=0; i<sorting.size(); i++) {
        if(sorting[i] <= cmin) {
            if(prevMin != sorting[i]) {
                minV.push_back(sorting[i]);
                prevMin = sorting[i];
            }
        }

        if(sorting[i] >= cmax) {
            if(prevMax != sorting[i]) {
                maxV.push_back(sorting[i]);
                prevMax = sorting[i];
            }
        }
    }

    cout << findAnswer() << endl;
    return 0;
}