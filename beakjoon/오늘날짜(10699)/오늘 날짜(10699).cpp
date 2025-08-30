#include <iostream>
#include <ctime>

int main() {
    // 현재 시간을 초 단위로 가져옵니다. (1970년 1월 1일 0시 0분 0초 기준)
    time_t curr_time = time(nullptr);

    // 로컬 시간으로 변환합니다. (time_t를 tm 구조체로 변환)
    tm* curr_tm = localtime(&curr_time);

    // 서울 날짜를 YYYY-MM-DD 형식으로 출력합니다.
    std::cout << curr_tm->tm_year + 1900 << "-"
              << curr_tm->tm_mon + 1 << "-"
              << curr_tm->tm_mday << std::endl;

    return 0;
}