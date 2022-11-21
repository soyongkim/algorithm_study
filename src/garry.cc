#include <iostream>
#include <vector>

using namespace std;

int N, ans;
int A[21][21];


bool canBeDistance(int x, int y, int d1, int d2) {
    return x < (x + d1 + d2) && (x + d1 + d2) <= N && 
        1 <= (y - d1) && (y - d1) < y && y < (y + d2) && (y + d2) <= N;
}


void calc(int x, int y, int d1, int d2) {
    int sum[5] = { 0, };
    int B[N+1][N+1] = { 0, };

    B[x][y] = 5;
    for(int i=1; i<=d1; i++) {
        for(int j=1; j<=d2; j++) {
            //cout << x+i << " " << y-i << endl;
            B[x+i][y-i] = 5;
            //cout << x+j << " " << y+j << endl;
            B[x+j][y+j] = 5;
            B[x+d1+j][y-d1+j] = 5;
            B[x+d2+i][y+d2-i] = 5;
        }
    }

    int start, end;
    for(int i=1; i<=N; i++) {
        start = end = 0;
        for(int j=1; j<=N; j++) {
            if(B[j][i] == 5) {
                if(start == 0) {
                    start = j; 
                } else {
                    end = j;
                }
            }
        }
        if(start != 0 && end != 0) {
            for(int k=start+1; k<end; k++) {
                B[k][i] = 5;
            }
        }
    }

    for(int r=1; r<=N; r++) {
        for(int c=1; c<=N; c++) {
            if(B[r][c] == 5) {
                sum[4] += A[r][c];
                continue;
            }

            if(r < x + d1 && c <= y) {
                sum[0] += A[r][c];
                B[r][c] = 1;
            } else if(r <= x + d2 && c > y) {
                sum[1] += A[r][c];
                B[r][c] = 2;
            } else if(r >= x + d1 && c < y - d1 + d2) {
                sum[2] += A[r][c];
                B[r][c] = 3;
            } else if(r > x + d2 && c >= y - d1 + d2) {
                sum[3] += A[r][c];
                B[r][c] = 4;
            } 
        }
    }

    
    // for(int i=1; i<=N; i++) {
    //     for(int j=1; j<=N; j++) {
    //         cout << B[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;

    int max, min;
    max = min = -1;
    for(int i=0; i<5; i++) {
        if(max == -1 || max < sum[i]) {
            max = sum[i];
        }

        if(min == -1 || min > sum[i]) {
            min = sum[i];
        }
    }

    //cout << max - min << endl;
    if(ans == -1 || ans > max - min) {
        ans = max - min;
    }
}


void simulate(int x, int y) {
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=N; j++) {
            if(canBeDistance(x, y, i, j)) {
                calc(x, y, i, j);
            }
        }
    }
}


void bf() {
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=N; j++) {
            simulate(i, j);
        }
    }
}

int main() {
    cin >> N;

    for(int i=1; i<=N; i++) {
        for(int j=1; j<=N; j++) {
            cin >> A[i][j];
        }
    }


    ans = -1;
    bf();
    cout << ans << endl;

    return 0;
}