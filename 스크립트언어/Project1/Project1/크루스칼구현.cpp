//
//  7 9
// 1 2 29
// 1 5 75
// 2 6 34
// 5 6 53
// 2 3 35
// 3 4 7
// 4 6 23
// 6 7 25
//4 7 13
//


#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


int v, e;
int parent[100001];

vector<pair<int, pair<int, int>>> edges; // 간선 정보 저장 (가중치, (노드1, 노드2))

int findParent(int x) {
    if (x == parent[x]) return x;
    // 찾아서 얻은 루트노드를 현재 부모테이블 값으로 갱신하다. 각각의 루트노드가 들어가도록 갱신
    return parent[x] = findParent(parent[x]);
}

void unionParent(int a, int b) {
    a = findParent(a);
    b = findParent(b);

    if (a < b) parent[b] = a;
    else parent[a] = b;
}


bool findCycle(int a, int b) {
    a = findParent(a);
    b = findParent(b);
    if (a == b) return true;
    return false;
}

int main() {
    cin >> v >> e;
    // 부모 테이블 초기화
    for (int i = 1; i <= v; i++) {
        parent[i] = i;
    }

    for (int i = 0; i < e; i++) {
        int a, b, cost;
        cin >> a >> b >> cost;
        edges.push_back({cost, {a, b}});
    }

	sort(edges.begin(), edges.end()); // 가중치 기준 정렬

    int result{};
    for (int i = 0; i < edges.size(); ++i) {
        int cost = edges[i].first;
        int a = edges[i].second.first;
        int b = edges[i].second.second;
        
        if (!findCycle(a, b)) {
            unionParent(a, b);
            result += cost;
        }
    }
    cout << result;
}