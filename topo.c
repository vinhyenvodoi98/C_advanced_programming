#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "dllist.h"

typedef struct {
	JRB edges;
	JRB vertices;
}Graph;

int hasEdge(Graph graph, int v1, int v2);
void topological(Graph graph);

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
	if(node == NULL) // only add new vertex
		jrb_insert_int(g.vertices, id, new_jval_s(strdup(name)));
}

char *getVertex(Graph g, int id)
{
	JRB node = jrb_find_int(g.vertices, id);
	if(node == NULL)
		return NULL;
	else return jval_s(node -> val);
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
void topological(Graph graph)
{
	int visited[1000]={};
    int n, output[100], i, u, v, start,check,k=1,h=1,topo[100],topo1[100];
    char b[100];
    Dllist node, stack;

    while(1)
    {
    	check=1;
    	for(i=0;i<=7;i++)
        	{
        		if(!visited[i+1])
        			{
        				start=i+1;
        				check=0;
        				break;
        			}
        	}
        if(check==1) break;
    	stack = new_dllist();
   		dll_append(stack, new_jval_i(start));
    	while (!dll_empty(stack))
    	{
    	    node = dll_last(stack);
    	    u = jval_i(node->val);
    	    dll_delete_node(node);
    	    topo[k]=u;
    	    k++;
    	    if (!visited[u])
    	        {
    	            visited[u] = 1;
    	            n = getAdjacentVertices(graph, u, output);
        	        for (i=0; i<n; i++)
        	        	{
        	            	v = output[i];             
        	            	if (!visited[v])
           		         	dll_append(stack, new_jval_i(v));
            	    	}        	
            	}
    	}
   		for(i=k-1;i>=1;i--)
   		{
   			topo1[h]=topo[i];
   			h++;
   		}
   		k=1;
	}
	for(i=8;i>=1;i--)
	{
		strcpy(b, getVertex(graph, topo1[i]));
		printf("%s ", b);
		//printf("%d\n",topo1[i]);
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

int main()
{
	int n,m,i,t,a1,b1;
	int a[100];
	char ten[20],topo[100];
	FILE *f;

	Graph g = createGraph();	
	f=fopen("tolo.txt","rt");
	while(1)
	{	
		if(i==0)
			for(i=0;i<=7;i++)
			{
				fscanf(f,"%d %s",&a1,ten);
				addVertex(g,a1,ten);
			}
		if(fscanf(f,"%d %d",&a1,&b1)==EOF) break;
		addEdge(g,a1,b1);
	}
	fclose(f);
	
	printf("topo: \n");
	topological(g);
	dropGraph(g);
	return 1;
}