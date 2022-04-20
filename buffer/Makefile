CC=gcc
CFLAGS=-I.

test: buffer_user.o test_user.o
	$(CC) -o test_user buffer_user.o test_user.o

run:
	./test_user

val:
	valgrind ./test_user

clean:
	rm *.o test_user
