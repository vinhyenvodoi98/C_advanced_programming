#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inc/btree.h"


int main()
{
	int x,i,n,size,mem,sai=0;
	char bname[30],word[40],nghia[5000],nghia1[400];
	BTA* book;
	btinit();	
	do{
		
		printf("nhan 0 de tao hoac truy cap phonebook \n");
		printf("nhan 1 de them vao phonebook\n");
		printf("nhan 2 de tim kiem bang ten\n");
		printf("nhan 3 de chinh sua sdt bang ten\n");
		printf("nhan 4 de xem toan bo\n");
		printf("nhan 5 de thoat phonebook hien tai\n");
		printf("nhan 6 de xoa\n");
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
			printf("nhap tu\n");
			scanf("%*c");scanf("%[^\n]",word);
			printf("nhap nghia cua tu:\n");
			scanf("%*c");scanf("%[^\n]",nghia);
        		if(btins(book,word,nghia,strlen(nghia)+1)) 
					{
					printf("error\n");
					}
			printf("da cap nhat diem\n");
		}
		
		//btdel(BTA* btact, char* key); xoa key va data
		if(x==2)
		{
			printf("nhap ten tim kiem: \n");
			scanf("%*c");scanf("%[^\n]",word);
			if(btsel(book,word,nghia,300,&size))
				printf("not found number\n");
			else
				printf("phone number of %s\n%s \n",word,nghia );
		}
		if(x==3)
		{
			printf("nhap ten de sua: \n");
			scanf("%*c");scanf("%[^\n]",word);
			if(btsel(book,word,nghia,300,&size))
				printf("not found number\n");
			else
			{
				printf("cap nhat nghia\n");
				scanf("%*c");scanf("%[^\n]",nghia);
				btupd(book,word,nghia,sizeof(char));
			}
		}
		if(x==4)
		{
			btsel(book,"",nghia,sizeof(char*),&size);
			while(btseln(book,word,nghia1,5000,&size)==0)
			{
				printf("%s \n%s\n",word,nghia1);
			}
		}
		if(x==5)
		{
			btcls(book);
		}
		if (x==6)
		{
			printf("nhap tu\n");
			scanf("%*c");scanf("%[^\n]",word);
			btdel(book, word);// xoa key va data
		}
		if (x==8)
		{
			btsel(book,"",nghia,300,&size);
			while(btseln(book,word,nghia,300,&size)==0)
			{
				btdel(book, word);
			}
		}
	}while(x!=7);
}