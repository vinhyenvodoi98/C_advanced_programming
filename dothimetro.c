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

int timten(Graph g, char ten[])
{
	int i,k=0,x;
	char b[30];
	for(i=0;i<10;i++)
	{
		strcpy(b, getVertex(g, i+1));
		x = strcmp(ten,b);
		if(x == 0)	
			return	(i+1);
	}
	return 	-1;
	
}

void addEdge(Graph graph, int v1, int v2)
{
	JRB node, tree;
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


int main() {
	int i,output[100],x,n,a1,b1;
	char ten[30];
	FILE *f;
	Graph g = createGraph();

	f=fopen("metro.txt","rt");	
		for(i=0;i<10;i++)
		{
			fscanf(f,"%d",&a1);
			fgetc(f);
			fgets(ten,30,f);
			ten[strlen(ten)-1]='\0';
			addVertex(g,a1,ten);
		}
	while(1)
	{
		if(fscanf(f,"%d %d",&a1,&b1)==EOF) break;
		addEdge(g,a1,b1);
		if(fgetc(f)=='\n')
		{
			fseek(f,-1,SEEK_CUR);
		}
		else
			fseek(f,-2,SEEK_CUR);
	}
	fclose(f);
	printf("nhap ten ga tau : ");
	scanf("%[^\n]",ten);
	x=timten(g,ten);
	if(x==-1)	printf("ko ton tai ten nay\n");
	else{
		n = getAdjacentVertices(g,x, output);
		if(n==0)
		printf("ko co ga nao gan. \n");
		else
		{
			printf("cac ga gan :\n");
			for(i=0; i<n; i++)
				{
					strcpy(ten, getVertex(g, output[i]));
					printf("%s\n", ten);
				}
			printf("\n");
		}
	}
	
	
	dropGraph(g);
	return 0;
}
