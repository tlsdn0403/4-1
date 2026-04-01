#include<iostream>
#include<queue>
#include<cstring>

using namespace std;
int n{}, m{};

bool visited[100001]{};

int bfs(int x) {
	queue<pair<int,int>> q;
	q.push({x,0});
	int answer{};
	while (!q.empty()) {
		int current = q.front().first;
		int distance = q.front().second;
		visited[current] = true;
		q.pop();
		if (current == m) {
			return distance;
			break;
		}

		if (current + 1 >= 0 && current + 1 < 100001 && visited[current + 1] == false) {
			q.push({ current + 1, distance + 1 });
		}
		
		if (current - 1 >= 0 && current - 1 < 100001 && visited[current - 1] == false) {
			q.push({ current - 1, distance + 1 });
		}
		
		if (current * 2 >= 0 && current * 2 < 100001 && visited[current * 2] == false) {
			q.push({ current * 2, distance + 1 });
		}

		
	}
	return 0;
}

int main() {
	cin >> n >> m;
	cout<< bfs(n);
}