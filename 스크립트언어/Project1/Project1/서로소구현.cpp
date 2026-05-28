#include<iostream>
using namespace std;


int v, e;
int parent[100001];

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
void printParentTable() {
    cout << "부모 테이블: ";
    for (int i = 1; i <= v; i++) {
        cout << parent[i] << ' ';
    }
    cout << '\n';
}

void printRootParent() {
    cout << "각 노드의 루트 부모: ";
    for (int i = 1; i <= v; i++) {
        cout << findParent(i) << ' ';
    }
    cout << '\n';
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

    cout << "초기 상태\n";
    printParentTable();
    cout << '\n';

    for (int i = 0; i < e; i++) {
        int a, b;
        cin >> a >> b;

        cout << "간선 입력: " << a << " " << b << '\n';

        unionParent(a, b);

        printParentTable();
        printRootParent();

        cout << '\n';
    }

    cout << "최종 부모 테이블\n";
    printParentTable();

    cout << "최종 루트 부모\n";
    printRootParent();

    return 0;
}