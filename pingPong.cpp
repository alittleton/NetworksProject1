#include "pingPong.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <unistd.h>
#include <netdb.h>

using namespace std;

ConnectionInfo::ConnectionInfo(){

    sockid = 0;
}

ConnectionInfo::~ConnectionInfo(){

}

int run_server(int port){
	std::cout << port << std::endl;

	int sockfd, newsockfd;
	unsigned int clilen;	
	// Structures for client and server addresses.
	struct sockaddr_in server_addr, cli_addr;
	
	// Create the server socket.
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{
		cerr << "Socket error." << endl;
		exit(1);
	}
	
	memset((void *) &server_addr, 0, sizeof(server_addr)); // Clear the server address structure.
	
	// Set up the server address structure.
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(port);
	
	// Bind the socket to the server address and port.
	if(bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) 
	{
		cerr << "Bind error.";
		exit(1);
	}
	
	// Listen on the socket, queue 5 incoming connections.
	listen(sockfd, 10);
	
	// Loop forever, handling connections.
	while(1) 
	{
		clilen = sizeof(cli_addr);
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		if(newsockfd < 0) 
		{
			cerr << "Accept error." << endl;
			exit(1);
		}
		handleConnection(newsockfd);
	}
	
}

int connect_to_server(char* who, int port, ConnectionInfo* con){
//int connect_to_server(char* host, char* port){
	int sockfd;
	struct sockaddr_in server_addr;
	int msgSize, i_port;
	char message[1024];
	char output[1024]; // Output message from server.
	struct hostent* hent;
	memset(output, '\0', 1024); // Clear the buffer.

	
	// Error check the server name.
	if((hent=gethostbyname(who)) == NULL) 
	{
		cerr << "Invalid host name." << endl;
		exit(1);
	}
	
	// Create the client socket.
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{
		cerr << "Socket error." << endl;
		exit(1);
	}
	
	memset((void *) &server_addr, 0, sizeof(server_addr)); // Clear the server address structure.
	
	// Set up the server address structure.
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr = *((struct in_addr *)hent->h_addr);
	server_addr.sin_port = htons(port);

	if(connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) 
	{
		cerr << "Connect error." << endl;
		exit(1);
	}

	con->sockid=sockfd;
	while(1){
		cout << "Enter your message: ";
		cin.getline(message,1024);
		if((msgSize = send(con->sockid, message, strlen(message), 0)) < 0) 
		{
			cerr << "Send error." << endl;
		}
			
		// Wait to receive response.
		if((msgSize = recv(con->sockid, output, 1023, 0)) < 0) 
		{
			cerr << "Receive error." << endl;
		}
		
		cout << output << endl;

		memset(output, '\0', 1024); // Clear the buffer.
		memset(message, '\0', 1024); // Clear the buffer.
	}	
	//close(sockfd);

}

void handleConnection(int clisock) 
{
	int msgSize;
	char buffer[1016]; // 
	char response[1016];
	memset(buffer, '\0', 1016); // Clear the buffer.
	memset(response, '\0', 1016); // Clear the buffer.
	
	while((msgSize = recv(clisock, buffer, 1015, 0)) > 0) 
	{
		cout << buffer << endl;

		if(buffer[0]=='P' && buffer[1]=='I'&& buffer[2]=='N' && buffer[3]=='G'){
			sprintf(response, "PONG");
		}
		else if(buffer[0]=='p' && buffer[1]=='i'&& buffer[2]=='n' && buffer[3]=='g'){
			sprintf(response, "PONG");
		}
		else{
			sprintf(response, "%s", buffer);
		}	
		
		if((msgSize = send(clisock, response, strlen(response), 0)) < 0) 
		{
			cerr << "Send error." << endl;
		}

		memset(buffer, '\0', 1016); // Clear the buffer.
		memset(response, '\0', 1016); // Clear the buffer.
	}
	
	
	
	
	close(clisock);
}
