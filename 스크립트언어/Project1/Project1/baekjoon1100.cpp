#include<iostream>
#include<string>
using namespace std;

 //auto 시작 = chrono::high_resolution_clock::now(); //스톱워치 시작
int main() {

	string chessboard;
	int answer = 0;
	for (int i = 0; i < 8; ++i) {
		cin >> chessboard;

		if (i % 2 == 0) {
			for (size_t j = 0; j < chessboard.length(); ++j) {
				if (j % 2 == 0)
				{
					if(chessboard[j] == 'F')
						answer++;
				}
			}
		}
		else 
		{
			for (size_t j = 0; j < chessboard.length(); ++j) {
				if (j % 2 != 0)
				{
					if (chessboard[j] == 'F')
						answer++;
				}
			}
		}
	}

	cout << answer;

}
