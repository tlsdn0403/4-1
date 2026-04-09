#include<iostream>

using namespace std;

struct node {
	char left{};
	char right{};
};

node tree[26]{};

void dfs(char c) {
	if (c == '.')return;
	cout << c;
	dfs(tree[c - 'A'].left);
	dfs(tree[c - 'A'].right);
}
void dfs_middle(char c) {
	if (c == '.')return;
	
	dfs_middle(tree[c - 'A'].left);
	cout << c;
	dfs_middle(tree[c - 'A'].right);
}

void dfs_back(char c) {
	if (c == '.')return;
	
	dfs_back(tree[c - 'A'].left);
	dfs_back(tree[c - 'A'].right);
	cout << c;
}


int main() {
	int n{};
	cin >> n;
	for (int i = 0; i < n; ++i) {
		char key{}, left{}, right{};
		cin >> key >> left >> right;
		tree[key - 'A'] = { left, right };
	}

	dfs('A');
	cout << '\n';
	dfs_middle('A');
	cout << '\n';
	dfs_back('A');

}