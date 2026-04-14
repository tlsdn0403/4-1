#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
	int T{};
	cin >> T;
	for (int i = 0; i < T; ++i) {
		int N{}, answer{};
		string board_1{ }, board_2{ };
		cin >> N;
		cin >> board_1;
		cin >> board_2;
		vector<int> change;
		for (int j = 0; j < N; ++j) {
			bool bChange = false;
			if (board_1[j] != board_2[j]) {
				int erase_num = -1;
				for (int v : change) {
					if (board_1[v] != board_1[j]) {
						swap(board_1[v], board_1[j]);
						bChange = true;
						erase_num = v;
						answer++;
						break;
					}
				}
				if (bChange) {
					change.erase(remove(change.begin(), change.end(), erase_num), change.end());
				}
				if (!bChange) {
					change.push_back(j);
				}
				
			}
		}
		answer += change.size();
		cout << answer<<'\n';
	}
}