#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#define INITIAL_SIZE 100
#define INCREMENTAL_SIZE 10

typedef struct {
  void *key;
  void *value;
} Entry;

Entry makeNode(void *phone, void* name);
int compare(void *key1,void* key2);

typedef struct {
  Entry *entries;
  int size, total;
  Entry (*makeNode)(void*, void*);
  int (*compare)(void*, void*);
} SymbolTable;

SymbolTable createSymbolTable(Entry (*makeNode)(void*, void*), int (*compare)(void*, void*));
void dropSymbolTable (SymbolTable *tab);
int addEntry (void* key, void* value, SymbolTable* book);
void* getEntryValue (void* key, const SymbolTable* book);
void transfer(SymbolTable *book);

int main()
{
  SymbolTable book=createSymbolTable(makeNode,compare);
  transfer(&book);
  int c;
  do {
    printf("\n___________\n");
    printf("   MENU\n1. Them so dien thoai\n2. Tra cuu so dien thoai\n3. Thoat\n");
    printf("Nhap lua chon:");
    scanf("%d",&c);

    if (c==1) {
      int sdt;
      char ten[30];
      printf("Nhap so dien thoai:");
      scanf("%d",&sdt);
      __fpurge(stdin);
      printf("Nhap ten chu so dien thoai:");
      gets(ten);
      addEntry(&sdt,ten,&book);
      for (int i=0;i<book.total;i++)
	printf("%-20s 0%d\n",(char*)book.entries[i].value,*(int *)book.entries[i].key);
    }
    
    else if (c==2) {
      char searchNum[15];
      __fpurge(stdin);
      printf("Nhap so dien thoai can tim:");
      gets(searchNum);
      int num=atoi(searchNum);
      char *find=(char *)getEntryValue(&num,&book);
      if (find != NULL) 
	printf("Chu nhan so dien thoai 0%d la %s.\n",num,find);
      else printf("Khong tim thay chu nhan so dien thoai %s.\n",searchNum);
    }
    
    else if (c==3) {
      FILE *f;
      f=fopen("PhoneEntries.txt","w");
      for (int i=0;i<book.total;i++)
	fprintf(f,"%s\t0%d\n",(char*)book.entries[i].value,*(int*)book.entries[i].key);
      dropSymbolTable(&book);
      break;
    }
    
    else printf("Khong co lua chon nay. Vui long nhap lai.\n");
  } while (1);
}

Entry makeNode(void *phone, void* name)
{
  Entry res;
  res.key=malloc(sizeof(int));
  memcpy(res.key,phone,sizeof(int));
  res.value=strdup((char *)name);
  return res;
}

int compare(void *key1, void* key2)
{
  int num1 = *(int *)key1;
  int num2 = *(int *)key2;
  if (num1==num2) return 0;
  else if (num1 < num2) return 1;
  else return -1;
}

SymbolTable createSymbolTable(Entry (*makeNode)(void*, void*), int (*compare)(void*, void*))
{
  SymbolTable a;
  a.entries=(Entry *)malloc(INITIAL_SIZE*sizeof(Entry));
  a.total=0;
  a.size=INITIAL_SIZE;
  a.makeNode=makeNode;
  a.compare=compare;
  return a;
}

int addEntry (void* key, void* value, SymbolTable* book)
{
  if ((*book).total==(*book).size) {
    (*book).entries=(Entry *)realloc((*book).entries, INCREMENTAL_SIZE);
    (*book).size=(*book).size+INCREMENTAL_SIZE;
  }
  
  Entry new=makeNode(key,value);
  (*book).entries[(*book).total]=new;
  (*book).total++;
}

void transfer(SymbolTable *book)
{
  FILE *f;
  char filename[]="PhoneEntries.txt";
  if ((f=fopen(filename,"r")) == NULL) {
    printf("Khong mo duoc file %s.\n",filename);
    return ;
  }
  else {
    int sdt;
    char ten[20];
    while((fscanf(f,"%[^\t]\t%d\n",ten,&sdt)) == 2) {
      addEntry(&sdt,ten,book);
    }
    fclose(f);
  }
}

void* getEntryValue (void* keySearch, const SymbolTable* book)
{
  int i;
  for (i=0;i<(*book).total;i++) {
    if (compare((*book).entries[i].key,keySearch)==0) {
      return (*book).entries[i].value;
    }
  }
  return NULL;
}

void dropSymbolTable (SymbolTable *tab)
{
  int i;
  for (i=0;i<(*tab).total;i++) { 
    free((*tab).entries[i].key);
    free((*tab).entries[i].value);
  }
  free((*tab).entries);
}

