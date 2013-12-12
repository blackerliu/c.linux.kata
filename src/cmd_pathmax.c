#include "apue.h"
#include <errno.h>
#include <limits.h>

#ifdef PATH_MAX
static int path_max = PATH_MAX;
#else
static int path_max = 0;
#endif

#define SUSV3	200112L

static long posix_version = 0;

/* If PATH_MAX is indeterminate, no guarantee this is a adequate */
#define PATH_MAX_GUESS 1024

char *path_alloc(int *sizep) /* also return allocated size, if nonull */
{
	char *ptr;
	int size;

	if(posix_version == 0){
		posix_version = sysconf(_SC_VERSION);
	}

	if(path_max == 0){

		errno = 0;
		
		if((path_max = pathconf("/", _PC_PATH_MAX)) < 0){
			if(errno == 0){
				path_max = PATH_MAX_GUESS;			
			} else {
				err_sys("pathconf error for _PC_PATH_MAX");
			}
		} else {
			path_max++;
		}
	}

	if(posix_version < SUSV3){
		size = path_max + 1;
	} else {
		size = path_max;
	}
	
	if((ptr = malloc(size)) == NULL){
		err_sys("malloc error for pathname");
	}

	if(sizep != NULL){
		*sizep = size;
	}
	
	return (ptr);
}

int main(void)
{
	return 0;
}
