/*
** client.c -- a stream socket client demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
/*
** client.c -- a stream socket client demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "mp3.h"
#include <arpa/inet.h>


// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char *argv[])
{
	int sockfd, numbytes;  
	char buf[MAXDATASIZE];
	struct addrinfo hints, *servinfo, *p;
	int rv;
	char s[INET6_ADDRSTRLEN];
    char * port;
    node * in_node = NULL;

    //Check for the correct number of args
	if (argc != 2) {
	    fprintf(stderr,"usage: client hostname port \n");
	    exit(1);
	}

    port = "2345";

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((rv = getaddrinfo(argv[1], port, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}

	// loop through all the results and connect to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) {
			perror("client: socket");
			continue;
		}

		if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("client: connect");
			continue;
		}

		break;
	}

	if (p == NULL) {
		fprintf(stderr, "client: failed to connect\n");
		return 2;
	}

	inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
			s, sizeof s);
	printf("client: connecting to %s\n", s);

	freeaddrinfo(servinfo); // all done with this structure


//Setup complete

    //while(1){

   	    if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
	        perror("recv");
            exit(1);
	    } 

	    buf[numbytes] = '\0';

        //Print message from the server
        printf("%s\n", buf);

        if((numbytes = recv(sockfd, in_node, MAXDATASIZE-1, 0)) == -1){
        	perror("recv");
            exit(1);
        }

        print_node(in_node, 1);


        // //Take in a user guess
        // scanf("%s", guess);
        // if(send(sockfd, guess, strlen(guess), 0) == -1){
        //     perror("send");        
        //     exit(0);
        // }
    //}









	return 0;
}


















// /*
// ** distvec.c 
// */

// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// #include <unistd.h>
// #include <errno.h>
// #include <string.h>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <netdb.h>
// #include <arpa/inet.h>
// #include <sys/wait.h>
// #include <signal.h>

// #define BACKLOG 10	 // how many pending connections queue will hold

// /*
//  * 
// */



// /*
//  * printForwardingTable
//  * Prints the fowrarding table for the specified nodes
//  * Input: Table
//  * Output: Forwarding table for current node in the format:
//            destination nexthop pathcost
//  */
// void printForwardingTable(distvec_rt * table){

//     int a = 0;
//     for (a = 0; a < table -> numNodes; a++){
//         printf("%d %d %d \n", table -> destination[a], table -> nexthop[a], table -> pathcost[a]);     
//     }
// }



// }

// dvRoutingTable * initDVRT(struct node * connectTable){
// 	dvRoutingTable * table = (dvRoutingTable *) malloc(connectTable-> curr_index) * sizeof(dvRoutingTable));
// 	table -> nodeID = connectTable -> node_num;
// 	table -> numNodes = connectTable -> arr_length;
// 	table -> numNeighbors = connectTable -> curr_index;

// 	table -> nextHop = malloc((connectTable->arr_length) * sizeof(int));
// 	table -> linkCost = mallow((connectTable -> arr_length) * sizeof(int));

// 	int
// }
#include <arpa/inet.h>

#define MAXDATASIZE 100 // max number of bytes we can get at once 

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char *argv[])
{
	int sockfd, numbytes;  
	char buf[MAXDATASIZE];
	struct addrinfo hints, *servinfo, *p;
	int rv;
	char s[INET6_ADDRSTRLEN];
    char guess[4];
    char * port;

    //Check for the correct number of args
	if (argc != 2) {
	    fprintf(stderr,"usage: client hostname port \n");
	    exit(1);
	}

    port = "2345";

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((rv = getaddrinfo(argv[1], port, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}

	// loop through all the results and connect to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) {
			perror("client: socket");
			continue;
		}

		if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("client: connect");
			continue;
		}

		break;
	}

	if (p == NULL) {
		fprintf(stderr, "client: failed to connect\n");
		return 2;
	}

	inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
			s, sizeof s);
	printf("client: connecting to %s\n", s);

	freeaddrinfo(servinfo); // all done with this structure


//Setup complete

    while(1){

   	    if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
	        perror("recv");
            exit(1);
	    } 

	    buf[numbytes] = '\0';

        //Print message from the server
        printf("%s\n", buf);

        //Client guessed the correct numbers, close connection
        if(strcmp(buf, "Correct!") == 0){
            break;
        }

        //Client used 8 guesses, close connection
        if(strcmp(buf, "Game over") == 0){
            break;
        }

        // //Take in a user guess
        // scanf("%s", guess);
        // if(send(sockfd, guess, strlen(guess), 0) == -1){
        //     perror("send");        
        //     exit(0);
        // }
    }









	return 0;
}


















// /*
// ** distvec.c 
// */

// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// #include <unistd.h>
// #include <errno.h>
// #include <string.h>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <netdb.h>
// #include <arpa/inet.h>
// #include <sys/wait.h>
// #include <signal.h>

// #define BACKLOG 10	 // how many pending connections queue will hold

// /*
//  * 
// */



// /*
//  * printForwardingTable
//  * Prints the fowrarding table for the specified nodes
//  * Input: Table
//  * Output: Forwarding table for current node in the format:
//            destination nexthop pathcost
//  */
// void printForwardingTable(distvec_rt * table){

//     int a = 0;
//     for (a = 0; a < table -> numNodes; a++){
//         printf("%d %d %d \n", table -> destination[a], table -> nexthop[a], table -> pathcost[a]);     
//     }
// }



// }

// dvRoutingTable * initDVRT(struct node * connectTable){
// 	dvRoutingTable * table = (dvRoutingTable *) malloc(connectTable-> curr_index) * sizeof(dvRoutingTable));
// 	table -> nodeID = connectTable -> node_num;
// 	table -> numNodes = connectTable -> arr_length;
// 	table -> numNeighbors = connectTable -> curr_index;

// 	table -> nextHop = malloc((connectTable->arr_length) * sizeof(int));
// 	table -> linkCost = mallow((connectTable -> arr_length) * sizeof(int));

// 	int
// }
