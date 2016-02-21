#include "pingPong.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[]){
    
    ConnectionInfo con;
    int port = atoi(argv[2]);
    //connect_to_server(argv[1], argv[2]);
    connect_to_server(argv[1], port, &con);
    char message[1024];
    char* response;

    while(1){

    	cin.getline(message, sizeof(message));
    	sendMessage(&con, message);

    	response = receiveMessage(&con);  

    	deallocate_message(response);
    	memset(message, '\0', sizeof(message));
    	memset(response, '\0', sizeof(response));
    }

    return 0;

}
