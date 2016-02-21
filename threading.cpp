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
  // pthread_t thread1, thread2;
  pthread_t *threads = new pthread_t[2];
  //int* num = 12;
  const char *message = "thread 2";

  for(int i = 0; i<2; i++){
    pthread_create(&threads[i], NULL, foo, NULL);
  }

  for(int i=0; i<2; i++){
    pthread_join(threads[i], NULL);
  }
  // int t1=pthread_create(&thread1, NULL, foo, NULL);
  // int t2=pthread_create(&thread2, NULL, bar, (void*) message);

  std::cout << "main" << std::endl;

  pthread_exit(NULL);



  return 0;
}