#include <string>
#include <vector>

using namespace std;


// 아이디 길이 3~15
// 소문자 , 숫자, - _ , 만 사용가능
// .은 연속 불가능 , 처금과 끝 불가능
string solution(string new_id) {
    string answer = "";
    int dotCnt{};
    for (int i = 0; i < new_id.size(); ++i) {
        // 1
        if (isupper(new_id[i]) != 0) {
            answer += tolower(new_id[i]);
            dotCnt = 0;
        }
        else if (isalpha(new_id[i])) {
            answer += new_id[i];
            dotCnt = 0;
        }
        else if (isdigit(new_id[i])) {
            answer += new_id[i];
            dotCnt = 0;
        }
        else if (new_id[i] == '-') {
            answer += new_id[i];
            dotCnt = 0;
        }
        else if (new_id[i] == '-') {
            answer += new_id[i];
            dotCnt = 0;
        }
        else if (new_id[i] == '.') {
            if (answer.size() == 0) {
                dotCnt++;
            }
            if (dotCnt < 1) {
                answer += new_id[i];
                dotCnt++;
            }
        }
      

    }
if (answer[answer.size() - 1] == '.') {
    answer[answer.size() - 1] -= '.';
}

// 5
if (answer.size() == 0) {
    answer = "a";
}
//6
if (answer.size() >= 16) {
    string newAnswer = "";
    for (int i = 0; i < 15; ++i) {
        newAnswer += answer[i];
    }
    answer = newAnswer;
}
//7
while (answer.size() <= 2) {
    answer += answer[answer.size() - 1];
}

return answer;
}