#include <stdio.h>
#include "jval.h"
#include "jrb.h"

JRB tao();
void taocanh(JRB g,int v1,int v2);
void taolienket(JRB g);
void huy(JRB g);

JRB tao()
{
	make_jrb();
}

int main()
{
	int x,v1,v2,n;
	JRB g;
	g = tao();
	do{
		printf("1,nhap vao cac canh cua do thi \n");
		printf("2,nhap quan he giua cac dinh \n");
		printf("3,tim kiem\n");
		printf("4,\n");
		printf("5,xoa\n");
		if(x==1)
		{
			printf("nhap vao so luong nut: \n");
			scanf("%d",&n);
			for(int i=0;i<n;i++)
			{
				scanf("%d",&v1);
				insert(g, (JRB)v1);
			}
		}
	/*	if(x==2)
		{	

		}*/
	}while(x!=6)
	return 0;
}