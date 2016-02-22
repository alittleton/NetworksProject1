#include "pingPong.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <thread>

using namespace std;

void foo(){
	cout << "foo" << endl;
}

void bar(int x){
	cout << x << endl;
}

int main(){

	std::thread first (foo);     // spawn new thread that calls foo()
  	std::thread second (bar,0);  // spawn new thread that calls bar(0)

  	std::cout << "main, foo and bar now execute concurrently...\n";

	// synchronize threads:
	first.join();                // pauses until first finishes
	second.join();               // pauses until second finishes

	std::cout << "foo and bar completed.\n";


	
	
	

	return 0;
}

