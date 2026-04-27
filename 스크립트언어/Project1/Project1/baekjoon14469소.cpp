#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int Num{};

struct cow {
	int time;
	int weight;
};
int main() {
	cin >> Num;
	vector<cow> cows(Num);
	for(int i = 0; i < Num; i++) {
		int a{}, b{};
		cin >> a >> b;
		cows[i] = {a, b};
	}
	sort(cows.begin(), cows.end(), [](const cow& a, const cow& b) {
		if (a.time == b.time) return a.weight < b.weight;
		return a.time < b.time;
		});

	int time = 0;
	for (int i = 0; i < Num; i++) {
		if (time < cows[i].time) {
			time = cows[i].time + cows[i].weight;
		}
		else {
			time += cows[i].weight;
		}
	}
	cout << time;
}