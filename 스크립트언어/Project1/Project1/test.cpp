#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

int main() {

	vector<int> v{ 1,2,3,4,5,6,7 };
	
	v.erase(remove_if(v.begin(), v.end(), [](int num) {return num % 2 == 0; }), v.end());

	for (int i : v) {
		cout << i << " ";
	}


	
}