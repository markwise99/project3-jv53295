CC=gcc -pthread
CFLAGS=-I.

test_user: buffer_user_sem.o test_user_sem.o
	$(CC) -o test_user buffer_user_sem.o test_user_sem.o

run:
	./test_user

val:
	valgrind ./test_user

clean:
	rm *.o test_user
