#include<iostream>
#include<cmath>
#include<string>

int solution(std::string s) {
	int answer{ };
	int beforeAnswer{};
	int num{};
	bool bIsint[9]{ 0 };
	for (size_t i = 0; i < s.size(); ++i) {
		if ('0' <= s[i] && s[i] <= '9')
		{
			if (num == 1 && s[i] == '0') {
				num = 10;
			}
			else {
				beforeAnswer = answer;
				answer += num;
				num = s[i] - '0';
			}

		}
		else if (s[i] == 'S') {
			num = pow(num, 1);
		}
		else if (s[i] == 'D') {
			num = pow(num, 2);
		}
		else if (s[i] == 'T') {
			num = pow(num, 3);
		}
		else if (s[i] == '*') {
			int Number = answer - beforeAnswer;
			Number *= 2;
			answer = beforeAnswer + Number;
			num *= 2;
		}
		else if (s[i] == '#') {
			num *= -1;
		}
	}
	answer += num;
	return answer;
}
int main() {
	while(true){
		std::string s;
		std::cin >> s;
		std::cout << solution(s);
	}
	
}