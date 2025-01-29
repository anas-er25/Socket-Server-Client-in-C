#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

int main()
{
	// Variables declaration
	int sd, cnx, read, nbclt=0;
	char msg_recv[255];
	char msg_send[255];
	struct sockaddr_in servaddr;

	//socket creation
	sd = socket(AF_INET, SOCK_STREAM, 0);
	if(sd<0) printf("Socket error");

	// Server address prepare
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = 1234;
	servaddr.sin_addr.s_addr = INADDR_ANY;

	// Bind to link the socket to address
	bind(sd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	// Listen connexions
	listen(sd, 3);

	// Accept a connexion
	strcpy(msg_send,"well received");
while((cnx = accept(sd, 0, 0))!=0)
{
	nbclt++;
	printf("Connection to client number : %d \n", nbclt);
	if(fork()==0)
	{
		while(1)
		{
		//fork()
		//parent for recv
		read = recv(cnx, msg_recv, sizeof(msg_recv), 0);
		//msg_recv[read]='\0';
		printf("Message received : %s (de size %d)\n", msg_recv, read);
		if(strcmp(msg_recv,"bye")==0) break;
		
		//child for send
		send(cnx, msg_send, sizeof(msg_send), 0);
		}
	// close the connextion
	close(cnx);
	exit(0);
	}
	//else;
}
	printf("End server.\n");

	close(sd);

}