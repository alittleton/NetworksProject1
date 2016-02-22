/*Andrew Littleton CSC 4200 Spring '16
pingPong is designed to run a server on a 
provided port and allow multiple clients
to connect using threads.  A data structure
of type ConnectionInfo is created upon 
calling connect_to_server which contains the
connection information necessary to send
and receive messages
*/


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

#endif
