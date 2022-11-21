#include <iostream>
#include <vector>
#define MAX 100000
using namespace std;

int N;
int stair[MAX][3];
int dir[3][2] = {{-1, -1}, {-1, 0}, {-1, 1}};

int main() {
    cin >> N;
    for(int i=0; i<N; i++) {
        for(int j=0; j<3; j++) {
            cin >> stair[i][j];
        }
    }


    int maxA[3][2];
    int minA[3][2];
    for(int i=0; i<3; i++) {
        maxA[i][0] = stair[0][i];
        minA[i][0] = stair[0][i];
    }

    int toggle = 0;
    for(int i=1; i<N; i++) {
        for(int j=0; j<3; j++) {
            int curMax = -1;
            int curMin = -1;
            for(int d=0; d<3; d++) {
                if(j + dir[d][1] >= 0 && j + dir[d][1] < 3) {
                    if (curMax == -1 || maxA[j + dir[d][1]][toggle] > curMax) {
                        curMax = maxA[j + dir[d][1]][toggle];
                    }
                    if (curMin == -1 || minA[j + dir[d][1]][toggle] < curMin) {
                        curMin = minA[j + dir[d][1]][toggle];
                    }
                }
            }
            maxA[j][!toggle] = curMax + stair[i][j];
            minA[j][!toggle] = curMin + stair[i][j];

            //cout << minA[0][toggle] << " " << minA[1][toggle] << " " << minA[2][toggle] << endl;
        }
        toggle = !toggle;
        //cout << minA[0][toggle] << " " << minA[1][toggle] << " " << minA[2][toggle] << endl;
    }

    int max = maxA[0][toggle] > maxA[1][toggle] ? maxA[0][toggle] : maxA[1][toggle];
    if(max < maxA[2][toggle]) max = maxA[2][toggle];

    int min = minA[0][toggle] < minA[1][toggle] ? minA[0][toggle] : minA[1][toggle];
    if(min > minA[2][toggle]) min = minA[2][toggle]; 
    
    cout << max << " " << min << endl;
    return 0;
}