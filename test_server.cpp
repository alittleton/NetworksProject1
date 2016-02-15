#include "pingPong.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[]){
    
    char hostname[1024] = "\0";
    gethostname(hostname, 1023);
    //printf("Hostname: %s\n", hostname);

    int port = atoi(argv[1]);
    run_server(port);

    return 0;

}
