// File: buffer_mon.c
// Author: Mark Wise
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include "buffer_mon.h"

static ring_buffer_421_t buffer;
static pthread_mutex_t mutex;
static pthread_cond_t fill_count;
static pthread_cond_t empty_count;

long init_buffer_421(void) {
   // Write your code to initialize buffer
   int i;

   // If buffer exists, exit
   if (buffer.read){
      printf("ERROR: Buffer already exists.\n");
      return -1;
   }else{
      // Else, initialize buffer
      buffer.length = 0;

      // First node is useful for initialization and
      // completing the "circle" by pointing the 20th node to first node
      node_421_t *firstNode = NULL;

      // Make (SIZE_OF_BUFFER) new nodes
      for(i = 0; i < SIZE_OF_BUFFER; i++){
         // Allocate data for current node
         node_421_t *node = malloc(sizeof(node_421_t));

         // Set default values
         node->data[0] = 0;
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

      // prevents segfault
      buffer.read = firstNode;

   }
   printf("Initialization success\n");

   // Initialize mutex and cond var pthreads
   pthread_mutex_init(&mutex, NULL);
   pthread_cond_init(&fill_count, NULL);
   pthread_cond_init(&empty_count, NULL);

   return 0;
}

// producer function inside test_mon.c
long enqueue_buffer_421(char * data){
   // Check for uninitialized buffer
   if(buffer.read == NULL){
      printf("ERROR: Cannot insert data into an uninitialized buffer\n");
      return 1;
   }

   // lock if buffer is full
   pthread_mutex_lock(&mutex);
   if(buffer.length == 20){
      pthread_cond_wait(&empty_count, &mutex);
   }

   printf("--- Enqueue: %c ---\n", data[0]);
   // Copy 1024 bytes from data into write node's data 
   memcpy(buffer.write->data, data, DATA_LENGTH);
   buffer.length++;
   // Update buffer's write pointer
   buffer.write = buffer.write->next;

   // unlock
   pthread_cond_signal(&fill_count);
   pthread_mutex_unlock(&mutex);
   return 0;
}

// consumer function inside test_mon.c
long dequeue_buffer_421(char * data) {
   if(buffer.read == NULL){
      printf("ERROR: Cannot dequeue an uninitialized buffer\n");
      return 1;
   }

   // lock if empty
   pthread_mutex_lock(&mutex);
   if(buffer.length == 0){
      pthread_cond_wait(&fill_count, &mutex);
   }

   // Copies 1024 bytes from the read node into the provided buffer data
   memcpy(data, buffer.read->data, DATA_LENGTH);
   buffer.length--;
   printf("--- Dequeue: %c ---\n", data[0]);
   buffer.read = buffer.read->next;

   // unlock
   pthread_cond_signal(&empty_count);
   pthread_mutex_unlock(&mutex);

   return 0;
}

// delete buffer and other unwanted components
long delete_buffer_421(void) {

   // If buffer is uninitialized, return -1
   if(buffer.read == NULL){
      printf("ERROR: Can't delete uninitialized buffer.\n");
      return -1;
   }

   // Traversal Nodes
   node_421_t *firstNode = buffer.read;
   node_421_t *currNode  = firstNode->next;
   node_421_t *nextNode  = NULL;

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
   printf("Buffer deleted successfully.\n");

   // clean up pthreads
   pthread_mutex_destroy(&mutex);
   pthread_cond_destroy(&fill_count);
   pthread_cond_destroy(&empty_count);
   return 0;
}
