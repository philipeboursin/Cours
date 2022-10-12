#include<stdio.h>

int f1()
{
    return 2;
}

int f2()
{
    for (int i = 1; i < 100000; i++);
    return 2;
}


int main()
{
    int res;
    for (int i = 0; i < 1000; i++)
    {
        res = f2();
    }
}