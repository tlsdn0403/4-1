#include <string>
#include <vector>
#include<iostream>
#include<algorithm>
#include<stack>
using namespace std;

vector<string> answer;
vector<bool> visit;
bool solve = false;
void dfs(string start , vector<vector<string>> tickets) {
    answer.push_back(start);

    if (answer.size() == tickets.size()+1) {
        solve = true;
        return;
    }




    for (int i = 0; i < tickets.size(); ++i) {
        if (start == tickets[i][0]) {
            if (!visit[i]) {
                visit[i] = true;
                dfs(tickets[i][1], tickets);
                if (solve) {
                    return;
                }
                visit[i] = false;
            }
        }
    }
    //잘못된 답 빼
    answer.pop_back();
}

vector<string> solution(vector<vector<string>> tickets) {

    visit.assign(tickets.size(), false);
    sort(tickets.begin(), tickets.end(), [](vector<string >s1, vector<string> s2) {
        return s1[1] < s2[1];
        });
    dfs("ICN", tickets);
    return answer;
}


