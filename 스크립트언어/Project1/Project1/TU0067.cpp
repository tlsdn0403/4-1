#include<iostream>
#include<string>
#include<vector>
using namespace std;

int main() {
	int num{};
	string s;
	
	cin>>num >> s;
	int Height{},minHeight{ }, maxHeigth{ };
	for (char c : s) {
		if (c == '+') {
			Height++;
			maxHeigth = max(maxHeigth, Height);
		}
		else if (c == '-') {
			Height--; 
			minHeight = min(minHeight, Height);
		}
	}
	Height = maxHeigth - minHeight;

	vector<string> vs(Height);
}