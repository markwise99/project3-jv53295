**NOTE TO GRADER**
To save you time compiling kernels, I can tell you that none of my kernel-space implementations will work properly.
I wasn't sure if partial credit is available, so I decided it was best to leave all my files in
*It is probably not worth your time trying to run my kernel-space implementations*

**How to compile and run buffer_user.c**
This will compile buffer_user.c and it's test file, test_user.c
Execute the following commands:
1. *make*
2. *make run*

To test for memory leaks:
1. *make*
2. *make val*

To clean up files:
1. *make clean*

**buffer_user.c**
I wrote the functions in the following order
1. init_buffer_421
2. delete_buffer_421
3. print_buffer_421
4. insert_buffer_421

For the most part, these functions all worked the first time they were tested.
I did have an issue within init where I was making firstNode it's own node,
instead of a pointer to another node.	

My biggest struggle was due to my reluctance to use global variables.
I didn't know how I was going to track anything without one, and had a hard 
time getting started. Once I realized I just needed to make a global buffer,
everything fell into place. I was concerned that with this global buffer I 
would have a hard time with memory allocation, not understanding that all of
it's memory was really allocated within the init function by making space for
nodes, not buffers.  

Once init was properly in place, the rest of the functions were pretty simple
to write - mostly because I understood how to make a "firstNode" and I had 
figured out the global buffer.

**test_user.c**
This file for part 1 is relatively simple. The main function simply calls
all the functions in buffer_user.c it needs to in order to test every edge case.
buffer_user.c should print errors, but never crash.

insert_rand(min, max, iterations) was made to help test these cases without having
to manually call insert_buffer 20 times. It accepts min and max so that I could
know for sure what is being inserted by the function, and what is there by default (0)
 
*Note that as of the day after the due date, no kernel implementations are working*
*I've spent weeks working on the same couple of issues with no results, so I'm going to try and finish all user space implementations a day late*
