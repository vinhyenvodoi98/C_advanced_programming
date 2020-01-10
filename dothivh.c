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

void dijstra(Graph graph,int start,int stop) 
{
	int visited[1000];
    int n, output[100], cha[100], giatri[100] , i, v, u, s, ts;
    Dllist node, queue;

    JRB node1;
    jrb_traverse(node1,graph.vertices)
    {
    	i=jval_i(node1->key);
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
        printf("%d\n",giatri[stop]);
        printf("%s\n",getVertex(graph,stop) );
        printf("%s\n",getVertex(graph,cha[stop]));
        while(1)
        {
        	if(giatri[stop]==10000)
        	{
        		printf("2 khong ton tan duong chuyen\n");
        		break;
        	}
        	else
        	{
        		printf("%s\n",getVertex(graph,i));
        		if(i==start) 
        			{
        				printf("\n");
        				break;
        			}
        		i=cha[i];
        	}        	
        }
        jrb_traverse(node1,graph.vertices)
    	{
    		i=jval_i(node1->key);
    		visited[i]=0;
    	}
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
	Graph g = createGraph();	
	dropGraph(g);
	return 0;
}
