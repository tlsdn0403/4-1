#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;
vector<int> v;
int N{};
int main() {

	cin >> N;
	for(int i =0 ; i < N; i++) {
		int num;
		cin >> num;
		v.push_back(num);
	}
	//내림차순
	sort(v.begin(), v.end(), [](int a, int b) {
		return a > b;
		});
	int count = 1;
	int answer{};
	for (int i : v) {
		if (count % 3 == 0) {
			count++;
		}
		else {
			answer += i;
			count++;
		}
	}
	cout << answer;
}