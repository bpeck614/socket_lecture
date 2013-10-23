#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
	struct sockaddr_in remoteaddr;
	int remotelength = sizeof(remoteaddr);
	int clisock;
	char buffer[256];
	int  n;

	if ( ( clisock = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket() error:\n");	
		exit(1);
	}

	remoteaddr.sin_family = PF_INET;
	remoteaddr.sin_port = htons(5232);
	remoteaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	while(1) {
		fgets(buffer, 255, stdin);
		sendto(clisock, buffer, strlen(buffer), 0, (struct sockaddr *) &remoteaddr, remotelength);
		n = recvfrom(clisock, buffer, 256, 0, (struct sockaddr *) &remoteaddr, &remotelength);
		printf("Recieved: %s\n", buffer);


	}
	close(clisock);


}
