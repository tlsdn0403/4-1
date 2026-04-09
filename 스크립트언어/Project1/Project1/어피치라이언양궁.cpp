#include<iostream>
#include <string>
#include<algorithm>
#include <vector>

using namespace std;
vector<int> appeach;

int maxNum = -1;
void dfs(int n, int maxTry , vector<int>& rion  , vector<int> &answer) {
   

    if (n >= maxTry) {
        int appeachPoint{};
        int rionPoint{};
        for (size_t i = 0; i < 11; i++) {
            if (rion[i] == 0 && appeach[i] == 0) continue;
            if (rion[i] > appeach[i]) {
                rionPoint += 10 - i;
            }
            else {
                appeachPoint += 10 - i;
            }
        }
        if (appeachPoint >= rionPoint) {
            return;
        }
        int score = rionPoint - appeachPoint;
        
        if (maxNum < score) {
            maxNum = score;
            answer = rion;
            return;
        }
        else if (maxNum == score) {
            for (int i = 10; i >= 0; --i) {
                if (rion[i] > answer[i]) {
                    maxNum = score;
                    answer = rion;
                    return;
                }
                else if (rion[i] == answer[i]) {
                    continue;
                }
                else {
                    return;
                }
            }
            
        }
        return;
    }
    
    for (int i = 0; i < 11; ++i) {
        rion[i] += 1;
       
        dfs(n + 1, maxTry, rion , answer);
        rion[i] -= 1;
    }
    
    return;
}

vector<int> solution(int n, vector<int> info) {
    maxNum = -1;
    appeach = info;
    vector<int> answer(11, 0);
    vector<int> v(11,0);
    dfs(0 , n , v,answer);
    if (maxNum <= 0) return { -1 };
    return answer;
}

int main() {
    vector<int> vi =solution(5, { 2,1,1,1,0,0,0,0,0,0,0 });
    for (int i : vi)
        cout << i;
}

