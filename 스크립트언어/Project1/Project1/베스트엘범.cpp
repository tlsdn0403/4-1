#include <string>
#include <vector>
#include<map>
#include<algorithm>
using namespace std;
struct Music {
    string genre;
    int play;
    int index;
};
map<string, vector<Music>> musicMap;

vector<int> solution(vector<string> genres, vector<int> plays) {

    for(int i = 0; i < genres.size(); ++i) {
         Music music;
         music.genre = genres[i];
         music.play = plays[i];
         music.index = i; 
         //genres 를 키값으로 거기에 뮤직 구조체 넣음
         musicMap[genres[i]].push_back(music);

         
	}
    for (auto& pair : musicMap) {
        sort(musicMap[pair.first].begin(), musicMap[pair.first].end(), [](Music a, Music b) {
            return a.play > b.play;
            });
    }
   

    vector<pair<string, int>> musicType;
    for (const auto& pair : musicMap) {
        int sum{};
        for (auto music : pair.second) {
            sum += music.play;
        }
        musicType.push_back({ pair.first, sum });
    }
    sort(musicType.begin(), musicType.end(), [](pair<string, int> a, pair<string, int> b) {
        return a.second > b.second;
        });
    vector<int> answer;
    for (int i = 0; i < musicType.size(); ++i) {
        string InputType = musicType[i].first;

        if (musicMap[InputType].size() == 1) {
            answer.push_back(musicMap[InputType][0].index);
        }
        else {
            answer.push_back(musicMap[InputType][0].index);
            answer.push_back(musicMap[InputType][1].index);
        }
    }

    
    return answer;
}