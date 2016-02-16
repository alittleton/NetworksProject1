#include <iostream>       // std::cout
#include <pthread.h>  
#include <cstdlib>       
 
void *foo(void* arg) 
{
  std::cout << "foo" << std::endl;
}

void *bar(void *x)
{
  char *num;
  num = (char *) x;
  std::cout << "bar " << num << std::endl;
}

int main() 
{
  pthread_t thread1, thread2;
  //int* num = 12;
  const char *message = "thread 2";

  int t1=pthread_create(&thread1, NULL, foo, NULL);
  int t2=pthread_create(&thread2, NULL, bar, (void*) message);

  std::cout << "main" << std::endl;

  pthread_exit(NULL);



  return 0;
}