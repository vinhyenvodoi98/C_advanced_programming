#include<stdio.h>
#include<stdlib.h>   
#include<string.h>
#include<time.h>
#define swap(type, a, b) {type temp = a; a = b; b = temp; } 

void quickSort1(int a[], int l, int r) // 2way
{
    int key;
    key = a[l];
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

void quickSort(int a[], int l, int r) // 3way
{
    int key;
    key = a[r];
    int i = l, j = r-1;
    int p = l ,q = r-1;
    int k;
    while(i <= j)
    {
        
        while(a[i] < key) { if(i==r) break; i++;}
        while(a[j] > key) { if(j==l) break; j--;}
        if(i <= j)
        {
            if(i < j)          swap(int, a[i], a[j]);
            if(j==l || i==r) break;
            if(a[i] == key)    {swap(int, a[p], a[i]); p++;}
            if(j<=p-1) { i++; break;}
            if(a[j] == key)    {swap(int, a[q], a[j]); q--;} 
            if(i==j && i==l) break;
            if(i==j ){i++;break;}
            i++;
            j--;
            if(p==q) break;

        }

    }
    swap(int, a[r], a[i]);i++;
    if(q!=r-1)  for(k=q+1;k<=r-1;k++)   {swap(int ,a[i],a[k]);i++;}
    if(p!=l)    for(k=p-1;k>=l;k--)     {swap(int ,a[j],a[k]);j--;}
    if (l < j) quickSort(a, l, j);  
    if (i < r-1) quickSort(a, i, r);
}
int main ()
{
    int i, arr[] = {1,1,2,4,7,5,7,4,1,2,5,9,5,4,2,1,5};
    quickSort(arr, 0,16);
    for (i=0; i<17; i++)
        printf ("%d ", arr[i]);
    return 0;
}

/*int main ()
{
    int i;
    int arr[1000];
    FILE *f;
    f=fopen("songuyen.txt","rt");
    for(i=0 ;i< 1000; i++)
    {
        fscanf(f,"%d ", &arr[i]);     
    }
    fclose(f);
    quickSort(arr, 0,999);
    for (i=0; i<1000; i++)
        printf ("%d ", arr[i]);
}*/
