#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 회전 초밥 벨트에 놓인 접시의 수 N, 초밥의 가짓수 d, 연속해서 먹는 접시의 수 k, 쿠폰 번호 c

int N, d, k, c;

vector<int> sushi;


int main() {
	// 입력부분
	cin >> N >> d >> k >> c;
	
	sushi.resize(N);
	for (int i = 0; i < N; i++) {
		cin >> sushi[i];
	}

	vector<int> count(d + 1, 0);
	int currentType = 0;

	// 초밥이 몇개씩 있는지
	for (int i = 0; i < k; i++) {
		if (count[sushi[i]] == 0) {
			currentType++;
		}
		count[sushi[i]]++;
	}

    int maxTypes = currentType;
    if (count[c] == 0) maxTypes++;

    for (int i = 0; i < N; i++) {
        // 맨 앞의 초밥 제거
        int removeNum = i;
        count[sushi[removeNum]]--;
        if (count[sushi[removeNum]] == 0) {
            currentType--;
        }

        
        int addNum = (i + k) % N;
        if (count[sushi[addNum]] == 0) {
            currentType++;
        }
        count[sushi[addNum]]++;

        int useCuopon = currentType;


        if (count[c] == 0) useCuopon++;

        maxTypes = max(maxTypes, useCuopon);
    }

    cout << maxTypes << "\n";
}	