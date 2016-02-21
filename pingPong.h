#ifndef PINGPONG_H
#define PINGPONG_H

#include <pthread.h>

class ConnectionInfo{
    public:

        int sockid;
        ConnectionInfo();
        ~ConnectionInfo();
       
    
    private:
};


/*pthread_t *server_threads;
pthread_t *client_threads;
int server_count;
int client_count;*/

int run_server(int port);
int connect_to_server(char* who, int port, ConnectionInfo* con);
int sendMessage(ConnectionInfo* con, char* message);
char* recieveMessage(ConnectionInfo* con);
void dealocate_message(char* mem);
//void* server_respond(int sockfd);


//int connect_to_server(char* port, char* host);
void handleConnection(int clisock);

#endif
