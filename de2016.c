#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "dllist.h"

typedef struct {
	JRB edges;
	JRB vertices;
}Graph;

Graph createGraph();
void addEdge(Graph graph, int v1, int v2);
int getAdjacentVertices(Graph graph, int v, int* output);
int adjacent(Graph graph, int v1, int v2);


Graph createGraph()
{
	Graph g;
	g.edges = make_jrb();
	g.vertices = make_jrb();
	return g;
}

void addVertex(Graph g, int id, char* name)
{

	JRB node = jrb_find_int(g.vertices, id);
	if(node == NULL)
		jrb_insert_int(g.vertices, id, new_jval_s(strdup(name)));
}

char *getVertex(Graph g, int id)
{
	JRB node = jrb_find_int(g.vertices, id);
	if(node == NULL)
		return NULL;
	else return jval_s(node -> val);
}

int getts(Graph graph,int v1, int v2)
{
	JRB tree, node, node1;
	int ts;
	node = jrb_find_int(graph.edges, v1);
	tree = (JRB) jval_v(node->val);
	node1 = jrb_find_int(tree,v2);
	if(node1==NULL)
		return -1;
	ts=jval_i(node1->val);
	return ts;
}

void addEdge(Graph graph, int v1, int v2)
{
	int a;
	JRB node, tree, node1;
	if(!adjacent(graph, v1, v2))
	{
		node = jrb_find_int(graph.edges, v1);
		if(node == NULL) {
			tree = make_jrb();
			jrb_insert_int(graph.edges, v1, new_jval_v(tree));
		}
		else {
			tree = (JRB) jval_v(node->val);
		}
		jrb_insert_int(tree, v2, new_jval_i(1));
	}
	else
	{
		node = jrb_find_int(graph.edges, v1);
		tree = (JRB) jval_v(node->val);
		node1 = jrb_find_int(tree,v2);
		a=jval_i(node1->val)+1;
		node1->val=new_jval_i(a);
	}
	if(!adjacent(graph, v2, v1))
	{
		node = jrb_find_int(graph.edges, v2);
		if(node == NULL) {
			tree = make_jrb();
			jrb_insert_int(graph.edges, v2, new_jval_v(tree));
		}
		else {
			tree = (JRB) jval_v(node->val);
		}
		jrb_insert_int(tree, v1, new_jval_i(1));
	}
	else
	{
		node = jrb_find_int(graph.edges, v2);
		tree = (JRB) jval_v(node->val);
		node1 = jrb_find_int(tree,v1);
		a=jval_i(node1->val)+1;
		node1->val=new_jval_i(a);
	}
}

int getAdjacentVertices(Graph graph, int v, int* output)
{
	JRB tree, node;
	int total;
	node = jrb_find_int(graph.edges, v);
	if(node == NULL)
		return 0;
	tree = (JRB) jval_v(node->val);
	total = 0;
	jrb_traverse( node, tree)
	{
		output[total] = jval_i(node->key);
		total++;
	}
	return total;
}

int adjacent(Graph graph, int v1, int v2)
{
	JRB node, tree;
	node = jrb_find_int(graph.edges, v1);
	if(node == NULL)
		return 0;
	tree = (JRB) jval_v(node -> val);
	if(jrb_find_int(tree, v2)==NULL)
		return 0;
	else return 1;
}

void dropGraph(Graph graph){
	JRB node, tree;
	jrb_traverse(node, graph.edges)
	{
		tree = (JRB) jval_v(node -> val);
		jrb_free_tree(tree);
	}
	jrb_free_tree(graph.edges);
	jrb_free_tree(graph.vertices);
}

