#include <iostream>
#include <vector>
#include <random>
#include <stdlib.h>
#include <time.h>

using namespace std;
vector<pair<int,int>> entry;

void Combination(vector<int> arr, vector<int> comb, int r, int index, int depth)
{
    if (r == 0)
    {
        pair<int,int> duel;
        duel.first = comb[0];
        duel.second = comb[1];
        entry.push_back(duel);
    }
    else if (depth == arr.size())  // depth == n // 계속 안뽑다가 r 개를 채우지 못한 경우는 이 곳에 걸려야 한다.
    {
        return;
    }
    else
    {
        // arr[depth] 를 뽑은 경우
        comb[index] = arr[depth];
        Combination(arr, comb, r - 1, index + 1, depth + 1);
        
        // arr[depth] 를 뽑지 않은 경우
        Combination(arr, comb, r, index, depth + 1);
    }
}

int main()
{
    srand(time(NULL));
    int num;
    cout << "Insert Participants number: ";
    cin >> num;

    vector<int> member;
    for(int i=1; i<=num; i++) {
        member.push_back(i);
    }
    
    int r = 2;
    vector<int> comb(r);
    
    Combination(member, comb, r, 0, 0);

    bool first = true;
    int visit[entry.size() + 1] = { 0, };
    int bd;
    while(1) {
        int d = rand()%(entry.size());
        if(visit[d] == 0) {
            if(first) {
                cout << entry[d].first << " vs " << entry[d].second << endl;
                visit[d] = 1;
                first = false;
                bd = d;
            } else {
                if(entry[bd].first == entry[d].first || entry[bd].first == entry[d].second
                    || entry[bd].second == entry[d].first || entry[bd].second == entry[d].second) {
                        continue;
                } else {
                    cout << entry[d].first << " vs " << entry[d].second << endl;
                    visit[d] = 1;
                    bd = d;
                }
            }
        }

        bool end = true;
        for (int i = 0; i < entry.size(); i++)
        {
            if (visit[i] == 0)
            {
                end = false;
                break;
            }
        }
        if (end)
        {
            break;
        }
    }
    return 0;
}