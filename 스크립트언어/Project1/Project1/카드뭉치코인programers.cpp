#include <string>
#include <vector>

using namespace std;

bool canMakeN(vector<int> Deck , int n) {

}

int solution(int coin, vector<int> cards) {
    int answer = 0;
    int n = cards.size();
    vector<int> myDeck;
    // 스테이지 1 시작하기전 드로우
    for (int i = 0; i < n / 3; i++) {
        myDeck.emplace_back(cards[i]);
    }

    return answer;
}