#include <iostream>
using namespace std;
int fibo(int n);

int main()
{
    int n;
    cin >> n;
    int a=0;
    a = fibo(n);
    cout << a <<endl;
}
int fibo(int n)
{
    if(n <= 2)
    {
        return 1;
    }
    else
    {
        return fibo(n-1) + fibo(n-2);
    }
}