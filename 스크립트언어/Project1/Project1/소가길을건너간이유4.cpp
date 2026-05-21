#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>


using namespace std;

// 닭의 마리수 , 소의 마리수
int C{}, N{};

vector<int> chicken;
// 건널 수 있는 시작시간 , 끝나는 시간
vector<pair<int, int>> cow;

int main() {
	cin >> C >> N;
	for (int i = 0; i < C; i++) {
		int c;
		cin >> c;
		chicken.push_back(c);
	}
	for(int i = 0; i < N; i++) {
		int start, end;
		cin >> start >> end;
		cow.push_back({ start, end });
	}

	//소가 start ~end 시간 사이에 닭이 도와줘야됨

	
}