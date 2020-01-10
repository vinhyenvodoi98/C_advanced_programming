#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int float_compare(const void *x,const void *y)
{
	int m,n;
	m=*((float*)x);
	n=*((float*)y);
	if(m==n) return 0;
	return m>n?1:-1;
}

float search(void *buf,int size,int l,int r,void *item, int(*compare)(const void*,const void*) )
{
	if(r<l) return -1;
	int i =(l+r)/2;
	int res=compare(item,(char *)buf +(size*i));
	if(res==0)
		return i;
	else if(res <0)
		return search(buf,size,l,i-1,item,compare);
	else if(res >0)
		return search(buf,size,i+1,r,item,compare);
}
int main ()
{
	float values[100];
	for(int i=0;i<100;i++)
		values[i]=rand()%100;
   	float item;
   	float key = 39;
   	qsort(values,100,sizeof (int), float_compare);
   	for(int i=0;i<100;i++)
   		printf("%f \n",values[i] );
   	item=  search(values, sizeof(float),0,100,&key,float_compare);
   	printf("%f\n",item );   	
   	return(0);
}