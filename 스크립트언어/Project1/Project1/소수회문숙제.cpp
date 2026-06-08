#include<iostream>
#include<string>
#include<algorithm>
#include<sstream>   // itos
using namespace std;

int n{};
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