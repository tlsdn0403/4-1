#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

int main() {

	string s;
	string boom;
	cin >> s >> boom;

	while (true) {
		auto pos = s.find(boom);
		if (pos == string::npos) {
			break;
		}
		s.erase(pos, boom.size()); // pos 위치부터 붐 크기만큼 지움
	}
	cout << s;
}