#include<iostream>
#include<vector>
#include<limits>
#include<algorithm>
using namespace std;
int n{};
vector<int> a; vector<int> b;
long long answer = std::numeric_limits<int>::max();
 // b를 바꾸지 말라고 말이 되어있지만 결과적으로 똑같음으로 b도 정렬을 하면 쉽게 풀 수 있다.

int main(){
	
	cin >> n;
	for (int i = 0; i< n; ++i) {
		int num{};
		cin >> num;
		a.push_back(num);
	}
	for (int i = 0; i< n; ++i) {
		int num{};
		cin >> num;
		b.push_back(num);
	}
	sort(a.begin(), a.end());
	sort(b.begin(), b.end(), [](int x, int y){
		return x > y;
	});
	long long num = 0;
	for (int i = 0; i < n; ++i) {
		num += a[i] * b[i];
	}
	answer = min(answer, num);
	cout << answer;

}