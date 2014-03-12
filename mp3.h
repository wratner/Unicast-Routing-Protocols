
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>

#define MAXDATASIZE 200
#define STRINGSIZE 10
#define MAXNODENUM 16
#define INIT_ROUTER_PORT 7806
#define MAXMESSAGENUM 20
#define TODECIMAL 48



typedef struct {
	int nodeId;
	int num_nodes;
	int num_neighbors;
	int *list_of_neighbors;
	int *costs;
	int *ports;
} node;

/*NETWORK*/
void sigchld_handler(int s);

void *get_in_addr(struct sockaddr *sa);


/* NODE */
node *initNode (int node_num, int nNodes, int num_neigh, int dest, int cost);

void addNode(node * topology, int src, int dest, int cost);

void assignPorts(node * topology, int src, int port);

void print_node(node * n, int index);

/* PARSE */
node *parseTopography(char * file);

int parseMessage(char * file, char message[MAXMESSAGENUM][MAXDATASIZE], int srcNode[MAXMESSAGENUM], int destNode[MAXMESSAGENUM]);


