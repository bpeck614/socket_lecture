#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{

	struct sockaddr_in serveraddr, clientaddr;
	char buffer[256];
	int sersock;
	int n;
	int clilength = sizeof(clientaddr);

	if (( sersock = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket() error:\n");
		exit(1);
	}

	serveraddr.sin_family = PF_INET;
	serveraddr.sin_port = htons(5232);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if ( (bind(sersock, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0) ) {
		perror("bind() error:\n");
		exit(1);
	}

	while(1) {
		n = recvfrom(sersock, buffer, 256, 0, (struct sockaddr *) &clientaddr, &clilength);
		printf("Received: %s\n", buffer);
		sendto(sersock, buffer, n, 0, (struct sockaddr *) &clientaddr, clilength);


	}
	close(sersock);

}










