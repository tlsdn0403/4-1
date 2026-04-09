#include <string>
#include <vector>
#include<iostream>
using namespace std;
int answer = 0;
vector<int> nums;
int targetNum{};
void dfs(char c , int num , int sum) {

    if (c == '+') {
        sum += nums[num];
    }
    else if (c == '-') {
        sum -= nums[num];
    }

    if (num == nums.size() - 1 ) {
        if (sum == targetNum) {
            answer += 1;
            return;
        }
        return;
    }

    dfs('+', num + 1, sum);

    dfs('-', num + 1, sum);


}

int solution(vector<int> numbers, int target) {
    nums = numbers;
    targetNum = target;
    dfs('+', 0, 0);
    dfs('-', 0 ,0);
    return answer;
}

int main() {
    cout<< solution({1, 1, 1, 1, 1}, 3);
}