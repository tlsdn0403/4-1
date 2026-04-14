#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int num{};
string s{};
int main() {
	cin >> num;
	cin >> s;
	
	bool isSecond = false;
	bool useRight = false;
	int answer{};
	vector<char> vc;


	for (int i = 0; i < num; ++i) {
		if (s[i] == 'S') {
			vc.push_back('*');
			vc.push_back(s[i]);
			isSecond = false;
		}
		else if (s[i] == 'L') {
			if (!isSecond) {
				vc.push_back('*');
				vc.push_back(s[i]);
				isSecond = true;
			}
			else {
				vc.push_back(s[i]);
				isSecond = false;
			}
		}
	}
	vc.push_back('*');
	//for (char c : vc) {
	//	cout << c;
	//}
	for (size_t t = 0; t < vc.size(); ++t) {
		if (vc[t] != '*' && vc[t] != 'O') {
			if (t >= 1 && t<vc.size()) {
				if (vc[t - 1] == '*') {
					vc[t - 1] = 'O';
					answer++;
					continue;
				}
				if (vc[t + 1] == '*') {
					vc[t + 1] = 'O';
					answer++;
					continue;
				}
			}
		}
	}

	answer = min(answer, num);
	cout << answer;
}