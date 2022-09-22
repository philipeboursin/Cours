#include<stdio.h>

int increment()
{
	static int c=4;
	c++;
	return c;
}

int decrement()
{
	static int c=4;
	c--;
	return c;
}

int main()
{
	increment();
	decrement();
	printf("%d\n", increment());
	printf("%d\n", decrement());
}
