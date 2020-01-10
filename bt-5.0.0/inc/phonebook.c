#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inc/btree.h"
#include "inc/bt.h"
int main()
{
	int x,i,n,size;
	long sdt;
	char name[80];
	BTA* book;
	do{
		scanf("%d",&x);
		if(x==1){
			btinit();
			book=btopn("mybook",0,0);
			if(!book)
			{
				printf("creat\n");
				book=btcrt("book",0,0);
				printf("inseet\n");
				sdt=98345678;
				if(btins(book,"Dung",(char*)&sdt,sizeof(long)))
					printf("error\n");
			}
		}
		/*if(x==2)
		{
			printf("name\n");
			gets(name);
			if(btsel(book,name,(char*)&sdt,sizeof(long)))
		}*/
	
	}while(x!=5);
}