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

	close(sockid);

}

void* server_respond(void* sockfd){

	char buffer[1016]; // 
	char response[1016];
	int msgSize;

	int sockptr=(intptr_t) sockfd;
	cout << "responding " << sockptr << endl;
	
	
	while((msgSize = recv(sockptr, buffer, 1015, 0)) > 0){
			
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
		
		if((msgSize = send(sockptr, response, strlen(response), 0)) < 0) 
		{
			cerr << "Send error." << endl;
		}

		memset(buffer, '\0', 1016); // Clear the buffer.
		memset(response, '\0', 1016); // Clear the buffer.
	}

	close(sockptr);
}

void* handleConnection(void* clisock){

	int sock = (intptr_t) clisock;
	cout << "handling " << sock << endl;

	pthread_t* threads;
	threads = new pthread_t[50];
    int thread_count = 0;
    

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

		pthread_create(&threads[thread_count], NULL, server_respond, (void*)(intptr_t) newsockfd);
		thread_count++;

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
		close(sockfd);
		return 1;
	}

	pthread_t server_thd;
	pthread_create(&server_thd, NULL, handleConnection, (void*)(intptr_t) sockfd);
	//out << "thread with sockid: " << sockfd << endl;


	return 0;
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
char* recieveMessage(ConnectionInfo* con){
	
	char response[1016];
	memset(response, '\0', 1016);

	int msgSize = 0;
	
	if((msgSize = recv(con->sockid, response, 1015, 0)) < 0) 
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