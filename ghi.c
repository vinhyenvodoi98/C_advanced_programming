#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void main()
{
	FILE *f;
	time_t t;
	f=fopen("songuyen.txt","wt");
	srand((unsigned) time(&t));
	for(int i;i<=10000;i++)
	{
		fprintf(f, "%d\t", rand() % 10);
	}
	fclose(f);
}