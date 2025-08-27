#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <map>
#include <utility> // std::pair 사용을 위해 추가

using namespace std;

// Player의 스탯 정보를 담는 구조체
struct PlayerStatus {
    int hp, attack, defense, avoid;
};

// 전역 변수
PlayerStatus p1_stats, p2_stats;
double memo[101][101][2];
bool visiting[101][101][2];

// 반환 타입을 pair로 수정: {계수 map, 상수항 double}
pair<map<pair<int, int>, double>, double> solve(int hp1, int hp2, int turn);

// AI 로직 함수 (편의를 위해 분리)
bool should_evade(int current_hp, int attack_power, const PlayerStatus& defender_stats) {
    int threshold1 = max(1, attack_power - (defender_stats.defense + 6));
    if (current_hp <= threshold1) return true;
    if (attack_power < max(1, 1 + defender_stats.avoid)) return true;
    if (attack_power >= current_hp) return false;
    
    // ★★★ 이 부분의 숫자 '3'을 다른 숫자로 바꿔서 테스트 ★★★
    if (attack_power < max(1, 1 + defender_stats.avoid)) return true; // 예를 들어 3을 4로
    
    return false;
}
pair<map<pair<int, int>, double>, double> solve(int hp1, int hp2, int turn) {
    if (hp1 <= 0) return {{}, 0.0};
    if (hp2 <= 0) return {{}, 1.0};

    if (memo[hp1][hp2][turn] > -0.5) {
        return {{}, memo[hp1][hp2][turn]};
    }

    if (visiting[hp1][hp2][turn]) {
        map<pair<int, int>, double> cycle_coeffs;
        cycle_coeffs[{hp1, hp2}] = 1.0;
        return {cycle_coeffs, 0.0};
    }

    visiting[hp1][hp2][turn] = true;

    PlayerStatus& attacker_stats = (turn == 0) ? p1_stats : p2_stats;
    PlayerStatus& defender_stats = (turn == 0) ? p2_stats : p1_stats;

    map<pair<int, int>, double> combined_coeffs;
    double constant_term = 0.0;

    for (int attack_dice = 1; attack_dice <= 6; ++attack_dice) {
        int attack_power = max(1, attacker_stats.attack + attack_dice);
        bool evade_decision = should_evade((turn == 0) ? hp2 : hp1, attack_power, defender_stats);

        for (int defend_dice = 1; defend_dice <= 6; ++defend_dice) {
            int next_hp1 = hp1;
            int next_hp2 = hp2;

            if (evade_decision) {
                int evade_power = max(1, defender_stats.avoid + defend_dice);
                if (evade_power <= attack_power) {
                    if (turn == 0) next_hp2 -= attack_power;
                    else next_hp1 -= attack_power;
                }
            } else {
                int defense_power = max(1, defender_stats.defense + defend_dice);
                int damage = max(1, attack_power - defense_power);
                if (turn == 0) next_hp2 -= damage;
                else next_hp1 -= damage;
            }

            auto result = solve(next_hp1, next_hp2, 1 - turn);
            
            // result.first는 map, result.second는 double
            for (auto const& [state, coeff] : result.first) {
                combined_coeffs[state] += coeff / 36.0;
            }
            constant_term += result.second / 36.0;
        }
    }

    // 자기 자신에 대한 계수가 있는지 확인 (순환 발생)
    if (combined_coeffs.count({hp1, hp2})) {
        int other_turn = 1 - turn;
        
        // 상대 턴의 계수와 상수를 계산하기 위해 solve 호출
        auto other_result_pair = solve(hp1, hp2, other_turn);
        
        double a = combined_coeffs[{hp1, hp2}];
        double c1 = constant_term;
        
        double b = other_result_pair.first[{hp1, hp2}];
        double c2 = other_result_pair.second;

        if (turn == 1) {
            swap(a, b);
            swap(c1, c2);
        }

        double final_prob_x, final_prob_y;
        if (abs(1.0 - a * b) < 1e-12) {
             final_prob_x = 0.0; // 분모가 0이면 무한루프, 승리 아님
        } else {
             final_prob_x = (a * c2 + c1) / (1.0 - a * b);
        }
        final_prob_y = b * final_prob_x + c2;

        memo[hp1][hp2][0] = final_prob_x;
        memo[hp1][hp2][1] = final_prob_y;

    } else {
        memo[hp1][hp2][turn] = constant_term;
    }

    visiting[hp1][hp2][turn] = false;
    return {{}, memo[hp1][hp2][turn]};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> p1_stats.hp >> p1_stats.attack >> p1_stats.defense >> p1_stats.avoid;
    cin >> p2_stats.hp >> p2_stats.attack >> p2_stats.defense >> p2_stats.avoid;

    for (int i = 0; i <= 100; ++i) {
        for (int j = 0; j <= 100; ++j) {
            memo[i][j][0] = -1.0;
            memo[i][j][1] = -1.0;
        }
    }
    
    // solve 결과값(pair)의 두 번째 요소(.second)가 최종 확률
    double result = solve(p1_stats.hp, p2_stats.hp, 0).second;

    cout << fixed << setprecision(12) << result << endl;

    return 0;
}