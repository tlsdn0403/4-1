#include<iostream>
#include<string>
#include<vector>

using namespace std;

int main() {
	int num{};
	string s;
	
	cin>>num >> s;
	int Height{},minHeight{ }, maxHeight{ };
	char prev = {};
	for (char c : s) {
		if (c == '+') {
			if (prev == '+') {
				Height++;
				maxHeight = max(maxHeight, Height);
			}
			else if (prev == '-') {

			}
			else if (prev == '=') {

			}
			
		}
		else if (c == '-') {
			if (prev == '+') {
				
			}
			else if (prev == '-') {
				Height--;
				minHeight = min(minHeight, Height);
			}
			else if (prev == '=') {
				Height--;
				minHeight = min(minHeight, Height);
			}
			
			
		}
		else {
			if (prev == '+') {
				Height++;
				maxHeight = max(maxHeight, Height);
			}
			else if (prev == '-') {
				
			}
			else if (prev == '=') {

			}
		}
		prev = c;
	}
	cout << maxHeight << " " << minHeight <<" " <<Height<<'\n';
	int startHeight = 0;
	if (minHeight > 0) {
		startHeight = minHeight-1;
	}
	Height = maxHeight - minHeight +1;
	if (Height < 1) {
		Height = 1;
	}


	vector<vector<char>> vs(Height, vector<char>(num, '.'));
	int k = 0;
	bool isUpper = false;
	bool isLower = false;
	bool isSame = false;
	for (char c : s) {
		if (c == '+') {
			if (isLower ==true && isSame == false) {
				startHeight--;
			}
			vs[startHeight][k] = '/';

			startHeight--;

			isLower = false;
			isUpper = true;
			isSame = false;
		}
		else if (c == '-') {
			if (isUpper== true) {
				startHeight++;
			}
			if (isLower == true && isSame == true) {
				startHeight++;
			}
			vs[startHeight][k] = '\\';

			startHeight++;

			isLower = true;
			isUpper = false;
			isSame = false;
		}
		else {
			if (isLower == true&& isSame ==false) {
				startHeight--;
			}
			vs[startHeight][k] = '_';
			isSame = true;
		}
		++k;
	}

	for (int i = 0; i < Height; ++i) {
		for (int j = 0; j < num; ++j) {
			cout << vs[i][j];
		}
		cout << '\n';
	}

}