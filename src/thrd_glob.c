#include "apue.h"
#include <pthread.h>

int glob = 6;	/* external variable in initialized data */
char buf[] = "a write to stdout\n";

void *thr_fn(void *arg)
{
	int *var;

	var = (int *)arg;

	printf("sub thread: tid = %x, glob = %d, var = %d\n", (int)pthread_self(), glob, *var);
	(*var)++;
	glob++;	  	 /* modify variables */

	printf("sub thread: tid = %x, glob = %d, var = %d\n", (int)pthread_self(), glob, *var);
}

int main(void)
{
	int var;	/* automatic variable on the stack */
	int err;
	pthread_t tid;
	
	var = 88;
	if(write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1){
		err_sys("write error");
	}
	printf("before pthread_create\n"); /* we don't flush stdout */

	
	printf("main thread: tid = %x, glob = %d, var = %d\n", (int)pthread_self(), glob, var);

	err = pthread_create(&tid, NULL, thr_fn, &var);
	if(err != 0){
		err_quit("can't create thread: %s\n", strerror(err));
	}
	sleep(2);
	
	printf("main thread: tid = %x, glob = %d, var = %d\n", (int)pthread_self(), glob, var);
	
}


