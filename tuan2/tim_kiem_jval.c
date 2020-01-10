#include <stdio.h>
#include "jval.h"

void quickSort(Jval a, int l, int r,int(*compare)( Jval*, Jval*));
int search(Jval a, int l, int r, int item,int(*compare)(Jval*,Jval*));

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
int search(Jval a, int l, int r, int item, int (*compare)(Jval*,Jval*))
{
    int mid=(l+r)/2;
    if(l==mid) return -1;
    if(a.iarray[mid]<item)
        search(a,mid+1,r,item,int_compare);
    if(a.iarray[mid]>item)
        search(a,l,mid-1,item,int_compare);
    if(a.iarray[mid]==item)
        return a.iarray[mid];
    
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
int main()
{
	int n,k,item;
    Jval a;

	printf("nhap so luong phan tu: ");
	scanf("%d",&n);
    
	for(int i=0;i<n;i++)
	{
		scanf("%d",&k);
		a.iarray[i]=k;
	}
    quickSort(a,0,n-1,int_compare);
    printf("da sap xep\n");
    printf("nhap phan tu muon tim \n");
    scanf("%d",&item);
    item=search(a,0,n-1,item,int_compare);
    if(item==-1)    printf("ko ton tai phan tu nay\n");
    else printf("%d\n",item);
	return 0;

}

