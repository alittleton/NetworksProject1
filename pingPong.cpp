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

    port = 0;
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

//int connect_to_server(char* who, int port, ConnectionInfo* con){
int connect_to_server(char* host, char* port){
	int sockfd;
	struct sockaddr_in server_addr;
	int msgSize, i_port;
	char message[1024];
	char output[1024]; // Output message from server.
	struct hostent* hent;
	memset(output, '\0', 1024); // Clear the buffer.

	// Check for correct commandline input.
	
	i_port = atoi(port);
	
	// Error check the port number.
	if(i_port <= 10000) 
	{
		cerr << "Port > 10000 required." << endl;
		exit(1);
	}
	
	// Error check the server name.
	if((hent=gethostbyname(host)) == NULL) 
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
	server_addr.sin_port = htons(i_port);

	if(connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) 
	{
		cerr << "Connect error." << endl;
		exit(1);
	}
	cout <<"What message to send: ";
	cin.getline(message,1024);
	if((msgSize = send(sockfd, message, strlen(message), 0)) < 0) 
	{
		cerr << "Send error." << endl;
	}
		
	// Wait to receive response.
	if((msgSize = recv(sockfd, output, 1023, 0)) < 0) 
	{
		cerr << "Receive error." << endl;
	}
	
	cout << output << endl;		
	close(sockfd);

}

void handleConnection(int clisock) 
{
	
	int msgSize;
	char buffer[1016]; // 
	memset(buffer, '\0', 1016); // Clear the buffer.
	
	if((msgSize = recv(clisock, buffer, 1015, 0)) < 0) 
	{
		cerr << "Receive error." << endl;
	}
	
	cout << "Message received from client: " << buffer<<endl;
	char response[1024];
	sprintf(response, "Server: I received the following message:  %s", buffer);
	
	if((msgSize = send(clisock, response, strlen(response), 0)) < 0) 
	{
		cerr << "Send error." << endl;
	}
	
	close(clisock);
}
