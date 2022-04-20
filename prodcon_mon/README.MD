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

**buffer_mon.c**

I again copied my code over from the semaphore implementation
I started by removing all semaphores and replacing them with pthread equivalents
I struggled with pthread syntax quite a bit
I solved this by doing research online. 
In particular, I found [this website](cis.temple.edu/~giorgio/old/cis307s97/readings/pbuffer.html) to be really helpful

**test_mon.c**

The same as test_user_sem.c. 
