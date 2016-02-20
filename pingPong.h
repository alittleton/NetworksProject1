#ifndef PINGPONG_H
#define PINGPONG_H

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
char* receiveMessage(ConnectionInfo* con);
//void* server_respond(int sockfd);


//int connect_to_server(char* port, char* host);
void handleConnection(int clisock);

#endif
