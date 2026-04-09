#include <string>
#include <vector>
#include<cmath>
#include<cstdlib> //abs for int, long int
#include<algorithm>

using namespace std;
int maxMinHeight{};

int solution(vector<int> heights) {
	sort(heights.begin(), heights.end());
	do {
		int num = 0;
		int minHeight = 200001;
		for (int i : heights) {
		
			if (num != 0) {
				minHeight = min(abs(num - i), minHeight);
			}
			num = i;

		}
		maxMinHeight = max(minHeight, maxMinHeight);

	} while (next_permutation(heights.begin(), heights.end()));

    return maxMinHeight;
}

int main() {
	solution({ 1, 8, 5});
}