#include<stdio.h>

char time[21][25]={"zero","one","two","three",\
				"four","five","six","seven",\
				"eight","nine","ten","eleven",\
				"twelve","thirteen","fourteen","fifteen","sixteen",\
				"seventeen","eighteen","nineteen","twenty"};
char arr[6][25]={"0","0","twenty","thirty","forty","fifty"};

void printfh(int h)
{
	if(h<=20)
	{
		printf("%s",time[h]);
	}
	else
	{
		printf("%s %s",time[20],time[h%20]);
	}
}

void printfm(int m)
{
	if(m<=20)
	{
		printf("%s",time[m]);
	}
	else
	{
		printf("%s %s\n",arr[m/10],time[m-(m/10*10)]);
	}
}
int main()
{
	int h,m;
	scanf("%d%d",&h,&m);
	
	if(m==0)
	{
		printfh(h);
		printf(" o'clock\n"); 
		return 0;
	}
	
	printfh(h);
	
	printf(" ");
	
	printfm(m);
}				
