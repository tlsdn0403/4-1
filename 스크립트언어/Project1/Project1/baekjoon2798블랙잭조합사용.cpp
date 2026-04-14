#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int count = 0;
int answer = 0;
int n, target;
void combination(size_t start , vector<int>& v,vector<int>& comb ) {
	if (comb.size() == 3) {
		int num = 0;
		for (int i : comb) {
			num += i;
		}
		if (num <= target) {
			answer = max(answer, num);
		}
		return;
	}

	for (size_t i = start; i < v.size(); ++i) {
		comb.push_back(v[i]);
		combination(i + 1, v, comb);
		comb.pop_back();
	}
}

int main() {

	cin >> n >> target;
	vector<int> v1(n, 0); 
	vector<int> comb;
	for (int i = 0; i < n; ++i) {
		cin >> v1[i];
	}

	combination(0, v1, comb);
	cout << answer;
}