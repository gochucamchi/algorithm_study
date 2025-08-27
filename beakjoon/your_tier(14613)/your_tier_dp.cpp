#include<iostream>
using namespace std;

/*
DP를 사용한 your_tier 문제 해결

dp[게임수][승리수][패배수] = 해당 상태에 도달할 확률

점화식:
dp[i+1][win+1][lose] += dp[i][win][lose] * W;  // 승리
dp[i+1][win][lose+1] += dp[i][win][lose] * L;  // 패배  
dp[i+1][win][lose] += dp[i][win][lose] * D;    // 무승부
*/

double dp[21][21][21];  // [게임수][승리수][패배수]
double w, l, d;

void solve_with_dp() {
    // 초기 상태: 0게임, 0승, 0패
    dp[0][0][0] = 1.0;
    
    // 20게임까지 진행
    for(int game = 0; game < 20; game++) {
        for(int win = 0; win <= game; win++) {
            for(int lose = 0; lose <= game - win; lose++) {
                if(dp[game][win][lose] == 0) continue;
                
                double current_prob = dp[game][win][lose];
                
                // 다음 게임에서 승리
                if(win + 1 <= 20) {
                    dp[game+1][win+1][lose] += current_prob * w;
                }
                
                // 다음 게임에서 패배  
                if(lose + 1 <= 20) {
                    dp[game+1][win][lose+1] += current_prob * l;
                }
                
                // 다음 게임에서 무승부 (승리수, 패배수 변화 없음)
                dp[game+1][win][lose] += current_prob * d;
            }
        }
    }
    
    // 20게임 후 각 티어별 확률 계산
    double bronze = 0, silver = 0, gold = 0, platinum = 0, diamond = 0;
    
    for(int win = 0; win <= 20; win++) {
        for(int lose = 0; lose <= 20 - win; lose++) {
            double prob = dp[20][win][lose];
            if(prob == 0) continue;
            
            int score_diff = win - lose;  // 승리수 - 패배수
            
            // 각 티어별로 확률 누적 (w-l 기준)
            if(score_diff <= -11) {  // 브론즈: -20 ~ -11
                bronze += prob;
            }
            else if(score_diff >= -10 && score_diff <= -1) {  // 실버: -10 ~ -1
                silver += prob;
            }
            else if(score_diff >= 0 && score_diff <= 9) {  // 골드: 0 ~ 9
                gold += prob;
            }
            else if(score_diff >= 10 && score_diff <= 19) {  // 플래티넘: 10 ~ 19
                platinum += prob;
            }
            else if(score_diff == 20) {  // 다이아: 20
                diamond += prob;
            }
        }
    }
    
    cout << bronze << endl;
    cout << silver << endl;
    cout << gold << endl;
    cout << platinum << endl;
    cout << diamond << endl;
}

int main() {
    cin >> w >> l >> d;
    
    cout << fixed;
    cout.precision(8);
    
    solve_with_dp();
    
    return 0;
}

/*
DP 접근법의 장점:
1. 직관적: 게임을 하나씩 진행하면서 상태를 업데이트
2. 이해하기 쉬움: 각 단계별로 확률이 어떻게 변화하는지 명확
3. combination 함수 불필요: 확률을 직접 누적하여 계산

시간복잡도: O(20 * 21 * 21) = O(8820) - 매우 효율적
공간복잡도: O(21 * 21 * 21) = O(9261)
*/