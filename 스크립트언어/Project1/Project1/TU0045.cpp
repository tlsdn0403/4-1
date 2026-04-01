#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>

using namespace std;

int n{}, m{};
unordered_map<int, vector<int>> graph;

bool dfs(int num, const unordered_map<int, vector<int>>& crossRoads) {
    bool visited[301] = {};

    int start = -1;
    for (int i = 1; i <= n; ++i) {
        if (i != num) {
            start = i;
            break;
        }
    }

    if (start == -1) return true; 

    stack<int> st;
    st.push(start);

    while (!st.empty()) {
        int currentNode = st.top();
        st.pop();

        if (visited[currentNode]) continue;
        visited[currentNode] = true;

        for (int next : crossRoads.at(currentNode)) {
            if (next == num) continue;      // 삭제된 노드는 무시
            if (!visited[next]) {
                st.push(next);
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (i == num) continue;             // 삭제한 노드는 검사 제외
        if (!visited[i]) return false;
    }

    return true;
}

int main() {
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int j, k;
        cin >> j >> k;
        graph[j].push_back(k);
        graph[k].push_back(j);
    }
    int count{};
    vector<int> answer;
    for (int i = 1; i <= n; ++i) {
        if (!dfs(i, graph)) {   // i를 지웠을 때 연결이 끊기면
            count++;
            answer.push_back(i);
        }
    }
    cout << count << '\n';
    for (int i : answer) {
        cout << i << '\n';
    }
}