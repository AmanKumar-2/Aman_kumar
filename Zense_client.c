#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
void chat_function(int network_socket);

int main()
{
	int network_socket;
	network_socket=socket(AF_INET,SOCK_STREAM,0);
	if(network_socket==-1)
	{
		printf("Socket could not be created\n");
		exit(0);
	}
	else
	{
		printf("Socket is created\n");
	}

	struct sockaddr_in serveraddr,cli;
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	serveraddr.sin_port=htons(9000);

	int connection_status;
	connection_status=connect(network_socket,(struct sockaddr *) &serveraddr,sizeof(serveraddr));
	if(connection_status!=0)
	{
		printf("Connection failed\n");
		exit(0);
	}
	else
	{
		printf("We are connected to the server\n");
	}

	chat_function(network_socket);
	close(network_socket);
	return 0;
}

void chat_function(int network_socket)
{
	char message[300];
	int size=0;
	int i;
	for(i=0;i>-1;i++)
	{
		bzero(message,300);
		printf("Enter the comment: ");
		size=0;
		while((message[size++] =getchar()) !='\n')
			;
			write(network_socket,message,sizeof(message));
			bzero(message,300);
			read(network_socket,message,sizeof(message));
			printf("Server message : %s",message);
			if((strcmp("close",message))==0)
			{
				printf("Client has decided to exit the chat\n");
				break;
			}
	}
}




