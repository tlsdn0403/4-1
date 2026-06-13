/*
 N개의 나라가 있다. 각 나라를 연결하는 M개의 간선(도로) 정보가 주어지며, 각각의 도로는 연결 비용이 다르다. 
 모든 도시를 최소 한 번 이상 방문하면서 최소 비용이 드는 연결망을 구축하려고 한다. 
 모든 도시가 연결되는 최소 비용을 출력하시오.

	input : 
		3 3
		1 2 1
		2 3 2
		1 3 3
	output :
		3
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
	int u, v, cost;
	// 비용 오름차순 정렬
	bool operator<(const Edge& other) const {
		return cost < other.cost;
	}
};

vector<int> parent_node;

// 유니온 파인드: Find
int findParent(int x) {
	if (x == parent_node[x]) return x;
	return parent_node[x] = findParent(parent_node[x]);
}

// 유니온 파인드: Union
void unionParent(int a, int b) {
	a = findParent(a);
	b = findParent(b);
	if (a != b) {
		if (a < b) parent_node[b] = a;
		else parent_node[a] = b;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, M;
	cin >> N >> M;

	parent_node.resize(N + 1);
	for (int i = 1; i <= N; ++i) {
		parent_node[i] = i;
	}

	vector<Edge> edges(M);
	for (int i = 0; i < M; ++i) {
		cin >> edges[i].u >> edges[i].v >> edges[i].cost;
	}

	// 1. 간선 비용 오름차순 정렬
	sort(edges.begin(), edges.end());

	int total_cost = 0;

	// 2. 비용이 작은 간선부터 사이클 확인하며 연결
	for (int i = 0; i < M; ++i) {
		if (findParent(edges[i].u) != findParent(edges[i].v)) {
			unionParent(edges[i].u, edges[i].v);
			total_cost += edges[i].cost;
		}
	}

	cout << total_cost << '\n';
}