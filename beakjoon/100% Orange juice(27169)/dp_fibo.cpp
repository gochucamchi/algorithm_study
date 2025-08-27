#include<iostream>

using namespace std;

int fibo_data[100];
int fibonacci(int x)
{
    if(x <= 2)
    {
        return 1;
    }
    if(fibo_data[x] != 0)
    {
        return fibo_data[x];
    }
    else
    {
        fibo_data[x] = fibonacci(x-1) + fibonacci(x-2);
        return fibo_data[x];
    }
}

int main(void)
{
    cout << fibonacci(30);
    return 0;
}