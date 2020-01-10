#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int int_compare( void const *x, void const *y)
{
	int m,n;
	m=*((int*)x);
	n=*((int*)y);
	if(m==n) return 0;
	return m>n?1:-1;
}
void swap(void *a,void *b, size_t size)
{
	void *temp=malloc(size);
	memcpy(temp,a,size);
	memcpy(a,b,size);
	memcpy(b,temp,size);
	free(temp);

}
void quickSort(void *base, int first, int last, size_t memSize, int (* int_compare)(const void *, const void *)) //3way
{
    char *carray = (char *)base;
    int i=first,j=last-1;
   	int p=first,q=last-1,k;
    while( i<=j )
    {
    	while(int_compare(&carray[i * memSize], &carray[last * memSize]) < 0) {if(i==last) break;i++;}
    	while(int_compare(&carray[j * memSize], &carray[last * memSize]) > 0) {if(j==first) break;j--;}
    	if( i<=j )
    	{
    		if(i<j) swap(&carray[i*memSize], &carray[j*memSize],memSize);
    		if(j==first || i==last) break;
    		if(int_compare(&carray[i * memSize], &carray[last * memSize]) == 0) {swap(&carray[p*memSize], &carray[i*memSize],memSize);p++;}
    		if(j<p-1){i++;break;}
    		if(int_compare(&carray[j * memSize], &carray[last * memSize]) == 0) {swap(&carray[q*memSize], &carray[j*memSize],memSize);q--;}
    		if(i==j && i==first) break;
    		if(i==j) {i++;break;}
    		i++;
    		j--;
    		if(p==q) break;
    	}
       
    }
    swap(&carray[i * memSize], &carray[last * memSize],memSize);i++;
    if(q!=last-1) for(k=q+1;k<=last-1;k++) {swap(&carray[i*memSize], &carray[k*memSize],memSize);i++;}
    if(p!=first) for(k=p-1;k>=first;k--) {swap(&carray[j*memSize], &carray[k*memSize],memSize);j--;}
    if(first<j) quickSort(base,first,j,sizeof(int),int_compare);
    if(i<last-1) quickSort(base,i,last,sizeof(int),int_compare);

}
int main ()
{
    int i, arr[] = {1,1,2,4,7,5,7,4,1,2,5,9,5,4,2,1,5};
    quickSort(arr, 0,16,sizeof(int),int_compare);
    for (i=0; i<17; i++)
        printf ("%d ", arr[i]);
    return 0;
}
