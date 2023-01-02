#include<stdio.h>

int main()
{
    int N=45;
    int n=(N>>1);
    n=n+(N&1);
    printf("%d \n",n);

}