#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "jval.h"


int main()
{
	int i,n,x;
	char name[80];
	long sdt;
	
	JRB book,node;
	book =make_jrb();
	while(1){
		printf("1. nhap \n");
		printf("2. add\n");
		printf("3. delete\n");
		printf("4. modify phone number \n");
		scanf("%d",&x);
		if(x==1)
		{
			FILE *f;
			f=fopen("gia.txt","rt");
			while(1)
			{	
				if(fscanf(f,"%s\t%ld",name,&sdt)==EOF) break;
				jrb_insert_str(book,strdup(name),new_jval_i(sdt));
			}
			fclose(f);
			printf("da cap nhat phonebook \n");
		}
		if(x==2)
		{
			printf("nhap ten :\n");
			scanf("%*c");scanf("%[^\n]",name);
			node=jrb_find_str(book, name);
			if(node==NULL)
			{
				printf("nhap sdt :\n");
				scanf("%ld",&sdt);
				jrb_insert_str(book,strdup(name),new_jval_v(sdt));
			}
			else
				printf("ten nay da ton tai\n");

		}
		if(x==3)
		{
			printf("nhap ten muon xoa\n");
			scanf("%*c");scanf("%[^\n]",name);
			node=jrb_find_str(book, name);
			if(node!=NULL)
				{
					jrb_delete_node(node);
					printf("da xoa thanh cong\n");
				}
			else
				printf("khong ton tai ten trong danh sach\n");
		}
		if(x==4)
		{
			printf("nhap ten muon xoa\n");
			scanf("%*c");scanf("%[^\n]",name);
			node=jrb_find_str(book, name);
			if(node!=NULL)
			{
				printf("nhap sdt moi: \n");
				scanf("%ld",&sdt);
				node->val=new_jval_v(sdt);
			}
			else
				printf("khong ton tai ten trong danh sach\n");
		}
		if(x==5)
		{
			jrb_traverse(node,book)
			printf("%s\t%d\n",jval_s(node->key),jval_i(node->val));
		}
		if(x==6)
			break;

	}
	
}