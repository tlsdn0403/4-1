#include<iostream>
#include<string>
#include<vector>

using namespace std;

int n{};
int main() {
	cin >> n;

	for(int i =0 ; i<n ; ++i) {
		string s;
		cin >> s;
		vector<char> v;
		for (char c : s) {
			if (c != ' ' && c != '=') {
				v.push_back(c);
			}
		}
		int firstNum{}, secondNum{};
		
		firstNum = v[0] - '0';
		secondNum= v[2] - '0';

		switch (v[4]) {
			case '+':
				if (firstNum + secondNum = v[4] - '0') {

				}
			break;
		}
	