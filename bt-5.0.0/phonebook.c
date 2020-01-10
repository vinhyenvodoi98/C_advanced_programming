#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inc/btree.h"
#include "inc/bt.h"
int main()
{
	int x,i,n,size;
	long sdt,sdt1;
	char bname[30],name[80];
	BTA* book;
		btinit();	
	do{
		
		printf("nhan 0 de tao hoac truy cap phonebook \n");
		printf("nhan 1 de them vao phonebook\n");
		printf("nhan 2 de tim kiem bang ten\n");
		printf("nhan 3 de chinh sua sdt bang ten\n");
		printf("nhan 4 de xem toan bo\n");
		printf("nhan 5 de thoat phonebook hien tai\n");
		scanf("%d",&x);
		if(x==0){
			printf("nhap ten sach \n");
			scanf("%*c");scanf("%[^\n]",bname);
			book=btopn(bname,0,0);
		if(!book)
			{
				printf("khoi tao sach\n");
				book=btcrt(bname,0,0);
			}
		}
		if(x==1){
				printf("them vao\n");
				while(1){
				scanf("%ld",&sdt);
				if(sdt==1) break;
				scanf("%*c");scanf("%[^\n]",name);
				if(btins(book,name,(char*)&sdt,sizeof(long))) 
					{
					printf("error\n");
					break;
					}

				}
		}
		//btdel(BTA* btact, char* key); xoa key va data
		if(x==2)
		{
			printf("nhap ten tim kiem: \n");
			scanf("%*c");scanf("%[^\n]",name);
			if(btsel(book,name,(char*)&sdt,sizeof(long),&size))
				printf("not found number\n");
			else
				printf("phone number of %s %d \n",name,sdt );
		}
		if(x==3)
		{
			printf("nhap ten de sua: \n");
			scanf("%*c");scanf("%[^\n]",name);
			if(btsel(book,name,(char*)&sdt,sizeof(long),&size))
				printf("not found number\n");
			else
			{
				printf("so dien thoai cap nhat: \n");
				scanf("%ld",&sdt);
				btupd(book,name,(char*)&sdt,sizeof(long));
			}
		}
		if(x==4)
		{
			btsel(book,"",(char*)&sdt,sizeof(long),&size);
			while(btseln(book,name,(char*)&sdt1,sizeof(long),&size)==0)
			{
				printf("%s %d\n",name,sdt1 );
			}
		}
		if(x==5)
		{
			btcls(book);
		}
	}while(x!=6);
}