#include "mp2.h"

int num_nodes(int source[], int dest[], int size)
{
	int i = 0;
	int maxValueA = source[0];
	int maxValueB = dest[0];
	for (i = 1; i < size; i++)
	{
		if (source[i] > maxValueA)
			maxValueA = source[i];
	}
	for (i = 1; i < size; i++)
	{
		if (dest[i] > maxValueB)
			maxValueB = dest[i];
	}
	if (maxValueA > maxValueB)
		return maxValueA;
	else
		return maxValueB;
}

node *parseTopography(char * file)
{
	FILE * f = fopen(file, "r");
	if (f == NULL)
	{
		printf("parse error\n");
		exit(1);
	}
	int total_nodes = 0;
	int lines = 0;
	int ch;
	int i = 0;
	char c_source[STRINGSIZE];
	char c_dest[STRINGSIZE];
	char c_cost[STRINGSIZE];

	while ((ch=fgetc(f)) != EOF) {
		if (ch == '\n')
			lines++;
	}
	lines = lines-1;
	int srcNode[lines], destNode[lines], nodeCost[lines];
	fclose(f);
	f = fopen(file, "r");
	while (!feof(f))
	{
		fscanf(f, "%s", c_source);
		fscanf(f, "%s", c_dest);
		fscanf(f, "%s", c_cost);

		srcNode[i] = atoi((char*)&c_source);
		destNode[i] = atoi((char*)&c_dest);
		nodeCost[i] = atoi((char*)&c_cost);

		i++;

	}
	total_nodes = num_nodes(srcNode, destNode, lines);
	node *topology = malloc((total_nodes) * sizeof(node));
	for (i = 1; i <= lines; i++)
	{
		node * n = initNode(i, total_nodes, 0, 0, 0);
		topology[i] = *n;
	}
	for (i = 0; i < lines; i++)
	{
		addNode(topology, srcNode[i], destNode[i], nodeCost[i]);
		addNode(topology, destNode[i], srcNode[i], nodeCost[i]);
	}
	int port = INIT_ROUTER_PORT;
	for (i = 0; i < total_nodes; i++)
	{
		assignPorts(topology, i, port);
		port++;
	}

	return topology;
}

int parseMessage(char * file, char message[MAXMESSAGENUM][MAXDATASIZE], int srcNode[MAXMESSAGENUM], int destNode[MAXMESSAGENUM])
{
	FILE * f = fopen(file, "r");
	if (f == NULL)
	{
		printf("parse error\n");
		exit(1);
	}
	int i = 0;

	char c_source[STRINGSIZE];
	char c_dest[STRINGSIZE];
	char c_message[MAXMESSAGENUM];
	int ch;
	while (!feof(f))
	{
		if (i == 0) {
			fscanf(f, "%s", c_source);
			srcNode[i] = atoi((char*)&c_source);
		}
		else
			srcNode[i] = atoi((char*)&c_source) - TODECIMAL;
		fscanf(f, "%s", c_dest);
		destNode[i] = atoi((char*)&c_dest);
		fscanf(f, "%s", c_message);
		strcpy(message[i], c_message);
		while ((ch=fgetc(f)) != '\n') {
			strcat(message[i], " ");
			fscanf(f, "%s", c_message);
			strcat(message[i], c_message);
		}
		message[i][strlen(message[i]) + 1] = '\0';
		i++;
		if ((ch=fgetc(f)) != -1)
			sprintf(c_source, "%d", ch);
		else
			break;

	}
	return i;
}
