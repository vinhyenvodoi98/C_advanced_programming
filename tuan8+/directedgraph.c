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

void addEdge(Graph graph, int v1, int v2, float weight) // v1--> v2
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
		jrb_insert_int(tree, v2, new_jval_f(weight));
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
			printf("%d va %.2f",jval_i(node->key),jval_f(node1->val));
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
		printf("%d va %.2f",jval_i(node1->key),jval_f(node1->val));
		total ++;
	}
	return total;
}

/*int DAG(Graph graph)
{
	int visited[1000];
	int n, output[100], i, u, v, start;
	Dllist node, stack;
	JRB vertex;

	jrb_traverse(vertex, graph.vertices)
	{
		memset(visited, 0, sizeof(visited));

		start = jval_i(vertex -> key);
		stack = new_dllist();
		dll_append(stack, new_jval_i(start));
		while(!dll_empty(stack))
		{
			node = dll_last(stack);
			u = jval_i(node -> val);
			dll_delete_node(node);
			if(!visited[u])
			{
				visited[u] = 1;
				n = outdegree(graph, u, output);
				for(i=0; i<n; i++)
				{
					v = output[i];
					if(v == start) // cycle detected
						return 0;
					if(! visited[v])
						dll_append(stack, new_jval_i(v));
				}
			}
		}
	}
	return 1; // no cycle
}*/

void dijstra(Graph graph, int start, int stop)
{
    int visited[1000];
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
	int n,m,i,t;
	int a[100];
	char b[100];

	Graph g = createGraph();
	addVertex(g, 1, "Nam");
	addVertex(g, 2, "Nam2");
	addVertex(g, 3, "Nam3");
	addVertex(g, 4, "Nhung");
	addEdge(g,1,2,5.5);
	addEdge(g,2,3,3.2);
	addEdge(g,3,4,1.3);
	addEdge(g,4,1,3.3);
	//printf("nhap :\n");
	//scanf("%d",&t);
	//n = indgree(g,t,a);
	//n = outdegree(g,t,a);
	//printf("\nAdjacent vertices of node :");
	//for(i=0; i<n; i++)
	//	printf("%5d", a[i]);
	printf("nhap 2 diem dau cuoi\n");
	scanf("%d %d",&a,&b);
	dijstra(g,a,b);
	strcpy(b, getVertex(g, t));
	printf("\nb = %s\n", b);
	dropGraph(g);
	return 1;
}