#include "pingPong.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[]){
    
    ConnectionInfo con;
    int port = atoi(argv[2]);
    //connect_to_server(argv[1], argv[2]);
    connect_to_server(argv[1], port, &con);

    return 0;

}
