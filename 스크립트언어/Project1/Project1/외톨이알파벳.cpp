#include <string>
#include <vector>
#include<map>
using namespace std;



//2회 이상 나타나고, 덩어리로 뭉쳐있지 않다면 외톨이
string solution(string input_string) {
    map<char, pair<int, bool> > m;

    char prev;
    for (char c : input_string) {
        if (m.find(c) != m.end()) {
            // 찾음
            m[c].first += 1;

            if (c != prev) {
                m[c].second = true;
            }


        }
        else {
            m.insert({ c , {1 , false} });
        }
        prev = c;
    }
    string answer = "";
    for (auto p : m) {
        if (p.second.first > 1 && p.second.second == true) {
            answer += p.first;
        }
    }

    if (answer == "") {
        answer = "N";
    }





    return answer;
}