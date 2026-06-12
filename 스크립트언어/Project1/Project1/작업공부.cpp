#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

// 작업의 개수
int N{};

vector<int> works[10001];
int timeTable[10001]{};
int dp[10001]{};
void topologysort() {
	
	queue<int> q;

	
	for(int i = 1; i <= N; i++) {
		// i번 작업의 선행작업이 없다면
		if(works[i].size() == 0) {
			q.push(i);
			dp[i] = timeTable[i];
		}
	}
	while (!q.empty()) {
		int current = q.front();
		q.pop();

		for(int i = 0; i < works[current].size(); i++) {
			int next = works[current][i];
			//  모든 간선에 대해서 최대값을 구한다.
			dp[next] = max(dp[next], dp[current] + timeTable[next]);


			works[next].erase(remove(works[next].begin(), works[next].end(), current), works[next].end());
			if (works[next].size() == 0) {
				q.push(next);
			}
		}
	}

}

int main() {
	cin >> N;

	for(int i  = 0; i < N; i++) {
		//  걸리는 시간 , 선행 작업 개수
		int time, num;
		cin >> time >> num;
		timeTable[i] = time;	
		for(int j = 0; j < num; j++) {
			int work;
			cin >> work;
			works[work].push_back(i);
		}
	}


}