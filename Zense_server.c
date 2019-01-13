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
	serveraddr.sin_family =AF_INET;
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	serveraddr.sin_port=htons(9000);

	bind(network_socket,(struct sockaddr *) &serveraddr,sizeof(serveraddr));

	if((listen(network_socket,10)) !=0)
	{
		printf("Listening failed\n");
		exit(0);
	}
	else
	{
		printf("Server is listening\n");
	}
	int len;
	len=sizeof(cli);
	int connect;
	connect=accept(network_socket,(struct sockaddr*)&cli,&len);
	if(connect<0)
	{
		printf("Server did not accept\n");
	}
	else
	{
		printf("Server has accepted the client's request\n");
	}

	chat_function(connect);

	close(network_socket);
	return 0;
}
		
void chat_function(int network_socket)
{
	char message[300];
	int size=0;
	for(;;)
	{
		bzero(message,300);
		read(network_socket,message,sizeof(message));
		printf("Client message : %s",message);
		printf("To Client: ");
		bzero(message,300);
		while((message[size++]=getchar())!='\n')
			;
			write(network_socket,message,sizeof(message));
			if((strncmp("close",message,5))==0)
			{
				printf("Server has exited\n");
				break;
			}
	}
}



