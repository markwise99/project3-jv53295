// File: buffer_user_sem.c
// Author: Mark Wise
// Description: User space implementation of bound buffer problem solution
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "buffer_sem.h"

static bb_buffer_421_t buffer;
static sem_t mutex;
static sem_t fill_count;
static sem_t empty_count;

long init_buffer_421(void) {
   // Write your code to initialize buffer
   printf("DEBUG: in init_buffer_421\n");
   int i;

   // If buffer exists, exit
   if (buffer.read){
      printf("DEBUG: Buffer already exists, returning -1\n");
      return -1;
   }else{
      // Else, initialize buffer
      buffer.length = 0;

      // First node is useful for initialization and
      // completing the "circle" by pointing the 20th node to first node
      bb_node_421_t *firstNode = NULL;

      // Make (SIZE_OF_BUFFER) new nodes
      for(i = 0; i < SIZE_OF_BUFFER; i++){
         // Allocate data for current node
         bb_node_421_t *node = malloc(sizeof(bb_node_421_t));

         // Set default values
         node->data[0] = 0; // FOR TESTING, CHANGE
         node->next = NULL;

         // If first node, set vals
         if(i == 0){
            firstNode = node;
            buffer.read = node;
            buffer.write = node;
         }

         // Point the prev node to curr node
         // Move read pointer to curr node
         buffer.read->next = node;
         buffer.read = node;
      }
      // make full circle
      buffer.read->next = firstNode;

      buffer.read = firstNode; // need to setup to prevent segfault?

   }
   printf("DEBUG: init success --- returning 0\n");
   //return 0;
   // Initialize your semaphores here.
   sem_init(&mutex, 1, 1);
   sem_init(&fill_count, 1, 0);
   sem_init(&empty_count, 1, SIZE_OF_BUFFER);
   return 0;
}

// producer func inside test.c
long enqueue_buffer_421(char * data){
   // TODO: Cannot insert data into an uninitialized buffer
   if(buffer.read == NULL){
      printf("ERROR: Cannot insert data into an uninitialized buffer\n");
      return 1;
   }
   sem_wait(&empty_count);
   sem_wait(&mutex);

   printf("DEBUG: Enqueue: %c\n", data[0]);
   // Copy 1024 bytes from data into write node's data 
   memcpy(buffer.write->data, data, DATA_LENGTH);
   buffer.length++;
   // Update buffer's write pointer
   buffer.write = buffer.write->next;

   sem_post(&mutex);
   sem_post(&fill_count);
   print_semaphores();
   return 0;

}

long dequeue_buffer_421(char * data) {
   if(buffer.read == NULL){
      printf("ERROR: Cannot dequeue an uninitialized buffer\n");
      return 1;
   }
   printf("DEBUG: Enqueuing\n");
	// Write your code to dequeue data from the buffer
   sem_wait(&mutex);
   sem_wait(&fill_count);
   printf("DEBUG: HERE 1\n");

   // Copies 1024 bytes from the read node into the provided buffer data
   memcpy(data, buffer.read->data, DATA_LENGTH);
   printf("DEBUG: HERE 2\n");
   buffer.length--; // ?????
   printf("DEBUG: HERE 3\n");

   buffer.read = buffer.read->next;
   printf("DEBUG: Dequeue: %c\n", data[0]);
   sem_post(&empty_count);
   sem_post(&mutex);
   print_semaphores();
   return 0;
}


long delete_buffer_421(void) {
   // Tip: Don't call this while any process is waiting to enqueue or dequeue.
   // write your code to delete buffer and other unwanted components

   // If buffer is uninitialized, return -1
   if(buffer.read == NULL){
      printf("ERROR: Can't delete uninitialized buffer. Returning -1\n");
      return -1;
   }

   // Traversal Nodes
   bb_node_421_t *firstNode = buffer.read;
   bb_node_421_t *currNode  = firstNode->next;
   bb_node_421_t *nextNode  = NULL;

   // Stop freeing when firstNode is reached
   while(currNode != firstNode){
      nextNode = currNode->next;
      free(currNode);
      currNode = nextNode;
   }
   // Free firstNode and reset pointers
   free(currNode);
   buffer.read = NULL;
   buffer.write = NULL;
   printf("DEBUG: Buffer deleted successfully. Returning 0.\n");

   sem_destroy(&mutex);
   sem_destroy(&fill_count);
   sem_destroy(&empty_count);
   return 0;
}

void print_semaphores(void) {
	// You can call this method to check the status of the semaphores.
	// Don't forget to initialize them first!
	// YOU DO NOT NEED TO IMPLEMENT THIS FOR KERNEL SPACE.
	int value;
	sem_getvalue(&mutex, &value);
	printf("sem_t mutex = %d\n", value);
	sem_getvalue(&fill_count, &value);
	printf("sem_t fill_count = %d\n", value);
	sem_getvalue(&empty_count, &value);
	printf("sem_t empty_count = %d\n", value);
	return;
}
