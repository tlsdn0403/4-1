#include<iostream>
#include<queue>
int A{}, B{};

using namespace std;
void bfs() {
	
}


int main() {
	cin >> A >> B;
	int answer =1;
	while (true) {
		if (A == B) {
			cout << answer;
			break;
		}
		if (A > B) {
			cout << -1;
			break;
		}
		if (B % 2 == 0) {
			B = B / 2;
			answer++;
		}
		else if (B % 10 == 1) {
			B = (B - 1) / 10;
			answer++;
		}
		else {
			cout << -1;
			break;
		}
	}

}