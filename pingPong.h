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

int run_server(int port);
int connect_to_server(char* who, int port, ConnectionInfo* con);
int sendMessage(ConnectionInfo* con, char* message);
char* recieveMessage(ConnectionInfo* con);
void dealocate_message(char* mem);
//void* server_respond(int sockfd);

void handleConnection(int clisock);

#endif
