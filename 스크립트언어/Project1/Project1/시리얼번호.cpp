#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int N;

int main() {
	cin >> N;
	vector<string> v;
	for(int i = 0; i < N; ++i) {
		string s;
		cin >> s;
		v.push_back(s);
	}
	
    sort(v.begin(), v.end(), [](string a, string b) {
        if (a.length() != b.length()) {
            return a.length() < b.length();
        }

        int aNum = 0, bNum = 0;

        for (char c : a) {
            if (c >= '0' && c <= '9') {
                aNum += c - '0';
            }
        }

        for (char c : b) {
            if (c >= '0' && c <= '9') {
                bNum += c - '0';
            }
        }

        if (aNum != bNum) {
            return aNum < bNum;
        }

        return a < b;
        });

	for(string s : v) {
		cout << s << "\n";
	}
}