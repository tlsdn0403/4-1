#include <string>
#include <vector>
#include<iostream>
#include<algorithm>
using namespace std;

vector<string> answer;
vector<bool> visit;
void dfs(string start , vector<vector<string>> tickets) {
    answer.push_back(start);
    if (answer.size() == tickets.size()+1) {
        return;
    }
    string end{};
    size_t endNum{};
    for (size_t i = 0; i < tickets.size(); ++i) {
        if (tickets[i][0] == start) {
            if (visit[i] == true) {
                continue;
            }
            if (end.empty()) {
                end = tickets[i][1];
                endNum = i;
            }  
            else {
                if (end > tickets[i][1]) {
                    end = tickets[i][1];
                    endNum = i;
                }
            }
        }
   
    }
    if (end.empty()) return;
    visit[endNum] = true;

    dfs(end, tickets);
}

vector<string> solution(vector<vector<string>> tickets) {

    visit.assign(tickets.size(), false);
    dfs("ICN", tickets);
    return answer;
}

