#include<iostream>

int answer{};
int money[6]{ 500, 100, 50, 10, 5, 1 };

int main() {
	int input{};
	std::cin >> input;
	int num = 1000 - input;
	while (num > 0) {
		for (int i = 0; i < 6; ++i) {
			if (num >= money[i]) {
				num -= money[i];
				answer++;
				break;
			}
		}
	}
	std::cout << answer;
}