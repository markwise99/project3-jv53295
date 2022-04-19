// File: buffer_user.c
// Author: Mark Wise
// Description: Implementation of the user-space circular buffer
#include "buffer.h"
#include <stdio.h>  // fprint
#include <stdlib.h> // malloc

// Need this globally to check whether or not a buffer exists
static ring_buffer_421_t buffer;

// Initialize a new circular buffer in memory
// Allocate memory for each of the 20 nodes
// The final node's next pointer should point to the first
// Each node stores an initial int value of 0
// Return 0 if successful, -1 if fails
long init_buffer_421(void){
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
      node_421_t *firstNode = NULL;

      // Make (SIZE_OF_BUFFER) new nodes
      for(i = 0; i < SIZE_OF_BUFFER; i++){
         // Allocate data for current node
         node_421_t *node = malloc(sizeof(node_421_t));

         // Set default values
         node->data = 0;
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
   }
   printf("DEBUG: init success --- returning 0\n");
   return 0;
}

// Insert int i into next available node
// If the buffer is full, insertion fails(if length == 20)
// Returns 0 if successful, -1 if fails
long insert_buffer_421(int i){
   if(buffer.read && buffer.length < 20){
      printf("DEBUG: Inserting val - %d\n", i);
      buffer.write->data = i;
      buffer.write = buffer.write->next;
      buffer.length++;
      return 0;
   }else{
      // Print which of the two errors and return 
      if(buffer.read == NULL){
         printf("ERROR: Buffer is uninitialized\n");
      }else{
         printf("ERROR: Buffer is full\n");
      }
      return -1;
   }
}

// Prints a string representation of every node in the buffer
// along with the data in each node to stdout
// Cannot print an uninitialized buffer
// Returns 0 if successful, -1 if fails
long print_buffer_421(){
   int i;

   // If buffer has been initialized, print
   if(buffer.read){
      printf("---PRINTING BUFFER---\n");

      // + 1 is for testing. remove. **********************
      for(i = 0; i < (SIZE_OF_BUFFER + 1); i++){
         printf("THIS data: %d\n", buffer.read->data);
         printf("NEXT data: %d\n", buffer.read->next->data);
         printf("---------------------\n");
         buffer.read = buffer.read->next;
      }
      return 0;
   }else{
      printf("DEBUG: Can't print uninitialized buffer, returning -1\n");
      return -1;
   }
}

// If a buffer exists, delete it
// Free any memory allocated in init_buffer_421
// Returns 0 if successful, -1 if not
long delete_buffer_421(){
   // If buffer is uninitialized, return -1
   if(buffer.read == NULL){
      printf("ERROR: Can't delete uninitialized buffer. Returning -1\n");
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
   printf("DEBUG: Buffer deleted successfully. Returning 0.\n");
   return 0;
}
