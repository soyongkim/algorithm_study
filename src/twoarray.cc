#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> A, B;
priority_queue<long long> pqA;
priority_queue<long long, vector<long long>, greater<long long>> pqB;
int n, m, T;


long long simulate() {
    long long curSum;
    for(int i=0; i<n; i++) {
        curSum = 0;
        for(int j=i; j<n; j++) {
            curSum += A[j];
            pqA.push(curSum);
        }
    }

    for(int i=0; i<m; i++) {
        curSum = 0;
        for(int j=i; j<m; j++) {
            curSum += B[j];
            pqB.push(curSum);
        }
    }

    long long curA, curB, minA, minB, ans;
    ans = 0;
    while(!pqA.empty() && !pqB.empty()) {
        curA = pqA.top();
        curB = pqB.top();

        if(curA+curB < T) {
            pqB.pop();
        } else if(curA+curB > T) {
            pqA.pop();
        } else {
            minA = minB = 0;
            while(!pqA.empty() && curA == pqA.top()) {
                pqA.pop();
                minA++;
            }
            while(!pqB.empty() && curB == pqB.top()) {
                pqB.pop();
                minB++;
            }
            ans += (minA*minB);
        }
    }

    return ans;
}



int main() {
    cin >> T;
    cin >> n;
    for(int i=0; i<n; i++) {
        A.push_back(0);
        cin >> A[i];
    }

    cin >> m;
    for(int i=0; i<m; i++) {
        B.push_back(0);
        cin >> B[i];
    }


    cout << simulate() << endl;
    return 0;
}
