#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct PhoneEntry
{
    int number;
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
 

void addPhoneNumber1(int number,char name[],PhoneBook book)
{
    book.entries[0].number=number;
    strcpy(book.entries[0].name,name);

}

PhoneBook createPhoneBook()
{
    PhoneBook p;
    p.total= 0;
    p.size= 0;
    p.entries= (PhoneEntry*) malloc (THEM * sizeof(PhoneEntry));
    return p;
}
void in(PhoneBook book)
{
    printf("%d\n",book.entries[0].number );
    printf("%s\n",book.entries[0].name );
}
int main()
{
    int number;
    char name[40];
    int n,x;
    PhoneBook p;
   
    do{
        printf("1, tao so dien thoai \n");
        printf("2, xoa so dien thoai \n");
        scanf("%d",&x);
        if(x==1)
        {
            p=createPhoneBook();
            printf("nhap so dien thoai thu  : ");
            scanf("%d",&number);
            printf("nhap ten chu nhan so : ");
            scanf("%*c"); scanf ("%[^\n]",name);
          
                //addPhoneNumber(number,name,p);
            addPhoneNumber1(number,name,p);
            
        }
        if(x==2)
        {
            in(p);
        }
    }while(x!=6);
}