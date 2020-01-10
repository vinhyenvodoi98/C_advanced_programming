#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node
{
	char name[20];
	struct node *next;
}node;
node *first;
int main()
{
	int x;
	do
	{
		printf("1, \n");
		printf("2, \n");
		printf("3, \n");
		printf("4, \n");
		scanf("%d",&x);
		if(x==1)
		{

		}
		if(x==2)
		{
			
		}		
		if(x==3)
		{
			
		}
	}while(x!=4);
}
/////////////////////////////////////////////////////////////////////////////////////////////////// ham kiem tra va tach chuoi
int main()
{
   const char haystack[20] = "Viet JackTeam";
   const char *needle = " ";
   char *ret;

   ret = strstr(haystack, needle);
   if(ret==NULL)	printf("khong co\n");
   else printf("Chuoi con la: %s\n", ret);
   
   return(0);
}
//////////////////////struct cay
typedef struct tree
{
	int ngay;
	struct tree *trai;
	struct tree *phai;
}tree; 
tree *root=NULL;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// doc file
//1 co so thu tu
	int num,num1;
	FILE *f;
	f=fopen(".txt","rt");
	fscanf(f,"%d ",&num);
	for(i=0 ;i< num; i++)
	{
		fscanf(f,"%d ", &num1);
		//s1=nhapvao1(s1,num1);
		for(j=0 ;j< num1; j++)
		{
			fscanf(f, "%f ",&b);
			//nhapvao(s1,b);
		}
		k=0;		
	}
	fclose(f);
///////////////////////////////////////////////////////////////////////////////////////// khong co so thu tu
	FILE *f;
	f=fopen(".txt","rt");
	while(1)
	{
		if(fscanf(f,"%s %d %d %d %d",ten,&a,&b,&c,&d)==EOF) break;
		//s1=them1(s1,ten,a,b,c,d); vs danh sach moc noi
		//root=them(root,ten,a,b); vs cay
	}
	fclose(f);
////////////////////////////////////////////////////////////////////////////////////////// in file cua cay
void infile(FILE*f ,tree* root)
    {
    	if (root != NULL)
    	{
    		infile(f,root->trai);
    		fprintf(f, "%s\t%s\t%f\n",root->usename,root->password,root->diem);
    		infile(f,root->phai);
    	}	 	
    }
void inrafile(tree *root)
{
	FILE *f;
	f=fopen("ten.txt","wt");
	infile(f,root);
	fclose(f);
}
///////////////////////////////////////////////////////////////////////////////////////in file cua danh sach moc noi
	FILE *f;
	f=fopen(".txt","wt");
	temp=first;
	while(temp)
	{
		fprintf(f, "%d %d %d %s\n",temp->masp,temp->gia,temp->soluong,temp->ten);
		temp=temp->next;
	}
	fclose(f);

///////neu ham co nhieu lien quan den string


	fgets(name,30,f);
	name[strlen(name)-1]='\0';



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// ham nhap vao ko sap xep
node *them1(node *pre,)
{
	node *temp;
	temp=(node *)malloc(sizeof(node));
	strcpy(temp->name,name);
	temp->mau=mau;
	if(first==NULL)
	{
		first=temp;
		pre=first;
	}
	else
	{
		pre->next=temp;
      	pre=pre->next;
      	pre=NULL;
	}
}
/// ham nhap co sap xep
node *vao(node *pre,)
{
	node *temp,*temp1,*temp2;
    temp=(node *)malloc(sizeof(node));
    strcpy(temp->name,name);
    temp->diem=diem;
    if(first==NULL)
    {
        first=temp;
    	pre=first;
    	temp->next=NULL;
    }
  else
    {
    	temp1=first;
    	while(temp1)
    	{
    		if(temp->diem < temp1->diem)
    			{
    			if(temp1==first)
    				{
    					temp->next=first;
    					first=temp;
    					break;
    				}
    			else
    				{
    				temp->next=temp2->next;
         		    temp2->next=temp;
         		    break;
    				}
    			}
    		temp2=temp1;
    		if(temp1->next==NULL)
    		{
    			temp1->next=temp;
    			temp->next=NULL;
    			break;	
    		}
    		temp1=temp1->next;
    	}	
  	}

/// ham in
void phanloai()
{
    node *temp;
    temp=first;
    while(temp)
    {
    	printf("%10s %d\n",temp->name,temp->diem);
        temp=temp->next;
    }
  printf("\n");
}
////////////////////////////////////////////////////////////////////////////////////////////////////////   binary tree


tree *them(tree *root, int x)	//////////////////////////////////////////////////////////dung de quy them vao cay      
    {
        if (root == NULL)
        {
        	root = (tree *)malloc(sizeof(tree));
            root -> ngay= x;
       		root -> trai = NULL;
       		root -> phai = NULL;
       		return root;
        }
        else if (root->ngay > x)	root->trai=them(root->trai,x);   
        else if (root->ngay < x)	root->phai=them(root->phai,x);
        else if (root->ngay ==x)	
        	{
        		return root;
        	}
    }


int check(tree *root,int x) // su dung de quy de tim ngay x neu co tra ve 0 khong co tra ve 1
{
	if (root == NULL) return 1;
    else if (root-> ngay > x)	return check(root->trai,x);   
    else if (root-> ngay < x)	return check(root->phai,x);
    else if (root-> ngay ==x)	return 0;
}



//////////////////////////////////////////////////////////////////////////////            xoa cay
tree *xoa_cay(tree *root, int x)    
{
	
    if (root==NULL) return root;
    if (root->ngay > x) root->trai=xoa_cay(root->trai, x);
    if (root->ngay < x) root->phai=xoa_cay(root->phai, x);
    if (root->ngay == x)
    {
    	tree *temp = root;
        if (root->trai == NULL) { root=root->phai; return root; }
        else if (root->phai == NULL) { root=root->trai; return root; }
        else
        {
            tree *temp1 = root;
            tree *temp2 = temp1->trai;
            while (temp2->phai != NULL)
            {
                temp1 = temp2;
                temp2 = temp2->phai;
            }
            temp->ngay = temp2->ngay;
            temp->dau = temp2->dau;
            free(temp2);
            temp2=NULL;
        }
    }
    return root;
}
///////////////////////////////////////////////////////////////////////////////			in cay
void NLR(tree* root)
    {
    	if (root != NULL)
    	{
    		NLR(root->trai);
    		printf("ngay %d: \n", root->ngay);
    		NLR(root->phai);
    	}	
    }


