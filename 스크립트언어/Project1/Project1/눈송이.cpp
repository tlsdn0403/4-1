#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
int n{};

int main() {

	cin >> n;

	vector<int> answer;
	while (n--) {
		int x, y;
		cin >> x >> y;
		
		vector<vector<char>> snow(x, vector<char>(y));
		vector<pair<int, int>> Center;


		for (int i = 0; i < x; ++i) {
			for (int j = 0; j < y; ++j) {
				cin >> snow[i][j];
				if (snow[i][j] == '+') {
					Center.push_back({ i,j });
				}
			}
		}
		int currentAnswer = 0;
		for (auto i : Center) {
			int size= 1;
			while (true) {
				
				if (i.first - size >= 0 && i.first + size < x && i.second - size >= 0 && i.second + size < y) {

				}
				else {
					currentAnswer = max(currentAnswer, size - 1);
					break;
				}

				if (snow[i.first - size][i.second - size] == '\\' && snow[i.first + size][i.second + size] == '\\' &&
					snow[i.first - size][i.second] == '|' && snow[i.first + size][i.second] == '|' &&
					snow[i.first][i.second - size] == '-' && snow[i.first][i.second + size] == '-' &&
					snow[i.first - size][i.second + size] == '/' && snow[i.first + size][i.second - size] == '/'
					) {
					size++;
				}
				else {
					currentAnswer = max(currentAnswer, size - 1);
					break;
				}
			}
		}

		answer.push_back(currentAnswer);

		/*cout << "------------------------- print---------------------" << endl;
		for(int i = 0; i < x; ++i) {
			for(int j = 0; j < y; ++j) {
				cout << snow[i][j];
			}
			cout << endl;
		}*/
	}
	for (int i : answer) {
		cout << i << endl;
	}
}