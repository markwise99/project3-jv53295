// File: test_user.c
// Author: Mark Wise
// Description: Test file for the user space implementation of circular buffer

#include "buffer.h"
#include <stdio.h>
#include <stdlib.h> // rand

// Inserts random numbers into buffer
// Iterations is the number of inserts
// Min and max set the rand range
void insertRand(int min, int max, int iterations){
   int randNum, i;
   for(i = 0; i < iterations; i++){
      randNum = rand() % (max + 1 - min) + min;
      printf("Inserting randNum: %d\n", randNum);
      insert_buffer_421(randNum);
   }
}

int main(){
   delete_buffer_421();
   print_buffer_421();
   init_buffer_421();
   print_buffer_421();
   init_buffer_421();
   delete_buffer_421();
   delete_buffer_421();
   insertRand(20, 40, 20);
   init_buffer_421();
   insertRand(20, 40, 20);
   print_buffer_421();
   insertRand(10, 20, 10);
   delete_buffer_421();

   return 0;
}
