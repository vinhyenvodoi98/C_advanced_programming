#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jval.h"
#include "jrb.h"

JRB tao();
JRB tao()
{
	make_jrb();
}

int main()
{
	int x,v1,v2,n;
	JRB g,node;
	jval tree;
	g = tao();
	do{
		printf("1,nhap vao cac canh cua do thi \n");
		printf("2,nhap quan he giua cac dinh \n");
		printf("3,tim kiem cac quan he\n");
		printf("4,\n");
		printf("5,xoa\n");
		scanf("%d",&x);
		if(x==1)
		{
			printf("nhap vao so luong nut: \n");
			scanf("%d",&n);
			for(int i=0;i<n;i++)
			{
				scanf("%d",&v1);
				jrb_insert_int(g, v1 ,NULL);
			}
		}
		if(x==2)
		{	
			while(1)
			{
				printf("nhap vao canh tao quan he\n");
				scanf("%d",&v1);
				if(v1==-1) break;
				node=jrb_find_int(g,v1);
				if(node==NULL) printf("khong ton tai canh nay \n");
				else{
					while(1)
					{
						printf("nhap vao quan he cua canh %d vs canh: \n" );
						scanf("%d",&v2);
						if(v2==-1) break;
						tree=(JRB)jval_v(node->val);
						jrb_insert_int(tree,v2,new_jval_(1));
					}
				}
			}
		}
		if(x==3)
		{
			printf("nhap quan he cua canh \n");
			scanf("%d",&v1);
			node=jrb_find_int(g,v1);
			if(node==NULL) printf("khong ton tai nut do\n");
			else {

			}
		}
	}while(x!=6);
	return 0;
}