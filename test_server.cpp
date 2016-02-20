#include "pingPong.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[]){
    
    int port = atoi(argv[1]);
    cout << "server: " << run_server(port) << endl;

    while(1){sleep(10);}

    return 0;

}
