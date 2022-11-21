#include <iostream>
#include <vector>
#define NULL -1

using namespace std;

typedef struct shark {
    bool live;
    int round;
    int curDir;
    int i, j;
    int preI, preJ;
    int priority[4][4];
    
    shark() {
        live = true;
        round = 0;
        preI = preJ = NULL;
    }
} shark;

typedef struct field {
    int lvl, round;
    int slvl, sk;

    field() {
        lvl = round = slvl = sk = NULL;
    }
} field;

int N, M, K;
vector<shark> sharks;
vector<vector<field>> mat;

int main() {
    cin >> N >> M >> K;

    for(int i=0; i<N; i++) {
        sharks.push_back(shark());
    }

    int tmp_lvl;
    for(int i=0; i<N; i++) {
        mat.push_back(vector<field>());
        for(int j=0; j<N; j++) {
            mat[i].push_back(field());
            cin >> tmp_lvl;
            if(tmp_lvl != 0) {
                mat[i][j].lvl = tmp_lvl-1;
                mat[i][j].round = 0;

                sharks[mat[i][j].lvl].i = i;
                sharks[mat[i][j].lvl].j = j;
            }
        }
    }

    for(int i=0; i<M; i++) {
        cin >> sharks[i].curDir;  
    }

    int tmp_dir[4];
    for(int i=0; i<M; i++) {
        for(int j=0; j<4; j++) {
            for(int k=0; k<4; k++) {
                cin >> tmp_dir[k];
                sharks[i].priority[j][k] = tmp_dir[k];
            }
        }
    }

    cout << endl;
    for(int i=0; i<M; i++) {
        cout << i << endl;
        cout << sharks[i].i << "," << sharks[i].j << endl;
        for(int j=0; j<4; j++) {
            for(int k=0; k<4; k++) {
                cout << sharks[i].priority[j][k];
            }
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}