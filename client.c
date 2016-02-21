#include "pingPong.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
  if( argc < 2){
    printf("give port as command line argument\n");
    return 1;
  }

  int port = atoi(argv[1]);

  ConnectionInfo info;
  if( connect_to_server( "localhost", port, &info)){
    printf("Failed to connect to server\n");
    return 1;
  }

  while( 1 ){
    char buff[4096];
    //read a string
    fgets(buff, 4096, stdin);

    int len = strlen(buff);
    buff[len-1]=0;//-1 to remove trailing \n

    //send the string.
    sendMessage(&info, buff);

    //recieve the string
    char * msg = recieveMessage(&info);
    if( msg == NULL ){
      printf("Failed to recieve message\n");
      return 1;
    }

    printf("%s\n",msg);
    dealocate_message(msg);
  }

  return 2; //shouldn't ever run
}
