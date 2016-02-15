#include "pingPong.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[]){
    
    ConnectionInfo thing1 = ConnectionInfo();
    int port = atoi(argv[1]);
    connect_to_server(argv[1], argv[2]);

    return 0;

}
