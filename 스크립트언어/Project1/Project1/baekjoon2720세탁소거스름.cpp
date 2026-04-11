#include<iostream>
#include<vector>
using namespace std;

struct Money {
	int quarter;
	int dime;
	int nickel;
	int penny;
};
int main() {
	int money[4] = { 25, 10, 5, 1 };
	int target{}, num{};
	cin >> target;
	vector<Money> answer(target);
	for (int i = 0; i < target; i++) {
		int moneyTarget{};
		cin >> moneyTarget;
		while (moneyTarget > 0) {
			if (moneyTarget >= money[0]) {
				answer[i].quarter++;
				moneyTarget -= money[0];
			}
			else if(moneyTarget >= money[1]) {
				answer[i].dime++;
				moneyTarget -= money[1];
			}
			else if(moneyTarget >= money[2]) {
				answer[i].nickel++;
				moneyTarget -= money[2];
			}
			else if(moneyTarget >= money[3]) {
				answer[i].penny++;
				moneyTarget -= money[3];
			}
		}
	}
	for (const auto& v : answer) {
		cout << v.quarter << " " << v.dime << " " << v.nickel << " " << v.penny << "\n";
	}
}