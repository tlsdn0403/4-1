#include <string>
#include <vector>
#include <sstream>
#include<map>

using namespace std;

// 1~n 번으로 분류된 개인정보가 n개 있다
// 유효기관 전까지만 보관이 가능하다
// 모든 달을 28일까지로 가정


// today = 오늘의 날짜
// terms 약관의 유효기관
// privacies 수집된 개인 정보

// privacies 에서 파기해야 될 애들의 번호를 answer에 넣자.

struct Day {
    int year;
    int month;
    int day;

};

Day makeDay(string day) {
    Day returnDay{};
    int cnt{};
    string word;
    for (char c : day) {
        if (c == '.') {
            if (cnt == 0) {
                returnDay.year = stoi(word);
                cnt++;
                word = "";
            }
            else if (cnt == 1) {
                returnDay.month = stoi(word);
                cnt++;
                word = "";
            }
        }
        else if (cnt == 2) {
            word += c;
        }
        else {
            word += c;
        }
    }
    returnDay.day = stoi(word);
    return returnDay;
}

bool isValid(Day today, Day privacyDay, int terms) {
    int todayDays =
        today.year * 12 * 28 +
        today.month * 28 +
        today.day;

    int privacyDays =
        privacyDay.year * 12 * 28 +
        privacyDay.month * 28 +
        privacyDay.day;

    int expiredDay = privacyDays + terms * 28;

    return todayDays < expiredDay;
}

vector<int> solution(string today, vector<string> terms, vector<string> privacies) {

    map<string, int> termsMap;

    Day toDay = makeDay(today);
    
    for (string s : terms) {
        stringstream ss(s);
        string  a, b;
        ss >> a >> b;
        termsMap[a] = stoi(b);
    }
    // termsMap[a] = 6;
    vector<int> answer;
    int cnt = 1;

    for(string s : privacies) {
        stringstream ss(s);
        string day, term;
        ss >> day >> term;
        Day privacyDay = makeDay(day);
        
        int waitTerm = termsMap[term];
        if (!isValid(toDay, privacyDay , waitTerm)) {
            answer.push_back(cnt);
        }
        cnt++;
	}
    return answer;
}

int main() {
    string today = "2020.01.01";
    vector<string> terms = { "Z 3", "D 5" };
    //"2021.05.02 A", "2021.07.01 B", "2022.02.19 C",
    vector<string> privacies = {  "2019.11.15 Z", "2019.08.02 D", "2019.07.01 D", "2018.12.28 Z" };
    solution(today, terms, privacies);
}