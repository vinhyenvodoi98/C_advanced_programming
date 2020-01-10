#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
int chuyen(char id[]);


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
	JRB node;
	jrb_traverse(node,g.vertices)
	{
		if (!strcmp(ten, jval_s(node->val)))
		break;
	}
	return jval_i(node->key);
}

int hasEdge(Graph graph, int v1, int v2)
{
	JRB tree, node;
	node = jrb_find_int(graph.edges, v1);
	if(node == NULL) return 0;
	tree = (JRB) jval_v(node -> val);
	if(jrb_find_int(tree, v2)== NULL)
		return 0;
	else return 1;
}

void addEdge(Graph graph, int v1, int v2) // v1--> v2
{
	JRB node, tree;
	if(!hasEdge(graph, v1, v2))
	{
		node = jrb_find_int(graph.edges, v1);
		if(node == NULL) {
			tree = make_jrb();
			jrb_insert_int(graph.edges, v1, new_jval_v(tree));
		} else
		{
			tree = (JRB) jval_v(node->val);
		}
		jrb_insert_int(tree, v2, new_jval_i(1));
	}
}



int indgree(Graph graph, int v, int* output)
{
	JRB tree, node, node1;
	int total =0;
	jrb_traverse(node, graph.edges)
	{
		tree = (JRB) jval_v(node -> val);
		if(node1=jrb_find_int(tree,v))
		{
			output[total] = jval_i(node -> key);
			//printf("%d va %d",jval_i(node->key),jval_i(node1->val));
			total ++;
		}
	}
	return total;
}

int outdegree(Graph graph, int v, int* output)
{
	JRB tree, node,node1;
	int total;
	node = jrb_find_int(graph.edges, v);
	if(node == NULL)
		return 0;
	tree = (JRB) jval_v(node -> val);
	total =0;
	jrb_traverse(node1, tree)
	{
		output[total] = jval_i(node1-> key);
		//printf("%d va %d",jval_i(node1->key),jval_i(node1->val));
		total ++;
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

int chuyen(char id[]) // ham atoi
{
	int i,n,p=1;
	int a=0;
	n=strlen(id);
	for(i=0;i<strlen(id);i++)
	{
		for(int j=1;j<n;j++)
			p=p*10;
		a=a+((int) id[i]-48) *p ;
		p=1;
		n--;
	}
	return a;
}
void docfile(Graph g,char filename[])
{
	FILE *f;
	int a,b,i,id1,id2;
	char name[20];
	f=fopen(filename,"rt");
	fscanf(f,"%d %d",&a,&b);
	fgetc(f);
	for(i=0;i<a;i++)
	{
		fscanf(f,"%s %d",name,&id1);
		addVertex(g,id1,name);
	}
	for(i=0;i<b;i++)
	{
		fscanf(f,"%d %d",&id1,&id2);
		addEdge(g,id1,id2);
	}
	fclose(f);
	//printf("%d\n",(int) id[0]); //ep kieu thi ve ma acscii
	
}
void incc(Graph g,int id1,int id2)
{
	int n,v,output[100],output1[100];
	n = outdegree(g, id1, output);
	v = outdegree(g, id2, output1);
        for(int i=0;i<n;i++)
        {
        	for(int j=0;j<v;j++)
        	{
        		if(output[i]==output1[j])
        			printf("%s\n",getVertex(g,output[i]));
        	}
        }

}

void cr(Graph g,int id1 ,int id2)
{
	int n,v,output[100],output1[100];
	n = indgree(g, id1, output);
	v = indgree(g, id2, output1);
        for(int i=0;i<n;i++)
        {
        	for(int j=0;j<v;j++)
        	{
        		if(output[i]==output1[j])
        			printf("%s\n",getVertex(g,output[i]));
        	}
        }
}

void odg(Graph g, int id)
{
	JRB node;
	int output[100];
	jrb_traverse(node,g.edges)
	{
		if(id<outdegree(g,jval_i(node->key),output))
			printf("%s\n",getVertex(g,jval_i(node->key)) );
	}
}

void rel(Graph g,int id)
{
	int n,v,output[100],output1[100];
	n = outdegree(g,id, output);
        for(int i=0;i<n;i++)
        {
        	v = outdegree(g, output[i], output1);
        	printf("%s\n",getVertex(g,output[i]) );
        	for(int j=0;j<v;j++)
        	{
        			printf("%s\n",getVertex(g,output1[i]));
        	}
        }
}

int main(int argc, char *argv[])
{
	Graph g = createGraph();
	
	if(argc==2 && strcmp(argv[1],"help")==0)
		printf("Supported command: help, i2n, n2i, cc, cr, odg, rel.\n");
	if(argc==2 && strcmp(argv[1],"about")==0)
		printf("C advanced 20142 final exam.\n");
	if(argc==4 && strcmp(argv[1],"i2n")==0)
		{
			docfile(g,argv[2]);
			printf("%s\n",getVertex(g,chuyen(argv[3])));
		}
	if(argc==4 && strcmp(argv[1],"n2i")==0)
		{
			docfile(g,argv[2]);
			printf("%d\n",timten(g,argv[3]) );
		}
	if(strcmp(argv[1],"cc")==0)
	{
		docfile(g,argv[2]);
		incc(g,atoi(argv[3]),atoi(argv[4]));
	}
	if(strcmp(argv[1],"cr")==0)
	{
		docfile(g,argv[2]);
		cr(g,atoi(argv[3]),atoi(argv[4]));
	}
	if(strcmp(argv[1],"odg")==0)
	{
		docfile(g,argv[2]);
		odg(g,atoi(argv[3]));
	}
	if(strcmp(argv[1],"rel")==0)
	{
		docfile(g,argv[2]);
		rel(g,atoi(argv[3]));
	}
	dropGraph(g);
	return 0;
}