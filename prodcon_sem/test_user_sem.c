// File: test_user_sem.c
// Author: Mark Wise
// Description: Test file
#include "buffer_sem.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

// from research gate (not working)
void *producer(void){
   int i = 0, item;
   char data[DATA_LENGTH];
   while(i < 1000){
      item = rand() % 1000;
      // wait 0-10ms
      // data
      //call enqueue
    
   }

void *consumer(void){
   


}

int main(){

   // define 2 threads
   pthread_t thread1, thread2;

   init_buffer_421();

   if (pthread_create(&thread1, NULL, producer, NULL) != 0){
      fprint("Debug. Unable to crete producer thread\n");
      exit(1);
   }
   if (pthread_create(&thread2, NULL, consumer, NULL) != 0){
      fprint("Debug. Unable to crete consumer thread\n");
      exit(1);
   }

   pthread_join(thread1, NULL);
   pthread_join(thread2, NULL);
   //enqueue_buffer_421("f");
   //dequeue_buffer_421(" ");
   
   delete_buffer_421();
   return 0;
}
