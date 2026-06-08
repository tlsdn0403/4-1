#include<iostream>
#include<string>
#include<vector>
#include<cmath>
using namespace std;

// 기수  , 진수표현 숫자의 수
int b, N, M;
int main() {

	cin >> b >> N >> M;

	vector<int> vN;
	vector<int> vM;
	int vnNum{}, vmNum{};
	for (int i = 0; i < N; ++i) {
		int num;
		cin >> num;
		vN.push_back(num);

		vnNum += pow(b, (N - i -1)) * num;
	}
	for (int i = 0; i < M; ++i) {
		int num;
		cin >> num;
		vM.push_back(num);

		vmNum += pow(b, (M - i-1))*num;
	}

	int answer = vnNum * vmNum;

	int num{};

	while (answer > 1) {
		answer /= b;
		num++;
		cout << answer << '\n';
	}
	cout << num;
}