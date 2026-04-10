#include<iostream>

using namespace std;

int Round{};
int main() {

	cin >> Round;
	int P1Sum{}, P2Sum{};
	pair<int, int> lead;
	pair<int, int> answer;
	for (int i = 0; i < Round; ++i) {
		int p1{}, p2{};
		cin >> p1 >> p2;
		P1Sum += p1, P2Sum += p2;
		if (P1Sum > P2Sum) {
			lead.first = 1;
			lead.second = P1Sum - P2Sum;
		}
		else {
			lead.first = 2;
			lead.second = P2Sum - P1Sum;
		}
		if (answer.second < lead.second) {
			answer = lead;
		}
	}
	cout << answer.first << " " << answer.second;
}