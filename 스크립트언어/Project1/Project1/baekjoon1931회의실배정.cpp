#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

struct Time {
	int start;
	int end;
};

int main() {
	int n{};
	cin >> n;
	vector<Time> time(n);
	
	for(int i = 0; i < n; i++) {
		cin >> time[i].start >> time[i].end;
	}
	sort(time.begin(), time.end(),[](Time a, Time b){
		if (a.end == b.end) {
			return a.start < b.start;
		}
		else {
			return a.end < b.end;
		}
	});
	int answer{};
	int startTime = {};
	for (auto t : time) {
		if(startTime <= t.start) {
			startTime = t.end;
			answer++;
		}
	}
	cout << answer;
}