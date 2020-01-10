#include <stdio.h>
#include "jval.h"
void swap(Jval *a,Jval *b) 
{
    Jval *temp = a; 
    a = b;
    b = temp; 
}
void in(Jval a, int n)
{
	for(int i=0;i<n;i++)
	{
		printf("%d ",a.iarray[i]);
	}
}
int int_compare( Jval *x, Jval *y)
{
	int m,n;
	m=*((int*)x);
	n=*((int*)y);
	if(m==n) return 0;
	return m>n?1:-1;
}

void quickSort(Jval a, int l, int r,int(*compare)( Jval*, Jval*))
{
    Jval key = new_jval_i(a.iarray[r]);
    int temp;
	int i = l, j = r-1;
    int p = l ,q = r-1;
    int k;
    while(i <= j)
    {
        
        while(a.iarray[i]<jval_i(key)) { if(i==r) break; i++;}
        while(a.iarray[j]>jval_i(key)) { if(j==l) break; j--;}
        if(i <= j)
        {
            if(i < j)          {temp = a.iarray[i]; a.iarray[i] = a.iarray[j]; a.iarray[j] = temp;}
            if(j==l || i==r) break;
            if(a.iarray[i]==jval_i(key))   {temp = a.iarray[p]; a.iarray[p] = a.iarray[i]; a.iarray[i] = temp; p++;}
            if(j<=p-1) { i++; break;}
            if(a.iarray[j]==jval_i(key))    {temp = a.iarray[q]; a.iarray[q] = a.iarray[j]; a.iarray[j] = temp; q--;} 
            if(i==j && i==l) break;
            if(i==j ){i++;break;}
            i++;
            j--;
            if(p==q) break;
        }

    }
    temp = a.iarray[r]; a.iarray[r] = a.iarray[i]; a.iarray[i] = temp;;i++;
    if(q!=r-1)  for(k=q+1;k<=r-1;k++)   {temp = a.iarray[i]; a.iarray[i] = a.iarray[k]; a.iarray[k] = temp;i++;}
    if(p!=l)    for(k=p-1;k>=l;k--)     {temp = a.iarray[j]; a.iarray[j] = a.iarray[k]; a.iarray[k] = temp;j--;}
    if (l < j) quickSort(a, l , j , int_compare);  
    if (i < r-1) quickSort(a, i , r , int_compare);
}
/*Jval search(Jval a, int l, int r,Jval item,int(*compare)( Jval*, Jval*))
{
    Jval key=new_jval_i(a.iarray[(l+r)/2]);
    int i = l, j = r;
    while(i<=j)
    {
        if(jval_i(item)<jval_i(key)) search(a,l,jval_i(key),item,)
    }    
}search */ 
int main()
{
	int n,k;
	Jval a[10];
	printf("nhap so luong phan tu: ");
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%d",&k);
		a.iarray[i]=k;
	}
	quickSort(a,0,n-1,int_compare);
	in(a,n);
    printf("nhap phan tu muon tim kiem: \n");
    scanf("%d",&n);
    search(a,0,n-1,int_compare);
    printf("%s\n", );
	return 0;

}

