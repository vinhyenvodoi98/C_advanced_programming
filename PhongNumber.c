#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct PhoneEntry
{
	long number;
	char name[80];
}PhoneEntry;
typedef struct PhoneBook
{
	struct PhoneEntry * entries;
	int total;
	int size;
}PhoneBook;

#define THEM 10
#define THEM_NUA 5
 

void addPhoneNumber(int number,char name[],PhoneBook book)
{
	int a;
	book.total++;
	if(book.total > book.size )
	{
		book.size=book.size+THEM_NUA;
		p.entries=(PhoneEntry*) malloc (book.size * sizeof(PhoneEntry));
	}
	a=FindingPhoneLocal(0,book.total-1,number,PhoneBook);
	for(int i=book.total-1;i>a;i--)
	{
		book.entries[i+1]=book.entries[i];
	}
}
int FindingPhoneLocal(int l,int r,int number,PhoneBook book)
{
	if(number>book.)
}
void dropPhoneBook(PhoneBook *book)
{
	book.total=0;
	book.size=THEM;
	free(p.entries);
}
PhoneBook createPhoneBook()
{
	PhoneBook p;
	p.total= 0;
	p.size= 0;
	p.entries= (PhoneEntry*) malloc (THEM * sizeof(PhoneEntry));
	return p;
}

int main()
{
	int number;
	char name[40];
	int n,x;
	PhoneBook p;
	printf("1, tao so dien thoai \n");
	printf("2, xoa so dien thoai \n");
	do{
		scanf("%d",&x);
		if(x==1)
		{
			p=createPhoneBook();
			printf("nhap so luong dien thoai:");
			scanf("%d",&n);
			for(int i=0;i<n;i++)
			{
				printf("nhap so dien thoai thu %d : ",i+1);
				scanf("%d",&number);
				printf("nhap ten chu nhan so %d : ",number);
				scanf("%*c"); scanf ("%[^\n]",name);
				addPhoneNumber(number,name,p);
			}
		}
		if(x==2)
		{
			dropPhoneBook(p);
		}
	}while(x!=6);
}