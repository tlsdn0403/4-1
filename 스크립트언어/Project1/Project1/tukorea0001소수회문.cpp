#include<iostream>
#include<string>
#include<algorithm>
#include<sstream>   // itos
using namespace std;

int n{};

//  회문
bool isPalindrome(int num) {
	string s;
	s = to_string(num);
	string r = s;
	reverse(s.begin(), s.end());
	if (r == s) {
		return true;
	}
	return false;
}
// 소수
bool primeNumber(int num) {
	if (num < 2)return false;
	for (int i = 2; i * i <= num; ++i) {
		if (num % i == 0) return false;
	}
	return true;
}

int main() {
	cin >> n;

	while (true) {
		if (isPalindrome(n) && primeNumber(n)) {
			cout << n;
			break;
		}
		n++;
	}
}