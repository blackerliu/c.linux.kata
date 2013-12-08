#ifndef _APUE_H
#define _APUE_H

#define _XOPEN_SOURCE 600 /* Single UNIX Specification, Version 3 */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/termios.h>

#ifndef TIOCGWINSZ
#include <sys/ioctl.n>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#define MAXLINE  4096

/* 
 * Default file access permissions for new files.
 */
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH )

/*
 * Default permissions for new directories.
 */
#define DIR_MODE (FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH )

typedef void Sigfunc(int); /* for signal handlers */

#if defined(SIG_IGN) && !defined(SIG_ERR)
#define SIG_ERR((Sigfunc *) -1)
#endif

#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b)) 

/*
 * Prototypes for own fuctions
 */
char        *path_alloc(int *);
long        open_max(void);
void        clr_fl(int, int);
void        set_fl(int, int);
void        pr_exit(int);
void        pr_mask(const char *);
Singfunc    *signal_intr(int, Sigfunc *);

int         tty_cbreak(int);
int         tty_raw(int);
int         tty_reset(int);
int         tty_atexit(void);
#ifdef ECHO     /* only if <termios.h> has been included. */
struct termios *tty_termios(void);
#endif


#endif
