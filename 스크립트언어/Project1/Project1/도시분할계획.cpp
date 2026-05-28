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
        edges.push_back({ cost, {a, b} });
    }

    sort(edges.begin(), edges.end()); // 가중치 기준 정렬
    vector<pair<int, pair<int, int>>> town;
    int result{};
    for (int i = 0; i < edges.size(); ++i) {
        int cost = edges[i].first;
        int a = edges[i].second.first;
        int b = edges[i].second.second;

        if (!findCycle(a, b)) {
            unionParent(a, b); 
            // 2개의 마을로 분리를 하려고 함, 그래서 가장 가중치가 큰 간선을 하나 빼기 위해서 따로 타운을 모아둔다.
            town.push_back({ cost , {a,b} });
            
        }
    }


    sort(town.begin(), town.end()); // 가중치 기준 정렬
    for (int i = 0; i < town.size() - 1; ++i) {
        result += town[i].first;
    }
    cout << result;
}