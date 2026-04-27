#include<iostream>
#include<stack>
#include<string>
//알파벳이 나오면 스택에 넣는다
// +가 나오면 스택에서 2개 꺼낸다	더해서 가로를 쳐서 다시 스택에 넣는다
// -가 나오면 스택에서 2개 꺼낸다	빼서 가로를 쳐서 다시 스택에 넣는다.
// 맨 마지막에 스택에 있는 것을 꺼내서 출력한다.
using namespace std;

int main() {
	string s;
	cin >> s;
	stack<string> st;

	for (char c : s) {
		if (isalpha(c)) {
			st.push(string(1, c));
		}
		//+나 -이면
		else {
			string s1 = st.top();
			st.pop();
			string s2 = st.top();
			st.pop();
			if (c == '+') {
				st.push("(" + s2 + "+" + s1 + ")");
			}
			else if (c == '-') {
				st.push("(" + s2 + "-" + s1 + ")");
			}
		}
	}
	while (!st.empty()) {
		cout << st.top();
		st.pop();
	}
}