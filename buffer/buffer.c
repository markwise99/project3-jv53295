// File: buffer.c
// Author: Mark Wise
// Description: Implementation of the kernel-space circular buffer
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include "buffer.h"

// Need this globally to check whether or not a buffer exists
static ring_buffer_421_t buffer;

// Initialize a new circular buffer in memory
// Allocate memory for each of the 20 nodes
// The final node's next pointer should point to the first
// Each node stores an initial int value of 0
// Return 0 if successful, -1 if fails
SYSCALL_DEFINE0(init_buffer_421){
   node_421_t *node;
   node_421_t *firstNode;
   int i = 0;
   printk("DEBUG: in init_buffer_421\n");

   // Init all vars before anything else

   // If buffer exists, exit
   if (buffer.read){
      printk("DEBUG: Buffer already exists, returning -1\n");
      return -1;
   }else{
      // Else, initialize buffer
      buffer.length = 0;

      // First node is useful for initialization and
      // completing the "circle" by pointing the 20th node to first node

      // Make (SIZE_OF_BUFFER) new nodes
      while(i < SIZE_OF_BUFFER){
         // Allocate data for current node
         node = kmalloc(sizeof(node_421_t), GFP_KERNEL);

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
         i++;
      }
      // make full circle
      buffer.read->next = firstNode;
   }
   printk("DEBUG: init success --- returning 0\n");
   return 0;
}

// Insert int i into next available node
// If the buffer is full, insertion fails(if length == 20)
// Returns 0 if successful, -1 if fails
//long insert_buffer_421(int i){
SYSCALL_DEFINE1(insert_buffer_421, int, i){
   if(buffer.read && buffer.length < 20){
      printk("DEBUG: Inserting val - %d\n", i);
      buffer.write->data = i;
      buffer.write = buffer.write->next;
      buffer.length++;
      return 0;
   }else{
      // Print which of the two errors and return 
      if(buffer.read == NULL){
         printk("ERROR: Buffer is uninitialized\n");
      }else{
         printk("ERROR: Buffer is full\n");
      }
      return -1;
   }
}

// Prints a string representation of every node in the buffer
// along with the data in each node to stdout
// Cannot print an uninitialized buffer
// Returns 0 if successful, -1 if fails
SYSCALL_DEFINE0(print_buffer_421){
   int i;

   // If buffer has been initialized, print
   if(buffer.read){
      printk("---PRINTING BUFFER---\n");

      // + 1 is for testing. remove. **********************
      for(i = 0; i < (SIZE_OF_BUFFER + 1); i++){
         printk("THIS data: %d\n", buffer.read->data);
         printk("NEXT data: %d\n", buffer.read->next->data);
         printk("---------------------\n");
         buffer.read = buffer.read->next;
      }
      return 0;
   }else{
      printk("DEBUG: Can't print uninitialized buffer, returning -1\n");
      return -1;
   }
}

// If a buffer exists, delete it
// Free any memory allocated in init_buffer_421
// Returns 0 if successful, -1 if not
SYSCALL_DEFINE0(delete_buffer_421){
   node_421_t *firstNode;
   node_421_t *currNode;
   node_421_t *nextNode;

   // If buffer is uninitialized, return -1
   if(buffer.read == NULL){
      printk("ERROR: Can't delete uninitialized buffer. Returning -1\n");
      return -1;
   }

   // Traversal Nodes
   firstNode = buffer.read;
   currNode  = firstNode->next;
   nextNode  = NULL;

   // Stop freeing when firstNode is reached
   while(currNode != firstNode){
      nextNode = currNode->next;
      kfree(currNode);
      currNode = nextNode;
   }
   // Free firstNode and reset pointers
   kfree(currNode);
   buffer.read = NULL;
   buffer.write = NULL;
   printk("DEBUG: Buffer deleted successfully. Returning 0.\n");
   return 0;
}

