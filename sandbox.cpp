#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

int main(){

	char foo[50];
	char bar[10] = "PONG";

	char buff[30] = "Hello, World";
	cout << sizeof(buff) << endl;
	char* buff_alloc = (char*)malloc(sizeof(buff));
	sprintf(buff_alloc, "%s", buff);

	cout << buff_alloc << endl;

	free(buff_alloc);
	
	

	return 0;
}

//old handleconnection code
/*int msgSize;
	char buffer[1016]; // 
	char response[1016];
	memset(buffer, '\0', 1016); // Clear the buffer.
	memset(response, '\0', 1016); // Clear the buffer.
	
	while((msgSize = recv(clisock, buffer, 1015, 0)) > 0) 
	{
		cout << buffer << endl;

		if(buffer[0]=='P' && buffer[1]=='I'&& buffer[2]=='N' && buffer[3]=='G'){
			sprintf(response, "PONG");
		}
		else if(buffer[0]=='p' && buffer[1]=='i'&& buffer[2]=='n' && buffer[3]=='g'){
			sprintf(response, "PONG");
		}
		else{
			sprintf(response, "%s", buffer);
		}	
		
		if((msgSize = send(clisock, response, strlen(response), 0)) < 0) 
		{
			cerr << "Send error." << endl;
		}

		memset(buffer, '\0', 1016); // Clear the buffer.
		memset(response, '\0', 1016); // Clear the buffer.
	}*/