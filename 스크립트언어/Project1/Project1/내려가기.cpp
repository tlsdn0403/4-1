#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int n{};

int main() {

	cin >> n;
	// [n][3]
	vector<vector<int>> vi(n, vector<int>(3, 0));
	vector<vector<int>> MaxDp(n, vector<int>(3, 0));
	vector<vector<int>> MinDp(n, vector<int>(3, 100000));

	for (int i = 0; i < n; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		vi[i][0] = a;
		vi[i][1] = b;
		vi[i][2] = c;
	}

	for (int i = 0; i < 3; ++i) {
		MaxDp[0][i] = vi[0][i];
		MinDp[0][i] = vi[0][i];

	}

	for (int i = 1; i < n; ++i) {
		for (int j = 0; j < 3; ++j) {
			//°¡Àå ¿ÞÂÊ
			if (j == 0) {
				MaxDp[i][j] = max(MaxDp[i][j], max(vi[i][j] + MaxDp[i - 1][j], vi[i][j] + MaxDp[i - 1][j + 1]));
				MinDp[i][j] = min(MinDp[i][j], min(vi[i][j] + MinDp[i - 1][j], vi[i][j] + MinDp[i - 1][j + 1]));
			}
			else if (j == 1) {
				MaxDp[i][j] = max(MaxDp[i][j], max(vi[i][j] + MaxDp[i - 1][j], vi[i][j] + MaxDp[i - 1][j + 1]));
				MaxDp[i][j] = max(MaxDp[i][j], vi[i][j] + MaxDp[i - 1][j -1]);
				MinDp[i][j] = min(MinDp[i][j], min(vi[i][j] + MinDp[i - 1][j], vi[i][j] + MinDp[i - 1][j + 1]));
				MinDp[i][j] = min(MinDp[i][j], vi[i][j] + MinDp[i - 1][j- 1]);
			}
			else if (j == 2) {
				MaxDp[i][j] = max(MaxDp[i][j], max(vi[i][j] + MaxDp[i - 1][j], vi[i][j] + MaxDp[i - 1][j - 1]));
				MinDp[i][j] = min(MinDp[i][j], min(vi[i][j] + MinDp[i - 1][j], vi[i][j] + MinDp[i - 1][j - 1]));
			}
		}
	}
	int maxNum = 0;
	int minNum = 100000;

	for (int i = 0; i < 3; ++i) {
		maxNum = max(MaxDp[n - 1][i], maxNum);
		minNum = min(MinDp[n - 1][i], minNum);
	}
	cout << maxNum << " " << minNum;
}


//for (int i = 0; i < 3; ++i) {
	//	for (int j = 0; j < n; ++j) {
	//		cout << vi[i][j] << " ";
	//	}
	//	cout << endl;
	//}