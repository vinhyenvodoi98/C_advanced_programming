#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "dllist.h"

typedef struct {
	JRB edges;
	JRB vertices;
	JRB cha;
	JRB giatri;
}Graph;

int hasEdge(Graph graph, int v1, int v2);
void dijstra(Graph graph,int start,int stop);


Graph createGraph()
{
	Graph g;
	g.edges = make_jrb();
	g.vertices = make_jrb();
	g.cha = make_jrb();
	g.giatri = make_jrb();
	return g;
}

void addVertex(Graph g, int id, char* name)

{
	JRB node = jrb_find_int(g.vertices, id);
	if(node == NULL) // only add new vertex
		jrb_insert_int(g.vertices, id, new_jval_s(strdup(name)));
}
void addgiatri(Graph g ,int id, int gt)
{
	JRB node = jrb_find_int(g.giatri, id);
	if(node == NULL)
		jrb_insert_int(g.giatri, id, new_jval_i(gt));
}

void addcha(Graph g,int id,int cha)
{
	JRB node =jrb_find_int(g.cha,id);
	if(node == NULL)
		jrb_insert_int(g.cha, id, new_jval_i(cha));
}

char *getVertex(Graph g, int id)
{
	JRB node = jrb_find_int(g.vertices, id);
	if(node == NULL)
		return NULL;
	else return jval_s(node -> val);
}
int getgiatri(Graph g, int id)
{
	JRB node=jrb_find_int(g.giatri,id);
	if(node==NULL)
		return -1;
	else return jval_i(node -> val);
}
int getcha(Graph g,int id)
{
	JRB node=jrb_find_int(g.cha,id);
	if(node==NULL)
		return -1;
	else return jval_i(node -> val);
}

int getts(Graph graph,int v1, int v2)
{
	JRB tree, node, node1;
	int ts;
	node = jrb_find_int(graph.edges, v1);
	if(node == NULL)
		return 0;
	tree = (JRB) jval_v(node->val);
	node1 = jrb_find_int(tree,v2);
	ts=jval_i(node1->val);
	return ts;
}

void addEdge(Graph graph, int v1, int v2, int weight) // v1--> v2
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
		jrb_insert_int(tree, v2, new_jval_i(weight));
	}
}

int getAdjacentVertices(Graph graph, int v, int* output)
{
	JRB tree, node;
	int total;
	node = jrb_find_int(graph.edges,v);
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
			printf("%d va %d",jval_i(node->key),jval_i(node1->val));
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
		printf("%d va %d",jval_i(node1->key),jval_i(node1->val));
		total ++;
	}
	return total;
}

void dijstra(Graph graph,int start,int stop) 
{
	int visited[1000];
    int n, output[100], i, v ,u, s, ts;
    Dllist node, queue;

    JRB gnode,gnode1,nodecha,nodecha1,tree;

    gnode=jrb_find_int(graph.giatri,start);
    	gnode->val=new_jval_i(0);
    nodecha=jrb_find_int(graph.cha,start);
    	nodecha->val=new_jval_i(start);

    queue = new_dllist();
    dll_append(queue, new_jval_i(start));

    while ( !dll_empty(queue) )
        {
            node = dll_first(queue);
            u = jval_i(node->val);
            if (!visited[u])
            {
            	visited[u] = 1;
            	gnode=jrb_find_int(graph.giatri,u);
            		s=jval_i(gnode->val);
            	n = getAdjacentVertices(graph, u, output);
            	for (i=0; i<n; i++)
                {
                	v=output[i];
                	gnode  = jrb_find_int(graph.giatri,v);
                   	ts=getts(graph,u,v);
                    if(s+ts<jval_i(gnode->val))
                    	{
                    		gnode->val=new_jval_i(s+ts);
                    		nodecha=jrb_find_int(graph.cha,v);
    						nodecha->val=new_jval_i(u);
                    	}
                    if (!visited[v])
                    	dll_append(queue, new_jval_i(v));
                }
            }
            dll_delete_node(node);
        }
        gnode = jrb_find_int(graph.giatri, stop);
        printf("%d\n",jval_i(gnode->val));
        printf("duong di la: \n");
        int st=stop;
        while(1)
        {	
        	nodecha=jrb_find_int(graph.cha, st);
       		if(jval_i(nodecha->val)==st)
       			break;
       		printf("%d ",jval_i(nodecha->val));
       		st=jval_i(nodecha->val);
        }	
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

int main(){
	int n,m,i=0,t,a1,b1,c1;
	int a[100];
	char b[100],ten[20];
	FILE *f;

	Graph g = createGraph();	
	f=fopen("dij.txt","rt");
	while(1)
	{	
		if(i==0)
			for(i=0;i<=7;i++)
			{
				fscanf(f,"%d %s",&a1,ten);
				addVertex(g,a1,ten);
			}
		if(fscanf(f,"%d %d %d",&a1,&b1,&c1)==EOF) break;
		addEdge(g,a1,b1,c1);
	}
	fclose(f);

	for(i=1;i<=8;i++)
	{
		addgiatri(g,i,100000);
		addcha(g,i,-1);
	}

	printf("nhap 2 diem dau cuoi\n");
	scanf("%d %d",&a1,&b1);
	dijstra(g,a1,b1);

	//strcpy(b, getVertex(g, t));
	//printf("\nb = %s\n", b);
	dropGraph(g);
	return 1;
}