#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jval.h"
#include "jrb.h"
#include "dllist.h"


int main()
{
	int i,n,x;
	char word[20],nghia[200],cachdoc[20];
	JRB book,node;
	Dllist mean,node1;
	book =make_jrb();
	while(1){
		printf("1. nhap \n");
		printf("2. tim sdt\n");
		printf("3. in \n");
		scanf("%d",&x);
		if(x==1)
		{
			FILE *f;
			f=fopen("diemtoan.txt","rt");
			while(1){
				fgets(word,20,f);
				word[strlen(word)-1]='\0';
				if(word[0]==NULL) break;
				printf("%s\n",word );
				fgets(cachdoc,20,f);
				cachdoc[strlen(cachdoc)-1]='\0';
				printf("%s\n",cachdoc );
				fgets(nghia,200,f);
				nghia[strlen(nghia)-1]='\0';
				printf("%s\n",nghia );
				mean=new_dllist();
				jrb_insert_str(book,strdup(word),new_jval_v(mean));
				mean->val=new_jval_s(cachdoc);
				dll_insert_b(mean,new_jval_s(cachdoc));
				mean=mean->flink;
				dll_insert_b(mean,new_jval_s(nghia));
				}
			
			fclose(f);
			printf("da cap nhat diem\n");
		}
		if(x==3)
		{
			printf("nhap tu tim kiem\n");
			scanf("%*c");scanf("%[^\n]",word);
			node=jrb_find_str(book,word);
			mean = (Dllist) jval_v(node->val);
			printf("%s\n",jval_s(dll_val(mean)));
			mean=mean->flink;
			printf("%s\n",jval_s(dll_val(mean)));
		}

	}
	
}