#include<iostream>
#include<string>

using namespace std;

int dx[8] = { 2,2,-2,-2,1,-1,1,-1 };
int dy[8] = { 1,-1 ,1,-1,2,2,-2,-2 };

int main() {
	string s;
	cin >> s;
	int x = s[0] - 'a' + 1;
	int y = s[1] - '0';
	cout<<x<<',' << y;
}