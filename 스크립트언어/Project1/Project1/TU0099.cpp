#include<iostream>
#include<vector>
using namespace std;

struct nutrient {
	int Carbs = 0;
	int Protein = 0;
	int Fat = 0;
	int kcal = 0;
};
int n;
int answer = 0;
nutrient normal;
void combination(size_t start, vector<nutrient> v, vector<nutrient> comb) {

	if (comb.size() <= 3 && comb.size()> 0) {
		int a = 0, b = 0, c = 0 , d = 0;
		for (nutrient nut : comb) {
			a += nut.Carbs;
			b += nut.Protein;
			c += nut.Fat;
		}
		d = (a * 4) + (b * 4) + (c * 9);
		if (a <= normal.Carbs && b >= normal.Protein && c <= normal.Fat && d <= normal.kcal) {
			answer++;
			if (comb.size() == 3) {
				return;
			}
		}
		else if (a > normal.Carbs && c > normal.Fat && d > normal.kcal) {
			return;
		}
		else {
			if (comb.size() == 3) {
				return;
			}
		}

	}

	for(size_t st = start; st < n; ++st) {
		comb.push_back(v[st]);
		combination(st + 1, v, comb);
		comb.pop_back();
	}
}


int main() {
	
	cin >> n;
	vector<nutrient> vn(n);
	for (int i = 0; i < n; ++i) {
		cin >> vn[i].Carbs >> vn[i].Protein >> vn[i].Fat;
	}
	
	cin >> normal.Carbs >> normal.Protein >> normal.Fat >>normal.kcal;

	vector<nutrient> vc;
	combination(0, vn, vc);
	cout << answer;
}