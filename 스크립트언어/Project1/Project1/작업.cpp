#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<queue>
using namespace std;

//작업의 개수
int N;


vector<vector<int>> graph(10001);

int indegree[10001]{0,};
int timeTable[10001]{};
int dp[10001]{};



void topologysort(){
	
	queue<int> q;

	for(int i = 1; i <= N; i++) {
		// i번 작업의 선행작업이 없다면
		if(indegree[i] == 0) {
			q.push(i);
			dp[i] = timeTable[i];
		}
	}

	while (!q.empty()) {
		int current = q.front();
		q.pop();

		for (int i = 0; i < graph[current].size(); ++i) {
			int next = graph[current][i];

			// 모든 간선에 대해서 최대값 구해야됨
			dp[next] = max(dp[next], dp[current] + timeTable[next]);

			indegree[next]--;

			if (indegree[next] == 0) {
				q.push(next);
			}
		}
	}
}

int main(){
	cin >> N;
	for (int i = 1; i <= N; i++) {
		// 걸리는 시간 , 선행 작업 개수
		int time, num;
		cin >> time >> num;
		timeTable[i] = time;
		for(int j = 0; j < num; j++) {
			int work;
			cin >> work;
			indegree[i]++;
			graph[work].push_back(i);
		}
	}
	topologysort();
	int answer{};

	for (int i = 1; i <= N; i++) {
		answer = max(dp[i], answer);
	}
	cout << answer;
	return 0;
}