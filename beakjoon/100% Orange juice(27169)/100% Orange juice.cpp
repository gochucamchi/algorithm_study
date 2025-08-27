#include<iostream>
#include<cstdlib>
#include<ctime>
#include<iomanip>
using namespace std;

/*
《100% Orange Juice》는 6면체 주사위를 이용해서 최대 4명의 플레이어가 함께 플레이할 수 있는 보드게임 형태의 아케이드 게임입니다.
플레이어는 캐릭터를 하나 선택하고, 각자의 목적(스타 200개 획득, 상대방을 14번 쓰러트리기 등)을 달성하기 위해 플레이하며,
가장 먼저 목적을 달성한 플레이어가 승리합니다.

이 보드게임에는 전투 시스템이 존재합니다. 캐릭터마다 4개의 고유의 능력치 체력, 공격, 방어, 회피를 갖고 있습니다.
전투는 선공과 후공이 일대일로 수행하며 다음과 같은 방식으로 진행됩니다.
*/

/*
입력 데이터
선공 캐릭터의 체력, 공격, 방어, 회피를 나타내는 정수 값
후공 캐릭터의 체력, 공격, 방어, 회피를 나타내는 정수 값
입력 예제
4 1 -1 2
5 1 -1 1
출력 예제
0.549831898994

출력 데이터
선공이 승리할 확률을 출력합니다.
출력한 값과 정답과의 절대 오차 또는 상대 오차가 10^{-6} 이하여야 합니다.
*/

/*
문제
선공과 후공의 캐릭터 능력치가 주어지면 밸런스 측정을 위한 AI 로직을 따라서 전투를 수행했을 때 선공이 승리할 확률을 계산해봅시다.
*/

/*
전투 로직
1.선공이 공격수, 후공이 수비수가 된다.
2.공격수가 주사위를 던진다.max(1,(주사위 + 공격)) 값이 이번 공격수의 공격의 공격력이다
3. 수비수는 상대의 공격력과 자신의 방어, 회피 능력치를 보고 방어와 회피중 무엇을 할지 결정한다.
    -1 수비수가 방어를 선택했을 시
    수비수가 주사위를 던진다max(1,(주사위+방어)) 값이 이번 수비수의 방어력이다. max(1,공격력 -  방어력)만큼의 체력을 잃는다
    -2 수비수가 회피를 선택했을 시
    수비수가 주사위를 던진다.max(1,(주사위 + 회피))값이 이번 수비수의 회피력이다. 만약 회피력이 공격력보다 크면 회피에 성공한다.
    회피력이 공격력보다 작거나 같다면 회피에 실패하고 공격력만큼 체력이 까인다
4. 수비수의 체력이 0이하가 되면 공격수가 승리한다
5. 수비수의 체력이 0이하가 되지않았으면 공격수와 수비수의 역할을 바꾼다.
6. 선공과 후공이 각각 공격을 한번 씩 수행하면 전투가 종료된다
*/

/*
밸런스 측정을 위한 AI 로직 *** 변경점이 많아서 주의해야함
1.선공이 공격수, 후공이 수비수가 된다.
2.공격수가 주사위를 던진다.max(1,(주사위 + 공격)) 값이 이번 공격수의 공격의 공격력이다
3. 수비수는 상대의 공격력과 자신의 방어, 회피 능력치를 보고 방어와 회피중 무엇을 할지 결정한다.
********************************여기서 부터는 회피와 방어를 어떤 조건일 때 하는지에 대해서 규칙이 나온다************************************
    -1 만약 현재 체력이 max(1,공격력 - (6+방어))이하이면 회피를 선택한다.
    -2 그 외에 만약 공격력이 max(1,1 + 회피)미만이면 회피를 선택한다
    -3 그 외에 만약 공격력이 현재 체력이상이면 방어를 선택한다
    -4 그 외에 만약 공격력이 max(1,3 + 회피) 미만이면 회피를 선택한다.
    -5 그 외에 방어를 선택한다
*******************************다시 기존과 똑같은 규칙***************    
    -1 수비수가 방어를 선택했을 시
    수비수가 주사위를 던진다max(1,(주사위+방어)) 값이 이번 수비수의 방어력이다. max(1,공격력 -  방어력)만큼의 체력을 잃는다
    -2 수비수가 회피를 선택했을 시
    수비수가 주사위를 던진다.max(1,(주사위 + 회피))값이 이번 수비수의 회피력이다. 만약 회피력이 공격력보다 크면 회피에 성공한다.
    회피력이 공격력보다 작거나 같다면 회피에 실패하고 공격력만큼 체력이 까인다
4. 수비수의 체력이 0이하가 되면 공격수가 승리한다
5. 수비수의 체력이 0이하가 되지않았으면 공격수와 수비수의 역할을 바꾼다.
6. 승자가 정해질 때 까지 위 과정을 반복한다.
*/
/*
c++문법이 상당히 오랜만이라 헷갈려서 적는것
선언부 구현부 실행부로 보통 구현이 되고 간단한거는 한번에 선언과 구현을 동시에 만들 때도 많이 있다.
따로따로 구현하기
선언부
    void Input_status();
구현부
    void Input_status()
    {
        cin >> hp >> attack >> defense >> avoid;
    }
실행부
    Input_status();
한번에 만들기
    void Input_status(){cin >> hp >> attack >> defense >> avoid;}

객체 생성시 초기화가 필요할 때도 가능한 문법이다.
클래스 안에서 따로따로 만들기
선언부
    Player();  // 선언부만 (클래스 안에)

구현부 (클래스 밖에)
    Player::Player() : hp(100), attack(10) {
        // 추가 로직이 있으면 여기에
    }
클래스 안에서 바로 만들기
*/

