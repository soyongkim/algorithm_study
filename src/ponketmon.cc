#include <vector>
#include <iostream>
#define MAX 200001
using namespace std;

int cnt[MAX];

int solution(vector<int> nums)
{
    int answer = 0;
    int cntV = 0;
    int maxV = nums.size()/2;

    for(int i=0; i<nums.size(); i++) {
        cnt[nums[i]]++;
    }

    for(int i=0; i<MAX; i++) {
        if(cnt[i] != 0) {
            cntV++;
        }
    }

    if(cntV < maxV) {
        answer = cntV;
    } else {
        answer = maxV;
    }
    return answer;
}

int main() {
    int N;
    vector<int> input;

    cin >> N;
    for(int i=0; i<N; i++) {
        input.push_back(0);
        cin >> input[i];
    }

    cout << solution(input) << endl;
    return 0;
}