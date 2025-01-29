#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<unistd.h>
#include<string.h>

int main()
{
	// Variables declaration
	int sd, read;
	char msg_send[255];
	char msg_recv[255];
	struct sockaddr_in servaddr;

	//socket creation
	sd = socket(AF_INET, SOCK_STREAM, 0);
	if(sd<0) printf("Socket error");

	// Server address prepare
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = 1234;
	servaddr.sin_addr.s_addr = INADDR_ANY;

	// To Start Connection with server
	connect(sd, (struct sockaddr *)&servaddr, sizeof(servaddr));

while(1)
	{
	// send/recv
	printf("Enter a message (finish by bye): ");gets(msg_send);
	send(sd, msg_send, sizeof(msg_send), 0);
	if(strcmp(msg_send,"bye")==0) break;
	read = recv(sd, msg_recv, sizeof(msg_recv), 0);
	msg_recv[read]='\0';
	printf("Server answer : %s.\n",msg_recv);
	}
	printf("End client.\n");
	
	// close the connextion
	close(sd);
}