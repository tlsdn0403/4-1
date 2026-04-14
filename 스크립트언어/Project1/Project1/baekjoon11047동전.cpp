#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
	int n, money;
	cin >> n >> money;
	vector<int> v1(n, 0);
	for (int i = 0; i < n; ++i) {
		cin >> v1[i];
	}
	sort(v1.begin(), v1.end(),[](int a, int b){
		return a > b;
	});
	
	int answer = 0;
	while (money > 0) {
		for (int i : v1) {
			if (i <= money) {
				money -= i;
				answer++;
				break;
			}
		}
	}
	cout << answer;
}