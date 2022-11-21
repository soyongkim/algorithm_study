#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<string> cache;
int cacheLen, cacheMax;
int totalCost;

void hitCache(int index) {
    totalCost++;
    string target = cache[index];
    cacheLen--;
    for(int i=index; i<cacheLen-1; i++) {
        cache[i] = cache[i+1];
    }
    cache[++cacheLen] = target;
}

void missCache(string target) {
    totalCost+=5;

    if(cacheLen < cacheMax) {
        cache[cacheLen++] = target;
    } else {
        for(int i=0; i<cacheMax-1; i++) {
            cache[i] = cache[i+1];
        }
        cache[cacheLen] = target;
    }
}

void searchCache(string target) {
    bool hit = false;
    for(int i=0; i<cacheLen; i++) {
        if(target.compare(cache[i]) == 0) {
            hit = true;
            hitCache(i);
        }
    }

    if(!hit) {
        missCache(target);
    }
}

void toLower(string str) {
    for_each(str.begin(), str.end(), [](char & c) {
        c = ::tolower(c);
    });
}

int solution(int cacheSize, vector<string> cities) {
    cacheMax = cacheSize;
    cacheLen = 0;

    for(int i=0; i<cacheMax; i++) {
        cache.push_back("");
    }




    for(int i=0; i<cities.size(); i++) {
        toLower(cities[i]);
        searchCache(cities[i]);
    }

    return totalCost;
}

int main() {
    int N;
    vector<int> input, input2, answer;

    cin >> N;
    for(int i=0; i<N; i++) {
        input.push_back(0);
        cin >> input[i];
    }

    for(int i=0; i<N; i++) {
        input2.push_back(0);
        cin >> input2[i];
    }
    return 0;
}