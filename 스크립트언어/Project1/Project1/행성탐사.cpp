#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;
// J =정글 , O = 바다 , I =얼음

// 행 , 열
int M{}, N{};

int dpJ[1001][1001];
int dpO[1001][1001];
int dpI[1001][1001];


struct ans {
	int j;
	int o;
	int i;
};
int main() {

	cin >> M >> N;
	int count{};
	cin >> count;

	for (int i = 0; i < M; ++i) {
		string s;
		cin >> s;
		for (int j = 0; j < s.size(); ++j) {
			if (s[j] == 'J') {
				dpJ[i + 1][j + 1] = dpJ[i + 1][j] + dpJ[i][j + 1] - dpJ[i][j] + 1;
				dpO[i + 1][j + 1] = dpO[i + 1][j] + dpO[i][j + 1] - dpO[i][j];
				dpI[i + 1][j + 1] = dpI[i + 1][j] + dpI[i][j + 1] - dpI[i][j];
			}
			else if (s[j] == 'O') {
				dpJ[i + 1][j + 1] = dpJ[i + 1][j] + dpJ[i][j + 1] - dpJ[i][j];
				dpO[i + 1][j + 1] = dpO[i + 1][j] + dpO[i][j + 1] - dpO[i][j] + 1;
				dpI[i + 1][j + 1] = dpI[i + 1][j] + dpI[i][j + 1] - dpI[i][j];
			}
			else if (s[j] == 'I') {
				dpJ[i + 1][j + 1] = dpJ[i + 1][j] + dpJ[i][j + 1] - dpJ[i][j];
				dpO[i + 1][j + 1] = dpO[i + 1][j] + dpO[i][j + 1] - dpO[i][j];
				dpI[i + 1][j + 1] = dpI[i + 1][j] + dpI[i][j + 1] - dpI[i][j] + 1;
			}
		}
	}
	vector<ans>  b;
	while (count > 0) {
		int r1, l1, r2, l2;
		cin >> r1 >> l1 >> r2 >> l2;

		ans a;
		a.j = dpJ[r2][l2] - dpJ[r2][l1 - 1] - dpJ[r1 - 1][l2] + dpJ[r1 - 1][l1 - 1];
		a.o = dpO[r2][l2] - dpO[r2][l1 - 1] - dpO[r1 - 1][l2] + dpO[r1 - 1][l1 - 1];
		a.i = dpI[r2][l2] - dpI[r2][l1 - 1] - dpI[r1 - 1][l2] + dpI[r1 - 1][l1 - 1];
		b.push_back(a);
		count--;
	}

	for (auto i : b) {
		cout << i.j << " " << i.o << " " << i.i << endl;
	}
}