#include<stdio.h>
int main()
{
FILE *fp;
int i,j;
fp=fopen(".\a.txt","r");
while (fscanf(fp,"%d%d",&i,&j)!=EOF)
{
printf("i=%d et j=%d \n",i,j);
}
fclose(fp);
}
