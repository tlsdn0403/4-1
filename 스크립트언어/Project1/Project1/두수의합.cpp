#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;
int n;
int taget;
vector<int> v;

int main() {
	cin >> n;

	for(int i = 0; i < n; i++) {
		int a;
		cin >> a;
		v.emplace_back(a);
	}
	cin >> taget;

	sort(v.begin(), v.end());

	int end = n - 1;
	int answer{};
	int start = 0;
	while(start < end) {
		int sum = v[start] + v[end];
		if(sum == taget) {
			answer++;
		}
		if(sum <= taget) {
			start++;
		} else {
			end--;
		}
	}
	cout << answer;
}

