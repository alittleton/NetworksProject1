// Andrew Littleton CSC 4200 Spring '16
//NOTE: must be compiled with the -std=c++11 and -pthread flags

#include "pingPong.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <unistd.h>
#include <netdb.h>  
#include <cstdlib>
#include <iostream>
#include <thread>

using namespace std;

ConnectionInfo::ConnectionInfo(){

    sockid = 0;

    
}

ConnectionInfo::~ConnectionInfo(){

	close(sockid);

}

/* this handles the server responses to the client,
	returns "PONG" is PING or ping is sent, otherwise
	returns the message that was sent
*/
void server_respond(int sockptr){

	char buffer[4096]; 
	char response[4096];
	int msgSize;

	//int sockptr=(intptr_t) sockfd;

	while((msgSize = recv(sockptr, buffer, 4095, 0)) > 0){
			
			//cout << buffer << endl;

		if(buffer[0]=='P' && buffer[1]=='I'&& buffer[2]=='N' && buffer[3]=='G' && buffer[4] == '\0'){
			sprintf(response, "PONG");
		}
		else if(buffer[0]=='p' && buffer[1]=='i'&& buffer[2]=='n' && buffer[3]=='g' && buffer[4] == '\0'){
			sprintf(response, "PONG");
		}
		else{
			sprintf(response, "%s", buffer);
		}	
		
		if((msgSize = send(sockptr, response, strlen(response), 0)) < 0) 
		{
			cerr << "Send error." << endl;
		}

		memset(buffer, '\0', 4096); //clear buffer so it can be reused
		memset(response, '\0', 4096);
	}

	close(sockptr);
}

/* this handles the accepting of clients to 
	the server and if successful, spawns
	a new thread that monitors server_respond
*/
void handleConnection(int sock){
    

	int newsockfd;

	struct sockaddr_in cli_addr;
	unsigned int clilen;
	listen(sock, 10);
	clilen = sizeof(cli_addr);

	while(1){	
		newsockfd = accept(sock, (struct sockaddr *) &cli_addr, &clilen);
		if(newsockfd < 0) 
		{
			cerr << "Accept error." << endl;
			exit(1);
		}

		std::thread (server_respond, newsockfd).detach();

	}

}


int run_server(int port){

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
		cerr << "Bind error." << endl;
		close(sockfd);
		return 1;
	}

	std::thread(handleConnection, sockfd).detach();

	return 0;
}

int connect_to_server(char* who, int port, ConnectionInfo* con){

	int sockfd;
	struct sockaddr_in server_addr;
	int msgSize;
	struct hostent* hent;
	
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

	cout << "Ready to send messages" << endl;

	con->sockid=sockfd;

	return 0;

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

char* recieveMessage(ConnectionInfo* con){
	
	char response[4096];
	memset(response, '\0', 4096);

	int msgSize = 0;
	
	if((msgSize = recv(con->sockid, response, 4095, 0)) < 0) 
	{
		cerr << "Receive error" << endl;
	}

	char* retval = (char*)malloc(sizeof(response)); //return a pointer to the message
	sprintf(retval, "%s", response);				

	return retval;
}

void dealocate_message(char* mem){
	free(mem);
}