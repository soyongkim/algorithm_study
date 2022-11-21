#include <iostream>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#define MAX 300000
using namespace std;

double Answer;

int main(int argc, char** argv)
{
	int T, test_case, N;
    vector<pair<int, int>> src;
    vector<int> start;
	cin >> T;

    for(int i=0; i<MAX; i++){
        src.push_back(pair<int,int>());
        start.push_back(0);
    }

	for(test_case = 0; test_case  < T; test_case++)
	{
		Answer = 0;
        cin >> N;

        for(int i=0; i<N; i++) {
            cin >> src[i].second;
            start[i] = src[i].second;
        }

        for(int i=0; i<N; i++) {
            cin >> src[i].first;
        }

        sort(src.begin(), src.begin() + N);

        for(int i=0; i<N; i++) {
            Answer += abs(src[i].second - start[i]);
        }   

		cout << "Case #" << test_case+1 << endl;
		cout << Answer << endl;
	}

	return 0;
}