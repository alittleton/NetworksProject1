#ifndef PINGPONG_H
#define PINGPONG_H

class ConnectionInfo{
    public:

        int port;
        ConnectionInfo();
        ~ConnectionInfo();
       
    
    private:
};

int run_server(int port);
int connect_to_server(char* who, int port, ConnectionInfo* con);
void handleConnection(int clisock);

#endif
