/** Distance Vector Protocol **/
/*
** distvec.c 
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

#define BACKLOG 10	 // how many pending connections queue will hold

/*
 * 
 */



/*
 * printForwardingTable
 * Prints the fowrarding table for the specified nodes
 * Input: Table
 * Output: Forwarding table for current node in the format:
           destination nexthop pathcost
 */
void printForwardingTable(distvec_rt * table){

    int a = 0;
    for (a = 0; a < table -> numNodes; a++){
        printf("%d %d %d \n", table -> destination[a], table -> nexthop[a], table -> pathcost[a]);     
    }
}



}

