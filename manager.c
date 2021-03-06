//THIS IS THE MANAGER FILE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "mp2.h"
#include <arpa/inet.h>
#define PORT "2345"
#define BACKLOG 10


void sigchld_handler(int s)
{
	while(waitpid(-1, NULL, WNOHANG) > 0);
}

void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char *argv[])
{

	if (argc != 3) {
		fprintf(stderr,"usage: manager topologyfile messagefile\n");
		exit(1);
	}
	char message[MAXMESSAGENUM][MAXDATASIZE];
	int srcNode[MAXMESSAGENUM], destNode[MAXMESSAGENUM];
	node * topology = parseTopography(argv[1]);
	int totalMessages = 0;
	int nNodes = topology[1].num_nodes;
	int i = 0;
	for(i = 1; i <= nNodes; i++)
		print_node(topology, i);
	totalMessages = parseMessage(argv[2], message, srcNode, destNode);
	for (i = 0; i < totalMessages; i++) {
		printf("%d %d %s\n",srcNode[i], destNode[i], message[i]);
	}

	int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
	struct addrinfo hints, *servinfo, *p;
	struct sockaddr_storage their_addr; // connector's address information
	socklen_t sin_size;
	struct sigaction sa;
	int yes = 1;
	char s[INET6_ADDRSTRLEN];
	int rv;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "manager: getaddrinfo error: %s\n", gai_strerror(rv));
		return 1;
	}	

	// loop through all the results and bind to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) {
			perror("manager: socket");
			continue;
		}

		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
				sizeof(int)) == -1) {
			perror("manager: setsockopt");
			exit(1);
		}

		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("manager: bind");
			continue;
		}
		break;
	}

	if (p == NULL)  {
		fprintf(stderr, "manager: failed to bind\n");
		return 2;
	}

	freeaddrinfo(servinfo); // all done with this structure

	if (listen(sockfd, BACKLOG) == -1) {
		perror("manager: listen");
		exit(1);
	}

	sa.sa_handler = sigchld_handler; // reap all dead processes
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGCHLD, &sa, NULL) == -1) {
		perror("manager: sigaction");
		exit(1);
	}

	printf("manager: waiting for connections...\n");


	while(1) {  // main accept() loop

        sin_size = sizeof their_addr;
        //Aceept incoming connection on listening socket
		new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
		if (new_fd == -1) {
			perror("accept");
			continue;
		}

        //Convert the IP address to a printable form
		inet_ntop(their_addr.ss_family,
			get_in_addr((struct sockaddr *)&their_addr),
			s, sizeof s);
		printf("server: got connection from %s\n", s);

		if (!fork()) { // this is the child process
			close(sockfd); // child doesn't need the listener

        //Send the first message introducing the game
        if(send(new_fd, "SEND TEXT", 13, 0)== -1){
            perror("send");        
            exit(0);
        }

		}
		close(new_fd);  // parent doesn't need this
	}

	return 0;
}
