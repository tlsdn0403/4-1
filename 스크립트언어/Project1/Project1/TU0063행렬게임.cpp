#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;
int a{}, b{};
void printMatrix() {
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < b; j++) {
			if(j+1 == b)
				cout << (j + (b * i)) + 1;
			else
				cout << (j + (b * i)) + 1 << " ";
		}
		cout << '\n';
	}
}

void printMatrixR() {
	for (int i = 0; i < b; i++) {
		for (int j = 0; j < a; j++) {
			if (j + 1 == a)
				cout << ((a - j - 1) * b) + (i + 1);
			else
				cout << ((a - j -1) * b) + (i + 1) << " ";
		}
		cout << '\n';
	}
}
void printMatrixL() {
	for (int i = 0; i < b; i++) {
		for (int j = 0; j < a; j++) {
			if (j + 1 == a) {
				cout << b * (j)+(b - i);
			}
			else
				cout <<b*(j)+ (b- i) << " ";
		}
		cout << '\n';
	}
}
void printMatrixT() {
	for (int i = 0; i < b; i++) {
		for (int j = 0; j < a; j++) {
			if (j + 1 == a) {
				cout << (j * b) + i + 1;
			}
			else
				cout << (j * b) + i + 1 << " ";
		}
		if(i +1 < b) {
			cout << '\n';
		}
		
	}
}

int main() {
	
	cin >> a >> b;
	cout << "M" << '\n';
	printMatrix();
	cout<<"R" << '\n';
	printMatrixR();
	cout<<"L" << '\n';
	printMatrixL();
	cout << "T" << '\n';
	printMatrixT();
}