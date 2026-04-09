#include <string>
#include <vector>
#include<map>
#include<sstream>

using namespace std;


int solution(vector<string> friends, vector<string> gifts) {
    int answer = 0;
    map<string, int> m;
    map<string, int> sendNum;
    map<string, int> receiveNum;
    for (string g : gifts) {
        if (m.find(g) == m.end()) {
            m.insert({g, 1});
        }
        else {
            m[g]++;
        }
       
        stringstream ss(g);
        string first{}, second{};
        ss >> first >> second;
        sendNum[first]++;

        // 이거 first로 하는 실수를 저지름
        receiveNum[second]++;
    }
    map<string, int > nextMonth;

    for (int i = 0; i < friends.size(); ++i) {
        for (int j = 0; j < friends.size(); ++j) {
            if (i == j) {
                continue;
            }
            int iTj{}, jTi{};
            iTj = m[friends[i] + " " + friends[j]];
            jTi = m[friends[j] + " " + friends[i]];

            if (iTj > jTi) {
                if (nextMonth.find(friends[i]) == nextMonth.end()) {
                    nextMonth.insert({ friends[i], 1 });
                }
                else {
                    nextMonth[friends[i]]++;
                }
            }
            else if( iTj == jTi) {
                int iCount = sendNum[friends[i]] - receiveNum[friends[i]];
                int jCount = sendNum[friends[j]] - receiveNum[friends[j]];
                if (iCount > jCount) {
                    if (nextMonth.find(friends[i]) == nextMonth.end()) {
                        nextMonth.insert({ friends[i], 1 });
                    }
                    else {
                        nextMonth[friends[i]]++;
                    }
                }
                else if (iCount < jCount) {
                   
                }
            }
        }
    }
        for (const auto & i : nextMonth) {
            answer = max(answer, i.second);
        }

    return answer;
}
int main() {
    solution({ "joy", "brad", "alessandro", "conan", "david" },
        { "alessandro brad", "alessandro joy", "alessandro conan", "david alessandro", "alessandro david" }
    );
    
}