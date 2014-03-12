#include "mp3.h"

node * initNode(int node_num, int nNodes, int num_neigh, int dest, int cost)
{
	node *n = malloc(sizeof(node) + (2 * (nNodes * sizeof(int))));
	int i = 0;

	n->nodeId = node_num;
	n->num_nodes = nNodes;
	n->num_neighbors = num_neigh;

	n->list_of_neighbors = malloc(nNodes * sizeof(int));
	n->list_of_neighbors[0] = dest;

	n->costs = malloc(nNodes * sizeof(int));
	n->costs[0] = cost;

	n->ports = malloc(nNodes * 6 * sizeof(int));

	for(i = 0; i<nNodes; i++)
	{
		n->list_of_neighbors[i] = -1;
		n->costs[i] = -1;
		n->ports[i] = -1;
	}

	n->costs[0] = cost;
	n->list_of_neighbors[0] = dest;

	return n;
}

void addNode(node * topology, int src, int dest, int cost)
{
	int i = (topology[src]).num_neighbors;
	topology[src].list_of_neighbors[i] = dest;
	topology[src].costs[i] = cost;
	topology[src].num_neighbors++;
}

void assignPorts(node * topology, int src, int port)
{
	int l = topology[0].num_nodes;
	int i = 0, j = 0, n = 0;
	for(i = 0; i < l; i++)
	{
		n = topology[i].num_neighbors;
		for (j = 0; j < n; j++)
		{
			if(topology[i].list_of_neighbors[j] == src)
			{
				topology[i].ports[j] = port;
			}
		}
	}
}

void print_node(node *n, int index)
{
	printf("********************\n");
	if (n[index].nodeId == -1)
	{
		printf("***EMPTY NODE***\n");
		return;
	}
	printf("Node: %d\n", n[index].nodeId);
	printf("Src\tDest\tCost\tPort\n");

	int i = 0;
	for (i = 0; i < n[index].num_neighbors; i++)
	{
		if((n[index].list_of_neighbors[i] != -1) && (n[index].costs[i] != -1)) {
			printf("%d\t%d\t%d\t%d\n",n[index].nodeId, n[index].list_of_neighbors[i], n[index].costs[i], n[index].ports[i]);
		}
	}
}