void dijstra(Graph graph,int start,int stop,int sl) 
{
	int visited[1000];
    int n, output[100], cha[100], giatri[100] , i, v, u, s, ts;
    Dllist node, queue;

    for(i=1;i<=sl;i++)
    {
    	giatri[i]=10000;
    }
    giatri[start]=0;
    queue = new_dllist();
    dll_append(queue, new_jval_i(start));

    while ( !dll_empty(queue) )
        {
            node = dll_first(queue);
            u = jval_i(node->val);
            if (!visited[u])
            {
            	visited[u] = 1;
            	s=giatri[u];
            	n = getAdjacentVertices(graph, u, output);
            	for (i=0; i<n; i++)
                {
                	v=output[i];
                   	ts=getts(graph,u,v);
                    if(s+ts<giatri[v])
                    	{
                    		giatri[v]=s+ts;
                    		cha[v]=u;
                    	}
                    if (!visited[v])
                    	dll_append(queue, new_jval_i(v));
                }
            }
            dll_delete_node(node);
        }
        printf("%d\n",stop);
        printf("%s\t",getVertex(graph,stop) );
        i=cha[stop];
    while(1)
        {
        	if(giatri[stop]==10000)
        	{
        		printf("2 san pham khong co su lien quan\n");
        		break;
        	}
        	else
        	{
        		printf("%s\t",getVertex(graph,i));
        		if(i==start) 
        			{
        				printf("\n");
        				break;
        			}
        		i=cha[i];
        	}        	
        }
        for(i=1;i<=sl;i++)
        {
        	visited[i]=0;
        }

}

int product(Graph g)
{
	int a,sl=1;
	char ten[30];
	FILE *f;
	f=fopen("product.txt","rt");
	while(1)
	{
		if(fscanf(f,"%d %s",&a,ten)==EOF) break;
		sl++;
		addVertex(g,a,ten);
		printf("Ma san pham  :%d\n",a);
		printf("Ten san pham :%s\n",ten);
	}
	printf("\n");
	fclose(f);
	return sl-1;
}

void orderhistory(Graph g)
{	
	int a1,b1;
	int i,j,t=0,p=0,q=0,k=0,a[100],b[100];
	FILE *f;
	f=fopen("orderhistory.txt","rt");
	while(1)
	{
		if(fscanf(f,"%d",&a1)==EOF) break;
		a[t]=a1;t++;
		if(fgetc(f)=='\n')
		{
			for(i=k;i<t;i++)
				for(j=i+1;j<t;j++)
				{
					b[p]=a[i];p++;
					b[p]=a[j];p++;
				}
			k=t;
			for(i=q;i<p;i=i+2)
			{
				addEdge(g,b[i],b[i+1]);
			}
			q=p;
			fseek(f,-1,SEEK_CUR);
		}
	}
	fclose(f);
	
}
void inorder(Graph g)
{
	FILE *f;
	int a1;
	char ten[30];
	f=fopen("orderhistory.txt","rt");
	while(1)
	{
		if(fscanf(f,"%d",&a1)==EOF) break;
		printf("%s\t", getVertex(g,a1));
		if(fgetc(f)=='\n')
		{
			printf("\n");
			fseek(f,-1,SEEK_CUR);
		}
		
	}
	printf("\n");
	fclose(f);	
}

int main()
{
	Graph g = createGraph();
	int x,a,b,sl,n,output[100];
	char ten[30];
	do{
		printf("1.in danh sach san pham\n");
		printf("2.in lich su mua ban\n");
		printf("3.do lien quan giua 2 san pham\n");
		printf("4.in ra cac san pham lien quan\n");
		printf("5.nhap ma so in ra do lien quan\n");
		printf("6.thoat\n");
		scanf("%d",&x);
		if(x==1)
		{
			sl=product(g);
		}
		if(x==2)
		{
			orderhistory(g);
			inorder(g);
		}
		if(x==3)
		{
			printf("nhap ma 2 sp: \n");
			scanf("%d %d",&a,&b);
			printf("do lien quan giua 2 san pham: %d\n",getts(g,a,b));
		}
		if(x==4)
		{
			printf("nhap vao ma so: \n");
			scanf("%d",&a);
			n = getAdjacentVertices(g,a, output);
			printf("%d\n",n );
			if(n==0)
			printf("ko co san pham nao lien quan \n");
			else
			{
				for(int i=0;i<n;i++)
					for(int j=0;j<n;j++)
					{
						if(getts(g,a,output[i])>getts(g,a,output[j]))
							{
								b=output[i];
								output[i]=output[j];
								output[j]=b;
							}
					}
				printf("cac san pham lien quan :\n");
				for(int i=0; i<n; i++)
				{
					strcpy(ten, getVertex(g, output[i]));
					printf("%s\t", ten);
				}
			printf("\n");
			}
		}
		if(x==5)
		{
			printf("nhap vao ma so 2 san pham: \n");
			scanf("%d %d",&a,&b);
			dijstra(g,a,b,sl);
		}
		else
		{

		}
	}while(x!=6);
}