#include <stdio.h>
#include <stdlib.h>
#include "jval.h"
#include "jrb.h"
#include "dllist.h"

int main()
{
	int i,n,x;
	float diemtoan,diemly,diemhoa;
	char name[80];
	
	JRB book,node;
	Dllist diem;
	book =make_jrb();
	/*f=fopen("diemly.txt","rt");
	{
		if(fscanf(f,"%s %f",name,&diemly)==EOF) break;
		jrb_insert_b(book,strdup(name),new_jval_f(diemly));
	}
	f=fopen("diemhoa.txt","rt");
	{
		if(fscanf(f,"%s %f",name,&diemhoa)==EOF) break;
		jrb_insert_b(book,strdup(name),new_jval_f(diemhoa));
	}*/
	while(1){
		printf("1. nhap \n");
		printf("2. in \n");
		scanf("%d",&x);
		if(x==1)
		{
			FILE *f;
			f=fopen("diemtoan.txt","rt");
			while(1)
			{	
				if(fscanf(f,"%s\t%f",name,&diemtoan)==EOF) break;
				diem=new_dllist();
				jrb_insert_str(book,strdup(name),new_jval_v(diem));
				dll_insert_a(diem, new_jval_f(diemtoan)) 
			}
			fclose(f);
			f=fopen("diemly.txt","rt");
			{
				if(fscanf(f,"%s %f",name,&diemly)==EOF) break;
				node = jrb_find_int(book, strdup(name));
				jrb_insert_b(name,new_jval_f(diemly));
			}
			fclose(f);
			f=fopen("diemhoa.txt","rt");
			{
			if(fscanf(f,"%s %f",name,&diemhoa)==EOF) break;
			jrb_insert_b(book,strdup(name),new_jval_f(diemhoa));
			}
			fclose(f);

			printf("da cap nhat diem\n");
		}
		if(x==2)
		{
			jrb_traverse(node,book)
			printf("%s\t%f\n",node->key,jval_f(node->val));
		}

	}
	
}