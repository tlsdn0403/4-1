#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct player {
	int num;
	int score;
	int vote;
};

vector<player> vh;
vector<player> vi;
vector<player> answer;
int n{};
int main() {
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int score;
		cin >> score;
		player p;
		p.num = i + 1;
		p.score = score;
		vh.push_back(p);
	}
	for (int i = 0; i < n; ++i) {
		int score;
		cin >> score;
		player p;
		p.num = i + 1;
		p.score = score;
		vi.push_back(p);
	}
	//for (auto i : vh) {
	//	cout << "Kod0" << i.num << " " << i.score << '\n';
	//}
	//for (auto i : vi) {
	//	cout << "Kod0" << i.num << " " << i.score << '\n';
	//}

	for (auto i : vh) {
		player p;
		p.score = n - i.score + 1;
		p.num = i.num;
		answer.push_back(p);
	}
	//cout << "first answer" << '\n';
	//for (auto i : answer) {
	//	cout<<"Kod0" << i.num << " " << i.score<<'\n';
	//}
	//cout << '\n';
	sort(vi.begin(), vi.end(), [](player pa, player pb) {
		return pa.score < pb.score;
		});
	//cout << "vi" << '\n';
	//for (auto i : vi) {
	//cout << "Kod0" << i.num << " " << i.score << '\n';
	//}
	//
	for (size_t t = 0; t < vi.size(); ++t) {
		answer[vi[t].num - 1].score += t+1;
		answer[vi[t].num - 1].vote = vi[t].score;

	}
	//for (auto i : answer) {
	//cout<<"Kod0" << i.num << " " << i.score << " "<<i.vote << '\n';
	//}
	//cout << "+vi" << '\n';
	//for (auto i : answer) {
	//	cout << "Kod0" << i.num << " " << i.score << '\n';
	//}
	sort(answer.begin(), answer.end(), [](player pa, player pb) {
		if (pa.score == pb.score) {
			return pa.vote > pb.vote;
		}
		return pa.score > pb.score;
		});
	//cout << "answer" << '\n';
	//for (auto i : answer) {
	//	cout << "Kod0" << i.num << " " << i.score << " " << i.vote << '\n';
	//}
	for (size_t t = 0; t < answer.size(); ++t) {
		if (answer[t].num < 10) {
			cout << t + 1 << ". " << "Kod0" << answer[t].num << " (" << answer[t].score << ")" << '\n';
		}
		else {
			cout << t + 1 << ". " << "Kod" << answer[t].num << " (" << answer[t].score << ")" << '\n';
		}
	}
}