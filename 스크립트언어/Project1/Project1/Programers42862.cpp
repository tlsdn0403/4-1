#include<iostream>
#include <string>
#include <vector>
#include<algorithm>

using namespace std;

int solution(int n, vector<int> lost, vector<int> reserve) {
    int answer = 0;
    answer = n;
    sort(lost.begin(), lost.end());
    sort(reserve.begin(), reserve.end());
    vector<int> realLost;
    vector<int> realReserve;

    for (int i : lost) {
        if (find(reserve.begin(), reserve.end(), i) == reserve.end()) {
            realLost.push_back(i);
        }
    }
    for (int i : reserve) {
        if (find(lost.begin(), lost.end(), i) == lost.end()) {
            realReserve.push_back(i);
        }
    }
    for (int r : realReserve) {
        auto it = find(realLost.begin(), realLost.end(), r - 1);
        if (it != realLost.end()) {
            realLost.erase(it);
        }
        else {
            auto it = find(realLost.begin(), realLost.end(), r + 1);
            if (it != realLost.end()) {
                realLost.erase(it);
            }
        }
        
    }
   
    answer -= realLost.size();
    return answer;
}

int main() {
    int n;
    cin >> n;
    vector<int> lost;
    vector<int> reserve;
    
    lost.push_back(2);
    lost.push_back(4);
    reserve.push_back(1);
    reserve.push_back(3);
    reserve.push_back(5);
    

    cout << solution(n, lost, reserve);
}