#include<stdio.h>
#include<stdlib.h>
#include<time.h>      
#define swap(type, a, b) {type temp = a; a = b; b = temp; }
 
void quickSort1(int *a, int l, int r)  //2way
{
    srand(time(NULL));
    int key = a[l + rand() % (r-l+1)];
    int i = l, j = r;
 
    while(i <= j)
    {
        while(a[i] < key) i++;      
        while(a[j] > key) j--;      
        if(i <= j)
        {
            if (i < j)
                swap(int, a[i], a[j]); 
            i++;
            j--;
        }
    }
    if (l < j) quickSort1(a, l, j);
    if (i < r) quickSort1(a, i, r);
}


void quickSort(int *a, int l, int r)  //3way
{
    srand(time(NULL));
    int x=l + rand() % (r-l+1);
    int key = a[x];
    printf("%d %d \n",key, x );
    int i = l, j = r;
    int p=l,q=r,k;
    while(i <= j)
    {
        while(a[i] < key) i++;      
        while(a[j] > key) j--;      
        if(i <= j)
        {
            if (i < j) swap(int, a[i], a[j]); 
            if(j==l || i==r) break;
            if(a[i] == key)    {swap(int, a[p], a[i]); p++;}
            if(j<p) { i++; break;}
            if(a[j] == key)    {swap(int, a[q], a[j]); q--;} 
            if(i==j && i==l) break;
            if(i==j ){i++;break;}
            i++;
            j--;
            if(p==q) break;
        }
    }
    if(q!=r)  for(k=q+1;k<=r-1;k++)   {swap(int ,a[i],a[k]);i++;}
    if(p!=l)    for(k=p-1;k>=l;k--)     {swap(int ,a[j],a[k]);j--;}
    if (l < j) quickSort(a, l, j);
    if (i < r) quickSort(a, i, r);
}
int main ()
{
    int i, arr[] = { 1,1,2,4,7,5,7,4,1,2,5,9,5,4,2,1,5};
    quickSort(arr, 0,16);
    for (i=0; i<17; i++)
        printf ("%d ", arr[i]);
    return 0;
}
