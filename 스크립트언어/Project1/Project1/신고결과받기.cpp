#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <set>

using namespace std;

vector<int> solution(vector<string> id_list, vector<string> report, int k) {

    set<pair<string, string>> Report;
    map<string, int> BadID;

    for (string s : id_list) {
        BadID.insert({ s, 0 });
    }

    for (string s : report) {
        stringstream ss(s);

        string first, second;
        ss >> first >> second;

        Report.insert({ first, second }); 
    }

    for (auto p : Report) {
        BadID[p.second]++;
    }

    vector<int> answer;

    map<string, int> MailCount;
    for (auto p : Report) {
        string reporter = p.first;
        string reported = p.second;

        if (BadID[reported] >= k) {
            MailCount[reporter]++;
        }
    }

    for (string s : id_list) {
        answer.push_back(MailCount[s]);

    }
    return answer;
}