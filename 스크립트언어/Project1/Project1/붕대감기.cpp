#include <string>
#include <vector>
#include<algorithm>
using namespace std;
struct Monster {
    int attackTime;
    int damage;

};

int solution(vector<int> bandage, int health, vector<vector<int>> attacks) {
    int answer = 0;

    // 시전시간
    int bandageTime = bandage[0];
    // 초당 회복량
    int healPerSecond = bandage[1];
    // 추가회복량
    int bonusHealth = bandage[2];

    vector<Monster> monsters;
    for (auto m : attacks) {
        Monster Mon;
        Mon.attackTime = m[0];
        Mon.damage = m[1];
        monsters.emplace_back(Mon);
    }
    int prevTime{};
    int currentHealth = health;
    for (int i = 0; i < monsters.size(); ++i) {
        if (i == 0) {
            prevTime = monsters[i].attackTime;
            currentHealth -= monsters[i].damage;
        }
        else {
            // 마지막 공격 이후 지속적으로 붕대 감은 시간.
            int Htime = monsters[i].attackTime - prevTime - 1;
            prevTime = monsters[i].attackTime;

            currentHealth += Htime * healPerSecond;

            if (Htime >= bandageTime) {
                int bonusNum = Htime / bandageTime;
                currentHealth += bonusNum * bonusHealth;
            }
            if (currentHealth > health) {
                currentHealth = health;
            }

            // 몬스터 공격 처리
            currentHealth -= monsters[i].damage;
            if (currentHealth <= 0) {
                return -1;
            }

        }
    }

    // 죽는다면 -1
    return currentHealth;
}