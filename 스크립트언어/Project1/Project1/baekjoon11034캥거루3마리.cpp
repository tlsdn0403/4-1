#include<iostream>
#include <algorithm>
using namespace std;


int main() {
	int cord[3];
	
	cin >> cord[0] >> cord[1] >> cord[2];

	sort(cord, cord + 3);
	cout << max(cord[2] - cord[1], cord[1] - cord[0]) - 1;
}