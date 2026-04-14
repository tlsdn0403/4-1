#include<iostream>
#include<string>

int N{}, M{};
int main() {

	std::string a, b;
	std::cin >> a >> b;
	size_t a_pos{}, b_pos{};
	for (char c : a) {
		auto pos = b.find(c);
		if (pos != std::string::npos) {
			a_pos = a.find(c);
			b_pos = pos;
			break;
		}
	}
	for (size_t i = 0; i < b.size(); ++i) {
		for (size_t j = 0; j < a.size(); ++j) {
			if (i == b_pos) {
				std::cout << a[j];
			}
			else if (j == a_pos) {
				std::cout << b[i];
			}
			else {
				std::cout << ".";
			}
		}
		std::cout << '\n';
	}
}