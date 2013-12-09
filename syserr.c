#include "apue.h"
#include <errno.h> 	/* for definition of errno */
#include <stdarg.h>	/* ISO C variable arguments */

static void err_doit(int, int, const char *, va_list);

/* 
 * Nonfatal error related to a system call.
 * Print a message and return.
 */
void err_ret(const char *fmt, ...)
{
	va_list  ap;

	va_start(ap,fmt);
	err_doit(1, errno, fmt, ap);
	va_end(ap);
}

/*
 * Fatal error related to a system call.
 * Print a message and terminate.
 */
void err_sys(const char *fmt, ...)
{
	va_list	ap;

	va_start(ap, fmt);
	err_doit(1, errno, fmt, ap);
	va_end(ap);
}


