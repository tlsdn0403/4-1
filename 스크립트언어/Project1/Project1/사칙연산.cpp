#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main() {
    int n;
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; ++i) {
        string s;
        getline(cin, s);

        stringstream ss(s);

        long long a, b, result;
        char op, equalSign;

        ss >> a >> op >> b >> equalSign >> result;

        bool correct = false;

        switch (op) {
        case '+':
            correct = (a + b == result);
            break;
        case '-':
            correct = (a - b == result);
            break;
        case '*':
            correct = (a * b == result);
            break;
        case '/':
            correct = (b != 0 && a / b == result);
            break;
        }

        if (correct) {
            cout << "correct"<<"\n";
        }
        else {
            cout << "wrong answer"<<"\n";
        }
    }
}