class Player
{
    private: 
        
    public:
    int hp, attack, defense, avoid;
    int save_hp;
    void Input_status();

    Player();
    /*
    Player()-생성자 함수 ---->> 이게 python의 __init__과 같은 역할을 한다. 객체를 만들 때 자동으로 호출되는 특별한 함수를 뜻한다.
    */
};

class Game
{
    private:
        
    public:
        int dice;
        Player player1, player2;
        Player* attacker = &player1;
        Player* defender = &player2;
        Player* temp = 0;
        /*
        헷갈리는 포인터 문법 오랜만에 정리하기
        //선언
        Player* ptr; Player 타입을 가리키는 포인터
        int* numptr; int 타입을 가리키는 포인터
        //초기화
        Player player1;
        Player* pre = &player1; // &는 주소연산자 (player1의 주소)

        //사용
        ptr->hp = 100; //포인터로 멤버 접근(화살표 연산자)
        (*ptr).hp = 100;//위에와 같은 의미 (*는 역참조 연산자)

        //값 변경
         Player player2;
         ptr = &player2; //이제 ptr은 Player2를 가리킴
        */
        bool winner_player1();
        void rollDice();
        void battle();
};


int main()
{
    srand(time(0));
    int n = 100000;
    int player1_win = 0;
    double player_1_probability_winning= 0;
    Game game;
    game.player1.Input_status();
    game.player2.Input_status();
    game.player1.save_hp = game.player1.hp;
    game.player2.save_hp = game.player2.hp;
    while(n>0)
    {
        game.battle();
        if(game.winner_player1() == true)
        {
            player1_win++;
        }
        n--;
    }
    player_1_probability_winning = (double)player1_win/100000;
    cout << fixed << setprecision(12) << player_1_probability_winning;
    return 0;
}
bool Game::winner_player1()
{
    if(defender == &player1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Player::Input_status() //스테이터스 데이터 변수 입력받기
{
    cin >> hp >> attack >> defense >> avoid;
}

void Game::rollDice() //주사위 던지기
{
    dice = (rand() % 6) + 1;
}

void Game::battle()
{
    attacker = &player1;
    defender = &player2;
    player1.hp = player1.save_hp;
    player2.hp = player2.save_hp;
    while(true)
    {
        if (defender->hp > 0) //공격 매커니즘
        {
            //공격이 하는 행위
            int attack_score;//최종공격력
            rollDice();
            attack_score = attacker->attack+dice; // 선공주자 데미지 + 주사위데미지 = 공격력
            if(attack_score <1){attack_score = 1;}// 데미지가 1보다 작으면 최소값 1로 만들기 
            
            //이제부터는 수비수가 하는 행위
            rollDice();
            int avoid_score, defense_score;
            avoid_score = defender->avoid+dice; //최종회피점수
            if(avoid_score < 1) avoid_score = 1;
            defense_score = defender->defense+dice;//최종방어력점수
            if(defense_score < 1) defense_score = 1;

            int threshold1 = attack_score - (defender->defense+6);
            if(threshold1 < 1) threshold1 = 1;
            if(defender->hp <= threshold1)//만약 현재 체력이 max(1,공격력 - (6+방어))이하이면 회피를 선택한다.
            {//회피코드 나중에 함수화 시킬예정
                if(avoid_score <= attack_score){
                    defender->hp = defender->hp-attack_score;
                }   
            }
            else if(attack_score < (defender->avoid+1 > 1 ? defender->avoid+1 : 1))//그 외에 만약 공격력이 max(1,1 + 회피)미만이면 회피를 선택한다
            {//회피코드 나중에 함수화 시킬예정
                if(avoid_score <= attack_score){
                    defender->hp = defender->hp-attack_score;
                }
            }
            else if(attack_score >= defender->hp)//그 외에 만약 공격력이 현재 체력이상이면 방어를 선택한다
            {//방어 코드 나중에 함수화해서 player2뿐만아니라 인자값으로 player1이든 2든 가능하게 통일 시킬예정
                if(attack_score-defense_score < 1)
                {
                    defender->hp -= 1;
                }
                else
                {
                    defender->hp -= attack_score-defense_score;
                }
            }
            else if(attack_score < (defender->avoid+3 > 1 ? defender->avoid+3 : 1))//그 외에 만약 공격력이 max(1,3 + 회피)미만이면 회피를 선택한다
            {//회피코드 나중에 함수화 시킬예정
                if(avoid_score <= attack_score){
                    defender->hp = defender->hp-attack_score;
                }
            }
            else//그외에 방어하기
            {
                //방어 코드 나중에 함수화해서 player2뿐만아니라 인자값으로 player1이든 2든 가능하게 통일 시킬예정
                if(attack_score-defense_score < 1)
                {
                    defender->hp -= 1;
                }
                else
                {
                    defender->hp -= attack_score-defense_score;
                }
            }
        }
        
        if(defender->hp <= 0)
        {
            break;
        }
        else
        {
        Player* temp_ptr = defender;
        defender = attacker;
        attacker = temp_ptr;
        }
    }
}
//생성자
Player::Player():
hp(0), attack(0), defense(0), avoid(0)
{

}