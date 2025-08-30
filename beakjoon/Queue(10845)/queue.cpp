#include<iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int * queue = new int[n];
    for(int i=0; i<n; i++)
    {
        queue[i] = 0;
    }
    string command;
    int value;
    //위 예시는 int의 n개 크기만큼 메모리를 new! 만들어서 달라는겁니다.
    /*
     int * queue = new int[n];
  //   ^
  //   포인터 선언의 *

    이렇게 읽으면 됩니다:
    - int * : "int를 가리키는 포인터"
    - queue : 변수명
    - new int[n] : n개 크기의 int 배열을 동적할당하고 첫 번째 주소 반환

    *곱하기 와 구별하는 법:
    // 포인터 선언 (타입 다음에 *)
    int* ptr;
    int * ptr2;  // 띄어쓰기 있어도 같음

    // 곱하기 (변수/숫자 사이에 *)
    int result = a * b;

    동적할당의 전체 흐름:
    int* queue = new int[n];  // 할당
    queue[0] = 10;           // 사용
    delete[] queue;          // 해제
    */
    for(int i=0; i<n; i++)
    {
        cin >> command;
        if(command == "push")
        {
            cin >> value;
            for(int j=0; j<n; j++)
            {
                if(queue[j] == 0)
                {
                    queue[j] = value;
                    break;
                }
            }
        }
        if(command == "pop")
        {
            if(queue[0] == 0)
            {
                cout << -1 << endl;
                continue;
            }
            else
            {
                cout << queue[0] << endl;
            }

        for(int j=0; j<n; j++)
        {
            if(j == n-1)
            {
                queue[j] = 0;  // 마지막 원소를 0으로
                break;
            }

            queue[j] = queue[j+1]; // 앞으로 당겨옴
            if(queue[j] == 0) // 당겨온 게 0이면
            {
                break;
            }
        }

        }
        if(command == "size")
        {
            int count = 0;
            for(int j=0; j<n; j++)
            {
                if(queue[j] == 0)
                {
                    count = j;
                    break;
                }
            }
            cout << count << endl;
        }
        if(command == "empty")
        {
            if(queue[0] == 0)
            {
                cout << 1 << endl;
            }
            else
            {
                cout << 0 << endl;
            }
        }
        if(command == "front")
        {
            if(queue[0] == 0)
            {
                cout << -1 << endl;
            }
            else
            {
                cout << queue[0] << endl;
            }
        }
        if(command == "back")
        {
            if(queue[0] == 0)
            {
                cout << -1 << endl;
            }
            else
            {
                int back;
                for(int j=0; j<n; j++)
                {
                    if(queue[j] == 0)
                    {
                        back = j-1;
                        break;
                    }
                    if(j == n-1)
                    {
                        back = j;
                    }
                }
                cout << queue[back] << endl;
            }
        }
    }
    
}