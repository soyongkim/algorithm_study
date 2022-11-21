#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int r, c, k, ans;

void simulate(int time, int cr, int cc, int** mat) {
    if(time > 100) {
        return;
    }

    if(mat[r][c] == k) {
        if(ans == -1 || ans > time) {
            ans = time;
            return;
        }
    }

    int count[101] = { 0, };
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    if(cr >= cc) {
        // row cal
        for(int i=0; i<cr; i++) {
            for(int j=0; j<cc; j++) {
                if(mat[i][j] != 0) {
                    count[mat[i][j]]++;
                }
            }

            for(int j=1; j<=100; j++) {
                if(count[j] > 0) {
                    pq.push(pair<int,int>(count[j], j));
                    count[j] = 0;
                }
            }

            int new_cc = 0;
            while(!pq.empty()) {
                if(new_cc < 100) {
                    pair<int,int> cur = pq.top(); pq.pop();
                    mat[i][new_cc++] = cur.second;
                    mat[i][new_cc++] = cur.first;
                } else {
                    pq.pop();
                }
            }

            for(int z=new_cc; z<100; z++) {
                if(mat[i][z] > 0) mat[i][z] = 0;
            }

            if(cc < new_cc) {
                cc = new_cc;
            }
        }
    } else {
        // col cal
        for(int i=0; i<cc; i++) {
            for(int j=0; j<cr; j++) {
                if(mat[j][i] != 0) {
                    count[mat[j][i]]++;
                }
            }

            for(int j=1; j<=100; j++) {
                if(count[j] > 0) {
                    pq.push(pair<int,int>(count[j], j));
                    count[j] = 0;
                }
            }

            int new_cr = 0;
            while(!pq.empty()) {
                if(new_cr < 100) {
                    pair<int,int> cur = pq.top(); pq.pop();
                    mat[new_cr++][i] = cur.second;
                    mat[new_cr++][i] = cur.first;
                } else {
                    pq.pop();
                }
            }

            for(int z=new_cr; z<100; z++) {
                if(mat[z][i] > 0) mat[z][i] = 0;
            }

            if(cr < new_cr) {
                cr = new_cr;
            }
        }

    }

    // for(int i=0; i<cr; i++) {
    //     for(int j=0; j<cc; j++) {
    //         cout << mat[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;

    simulate(time+1, cr, cc, mat);
}


int main() {
    cin >> r >> c >> k;
    r--; c--;
    int** mat = new int*[100];
    for(int i=0; i<100; i++) {
        mat[i] = new int[100]{};
    }

    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            cin >> mat[i][j]; 
        }
    }

    ans = -1;
    simulate(0, 3, 3, mat);
    cout << ans << endl;

    for(int i=0; i<100; i++) {
        delete[] mat[i];
    }
    delete[] mat;

    return 0;
}