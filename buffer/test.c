// File: test.c
// Author: Mark Wise
// Description: Test file for the kernel space implementation of circular buffer

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
//#define __NR_hello 441
#define __NR_init_buffer_421 442
#define insert_buffer_421 443
#define print_buffer_421 444
#define delete_buffer_421 445

//443     common  insert_buffer_421       sys_insert_buffer_421
//444     common  print_buffer_421        sys_print_buffer_421
//445     common  delete_buffer_421       sys_delete_buffer_421

long init_buffer_syscall(void)
{

return syscall(__NR_init_buffer_421);

}

int main(int argc, char *argv[]){
   if (init_buffer_syscall() < 0)
      perror("Bro what");
   return 0;
}
