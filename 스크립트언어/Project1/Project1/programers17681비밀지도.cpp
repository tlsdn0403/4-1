#include <string>
#include <vector>
#include <bitset>
#include<iostream>
#include<stack>
using namespace std;



vector<string> solution(int n, vector<int> arr1, vector<int> arr2) {
    vector<string> answer;
    for (int i = 0; i < n; ++i) {
        int num1 = arr1[i];
        int num2 = arr2[i];
        string row1 = "";
		string row2 = "";
        for (int i = 0; i < n; i++) {
            row1 += char('0' + (num1 % 2));
			row2 += char('0' + (num2 % 2));
            num1 /= 2;
			num2 /= 2;
        }
		string combined = "";
        for(int i = 0; i < n; ++i) {
            combined += char('0' + ((row1[i] - '0') | (row2[i] - '0')));
		}
		string row = "";
        for(int j = n - 1; j >= 0; --j) {
            if (combined[j] == '1') {
                row += "#"; // 벽
            } else {
                row += " "; // 공백
            }
		}
		answer.push_back(row);
    }
    
    return answer;
}

int main() {
    int n = 5;
	stack<int> my_s;
    vector<int> arr1 = {9, 20, 28, 18, 11};
    vector<int> arr2 = {30, 1, 21, 17, 28};
	int X = 9;
    while (X != 0)
    {
        if (X % 2 == 1) // 나머지가 1
            my_s.push(1);
        else			// 나머지가 0
            my_s.push(0);

        X /= 2; 		// X가 0이 될 때까지 2로 계속해서 나눈다.
    }
    for(int i = 0; i < my_s.size(); ++i) {
        cout << my_s.top() << " ";
        my_s.pop();
	}
    return 0;
}