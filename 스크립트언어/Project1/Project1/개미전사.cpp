#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n;
int d[100];

int main() {
	cin >> n;
	vector<int> v;
	for(int i = 0; i < n; i++) {
		int num;
		cin >> num;
		v.push_back(num);
	}

	d[0] = v[0];
	d[1] = max(v[0], v[1]);

	for (int i = 2; i < n; i++) {
		d[i] = max(d[i - 2] + v[i], d[i - 1]);
	}
	cout << d[n - 1];
}