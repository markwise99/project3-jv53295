// File: test_mon.c
// Author: Mark Wise
// Description: Test file
#include "buffer_mon.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // for usleep()

// writes sequential blocks of characters
// randomly waits 0-10ms prior to each enqueue
// param is there to prevent compiler warnings
void *producer(void *param){
   int i = 0, j = 0, charAsInt;
   int waitTime = 0;
   char currChar;
   char data[DATA_LENGTH]; // passed to enqueue
   for(i = 0; i < 1000; i++){
      // wait 0-10ms
      // usleep takes time in milliseconds
      waitTime = (rand() % 11);
      usleep(waitTime);

      // Get a digit 0-9, then convert to char
      charAsInt = i % 10;
      currChar = charAsInt + '0'; // uses ASCII logic

      // fill data char array with the same char (currChar)
      for(j = 0; j < DATA_LENGTH; j++){
         data[j] = currChar;
      }
      //call enqueue data
      enqueue_buffer_421(data);
      printf("Produced: %c\n", data[0]);

   }
}

// Retrieves sequential blocks of characters from the buffer
// Randomly waits 0-10ms prior to each dequeue
// param prevents compiler warnings
void *consumer(void *param){
   int i = 0, j = 0, charAsInt;
   float waitTime = 0;
   char currChar;
   char data[DATA_LENGTH];
   for(i = 0; i < 1000; i++){
      // Get a digit 0-9, then convert to char
      charAsInt = i % 10;
      currChar = charAsInt + '0';
      waitTime = (rand() % 11);
      usleep(waitTime);

      // fill data char array with the same char (currChar)
      for(j = 0; j < DATA_LENGTH; j++){
         data[j] = currChar;
      }

      // dequeue, end for loop
      dequeue_buffer_421(data);
      printf("Consumed: %c\n", data[0]);
   }
}

int main(){

   // define 2 threads
   pthread_t thread1, thread2;
   init_buffer_421();

   // attempt to create pthreads and call producer & consumer
   if (pthread_create(&thread1, NULL, producer, NULL) != 0){
      printf("ERROR: Unable to crete producer thread\n");
      exit(1);
   }
   if (pthread_create(&thread2, NULL, consumer, NULL) != 0){
      printf("ERROR: Unable to crete consumer thread\n");
      exit(1);
   }

   // Prevent leakage
   pthread_join(thread1, NULL);
   pthread_join(thread2, NULL);

   delete_buffer_421();
   return 0;
}
