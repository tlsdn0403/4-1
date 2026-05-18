#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

// 카드의 개수만큼 제곱한 게 점수


int n{}, j{};

int main() {
	cin >> n >> j;

	string s;
	cin >> s;
	int kCount{};
	int dCount{};
	int oCount{};
	int rCount{};
	//krokod
	int krokodCount{};

	for (char c : s) {
		if (c == 'k') {
			kCount++;
		}
		if (c == 'd') {
			dCount++;
		}
		if (c == 'o') {
			oCount++;
		}
		if (c == 'r') {
			rCount++;
		}
	}
	int kCount1 = kCount;
	int dCount1 = dCount;
	int oCount1 = oCount;
	int rCount1 = rCount;
	while (true) {
		if (kCount1 >= 2 && rCount1 >= 1 && oCount1 >= 2 && dCount1 >= 1) {
			krokodCount++;
			kCount1 -= 2;
			rCount1 -= 1;
			oCount1 -= 2;
			dCount1-= 1;
		}
		else {
			break;
		}
	}

	int answer{};
	int maxNum{};
	maxNum = max(maxNum, kCount);
	maxNum = max(maxNum, dCount);
	maxNum = max(maxNum, oCount);
	maxNum = max(maxNum, rCount);

	if (maxNum == kCount) {
		kCount += j;
	}
	else if (maxNum == dCount) {
		dCount += j;
	}
	else if (maxNum == oCount) {
		oCount += j;
	}
	else if (maxNum == rCount) {
		rCount += j;
	}
	//cout << "k: " << kCount << " d: " << dCount << " o: " << oCount << " r: " << rCount <<"krokod:"<<krokodCount<< endl;
	answer = (kCount * kCount) + (dCount * dCount) + (oCount * oCount) + (rCount * rCount) + krokodCount*7;
	cout << answer;
}