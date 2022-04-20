**How to compile and run buffer_user_sem.c**

This will compile buffer_user_sem.c and it's test file, test_user_sem.c

Execute the following commands:
1. *make*
2. *make run*

To test for memory leaks:
1. *make*
2. *make val*

To clean up files:
1. *make clean*

**buffer_user_sem.c**

I mostly struggled with finding the correct syntax for the semaphore function calls
My largest bug was caused by having semwait and sempost in the wrong order in the dequeue function
I tackled these issues through lots of research and experimenting 

**test_user_sem.c**

I had a lot of trouble with the producer and consumer functions. 
I wasn't sure what function we were supposed to use for waiting, and the existence 
of a C function called wait() didn't make this easier. When I decided to use sleep,
I didn't realize it wouldn't take anything shorter than 1 second. As a result, 
I tried to use a float and divide by 1000 to convert my seconds to milliseconds,
only to have this number truncated down to 0 when run. 
When I found out usleep() took ms as input, most of my issues were solved.
