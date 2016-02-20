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
#include <pthread.h>  
#include <cstdlib>

using namespace std;

ConnectionInfo::ConnectionInfo(){

    sockid = 0;
}

ConnectionInfo::~ConnectionInfo(){

}

//void* server_respond(void* sockfd){
void server_respond(int sockfd){

	cout << "server_respond" << endl;
	//int* sockid = (int*) sockfd;
	struct sockaddr_in cli_addr;
	//int newsockfd=*sockid;
	int newsockfd=sockfd;
	unsigned int clilen;
	listen(newsockfd, 10);
	// Loop forever, handling connections.
	while(1) 
	{
		clilen = sizeof(cli_addr);
		newsockfd = accept(newsockfd, (struct sockaddr *) &cli_addr, &clilen);
		if(newsockfd < 0) 
		{
			cerr << "Accept error." << endl;
			exit(1);
		}
		handleConnection(newsockfd);
	}
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
		return 1;
	}

	listen(sockfd, 10);
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

	int* sockfd_point = &sockfd;

	//pthread_t server_thd;
	//pthread_create(&server_thd, NULL, server_respond, (void*) sockfd_point);
	//server_respond(sockfd);
	cout << "thread created" << endl;
	
	return 0;
}



void handleConnection(int clisock){
	cout << "handling" << endl;
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
}

int connect_to_server(char* who, int port, ConnectionInfo* con){
//int connect_to_server(char* host, char* port){
	int sockfd;
	struct sockaddr_in server_addr;
	int msgSize;
	//char message[1024];
	//char output[1024]; // Output message from server.
	struct hostent* hent;
	//memset(output, '\0', 1024); // Clear the buffer.

	
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
		return 1;
	}

	con->sockid=sockfd;

	return 0;
	/*while(1){
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
	}	*/
	//close(sockfd);

}

int sendMessage(ConnectionInfo* con, char* message){
	int msgSize = 0;
	
	if((msgSize = send(con->sockid, message, strlen(message), 0)) < 0) 
	{
		cerr << "Send error." << endl;
		return 1;
	}

	return 0;

}


//void handleConnection(int clisock) 
char* receiveMessage(ConnectionInfo* con){
	int msgSize;
	char buffer[1016]; // 
	char response[1016];
	memset(buffer, '\0', 1016); // Clear the buffer.
	memset(response, '\0', 1016); // Clear the buffer.
	
	if((msgSize = recv(con->sockid, buffer, 1015, 0)) < 0) 
	{
		cerr << "Receive error" << endl;
	}

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
		
	memset(buffer, '\0', 1016); // Clear the buffer.
	memset(response, '\0', 1016); // Clear the buffer.

	char* retval = (char*)malloc(sizeof(response)); //return a pointer to the message
	sprintf(retval, "%s", response);				

	return retval;
}
