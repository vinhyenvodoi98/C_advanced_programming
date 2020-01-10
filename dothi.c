#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "dllist.h"

typedef JRB Graph;
Graph createGraph();
void addEdge(Graph graph, int v1, int v2, int ts);
int getAdjacentVertices(Graph graph, int v, int* output);
int adjacent(Graph graph, int v1, int v2);

void printfdinh(int v) {printf("%d",v );}

Graph createGraph()
{
	make_jrb();
}

void addEdge(Graph graph, int v1, int v2, int ts)
{
	JRB node, tree;
	if(!adjacent(graph, v1, v2))
	{
		node = jrb_find_int(graph, v1);
		if(node == NULL) {
			tree = make_jrb();
			jrb_insert_int(graph, v1, new_jval_v(tree));
		}
		else {
			tree = (JRB) jval_v(node->val);
		}
		jrb_insert_int(tree, v2, new_jval_i(ts));
	}
	if(!adjacent(graph, v2, v1))
	{
		node = jrb_find_int(graph, v2);
		if(node == NULL) {
			tree = make_jrb();
			jrb_insert_int(graph, v2, new_jval_v(tree));
		}
		else {
			tree = (JRB) jval_v(node->val);
		}
		jrb_insert_int(tree, v1, new_jval_i(ts));
	}
}

int getAdjacentVertices(Graph graph, int v, int* output)
{
	JRB tree, node;
	int total;
	node = jrb_find_int(graph, v);
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
	node = jrb_find_int(graph, v1);
	if(node == NULL)
		return 0;
	tree = (JRB) jval_v(node -> val);
	if(jrb_find_int(tree, v2)==NULL)
		return 0;
	else return 1;
}

void dropGraph(Graph graph)
{
	JRB tree, node;
	jrb_traverse(node,graph)
	{
		tree = (JRB) jval_v(node->val);
		jrb_free_tree(tree);
	}
	jrb_free_tree(graph);
}

void BFS(Graph graph,int start,int stop)
{
	int visited[1000] = {};
    int n, output[100], i, u, v;
    Dllist node, queue;

    queue = new_dllist();
    dll_append(queue, new_jval_i(start));

    while ( !dll_empty(queue) )
        {
            node = dll_first(queue);
            u = jval_i(node->val);
            dll_delete_node(node);
            if (!visited[u])
            {
            visited[u] = 1;
            if ( u == stop ) return;
            n = getAdjacentVertices(graph, u, output);
            for (i=0; i<n; i++)
                {
                    v = output[i];
                    printfdinh(v);
                    if (!visited[v])
                    	dll_append(queue, new_jval_i(v));
                }
            }
        }
}
void DFS(Graph graph, int start, int stop)
{
    int visited[1000] = {};
    int n, output[100], i, u, v;
    Dllist node, stack;

    stack = new_dllist();
    dll_append(stack, new_jval_i(start));

    while ( !dll_empty(stack) )
    {
        node = dll_last(stack);
        u = jval_i(node->val);
        dll_delete_node(node);
        if (!visited[u])
            {
                visited[u] = 1;
                if ( u == stop ) return;
                n = getAdjacentVertices(graph, u, output);
                for (i=0; i<n; i++)
                {
                    v = output[i];             
                    printfdinh(v);
                    if (!visited[v])
                    dll_append(stack, new_jval_i(v));
                }
            }
    }
}

int getts(Graph graph,int v1, int v2)
{
	JRB tree, node, node1;
	int ts;
	node = jrb_find_int(graph, v1);
	if(node == NULL)
		return 0;
	tree = (JRB) jval_v(node->val);
	node1 = jrb_find_int(tree,v2);
	ts=jval_i(node1->val);
	return ts;
}

int main() {
	int i,n, output[100],x,a,b,ts;
	Graph g = createGraph();
	addEdge(g,0,1,2);
	addEdge(g,0,2,1);
	addEdge(g,1,2,7);
	addEdge(g,1,3,5);
	printf("nhap vao dinh muon tim\n");
	scanf("%d",&x); 
	n = getAdjacentVertices(g,x, output);
	if(n==0)
		printf("No adjacent vertices of node 1 \n");
	else
	{
		printf("Adjacent vertices of node 1:");
		for(i=0; i<n; i++)
			printf("%5d", output[i]);
		printf("\n");
	}
	/*while(a!=-1)
	{
		printf("nhap cac canh quan he:  ");
		scanf("%d" ,&a);
		if(a==-1) break;
		scanf("%d" ,&b);
		printf("nhap trong so: ");
		scanf("%d",&ts);
		addEdge(g,a,b,ts);
	}
	printf("nhap vao dinh muon tim\n");
	scanf("%d",&x); 
	n = getAdjacentVertices(g,x, output);
	if(n==0)
		printf("No adjacent vertices of node 1 \n");
	else
	{
		printf("Adjacent vertices of node 1:");
		for(i=0; i<n; i++)
			printf("%5d", output[i]);
		printf("\n");
	}
	printf("nhap diem dau diem cuoi\n");
	scanf("%d %d",&a,&b);
	BFS(g, a, b );
	printf("\n");
	DFS(g, a, b );
	
	
	//printf("nhap diem dau diem cuoi\n");
	//scanf("%d %d",&a,&b);
	//printf("duong di tu a den b \n");
	//ts = getts(g,a,b);
	//printf("%d\n",ts); 
	//BFS(g,a,b,printfdinh);
	*/
	dropGraph(g);
	return 0;
}