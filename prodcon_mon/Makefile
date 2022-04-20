CC=gcc -pthread
CFLAGS=-I.

test_user: buffer_mon.o test_mon.o
	$(CC) -o test_user buffer_mon.o test_mon.o

run:
	./test_user

val:
	valgrind ./test_user

clean:
	rm *.o test_user
