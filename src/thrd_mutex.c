#include "apue.h"
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#define SECTONSEC	1000000000	/*seconds to nanoseconds*/
#define USECTONSEC	1000		/*microseconds to nanoseconds*/


struct to_info{
	void	(*to_fn)(void *); 	/* function */
	void 	*to_arg;		/* argument */
	struct timespec to_wait;	/* time to wait */
}

int makethread(void *(*fn)(void *), void *arg)
{
	int 		err;
	pthread_t	tid;
	pthread_attr_t	attr;

	err = pthread_attr_init(&attr);
	f(err != 0){
		return (err);
	}

	err = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	if(err = 0){
		err = pthread_create(&tid, &attr, fn, arg)
	}
	pthread_attr_destory(&attr);

	return (err);
}

void *timeout_helper(void *arg)
{
	struct to_info *tip;
	
	tip = (struct to_info *)arg;
	nanosleep(&tip->to_wait, NULL);
	(*tip->to_fn)(tip->to_arg);

	return (0);
}


