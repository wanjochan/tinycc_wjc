/* wrapper to libc */

#include "tcc_dl.h"

/* stddef.h */
#ifndef __SIZE_TYPE__

//@ref PTR_SIZE has depedency of ARCH
#if PTR_SIZE == 4
/* 32bit systems. */
#define __SIZE_TYPE__ unsigned int;
#elif LONG_SIZE == 4
/* 64bit Windows. */
#define __SIZE_TYPE__ unsigned long long;
#else
/* Other 64bit systems. */
#define __SIZE_TYPE__ unsigned long;
#endif
#endif //!__SIZE_TYPE__

typedef __SIZE_TYPE__ size_t;

#ifndef NULL
#define NULL ((void*)0)
#endif

#if defined(_SSIZE_T_DEFINED)
#elif defined(__DEFINED_ssize_t)
#elif defined(__SSIZE_T)
typedef __SSIZE_T	ssize_t;
#elif defined(__GNUC__)
//TODO
typedef int ssize_t;
#define __DEFINED_ssize_t
#else
typedef int ssize_t;//TODO tmp...
#endif

//TODO va_list need some transfer from ..., need ASM help !
/* for stdarg.h */

/* string.h */
//char *strcat(char *dest, const char *src);
//char *strchr(const char *s, int c);
//char *strrchr(const char *s, int c);
//char *strcpy(char *dest, const char *src);
//void *memcpy(void *dest, const void *src, size_t n);
//void *memmove(void *dest, const void *src, size_t n);
//void *memset(void *s, int c, size_t n);
//char *strdup(const char *s);
//size_t strlen(const char *s);
//extern int   memcmp( const void *__s1, const void *__s2, size_t __n );
//extern int strcmp( const char *__s1, const char *__s2 );
//extern char *strstr( const char *__s1, const char *__s2 );
//extern int strncmp( const char *__s1, const char *__s2, size_t __n );

#ifdef _WIN32//for win32
//TODO....
#define errno TCC(errno)
#else//not win32
//#include <errno.h>
#ifdef errno
//skip
#else

//TODO  
#ifdef __APPLE__
int *__error();
#define errno (*__error())
#else
int *__errno_location();
#define errno (*__errno_location())
#endif

#endif
#endif//_WIN32


/* unistd.h */
#define SEEK_CUR 1
#define SEEK_END 2
#define SEEK_SET 0

#define	PROT_NONE	0x00	/* [MC2] no permissions */
#define	PROT_READ	0x01	/* [MC2] pages can be read */
#define	PROT_WRITE	0x02	/* [MC2] pages can be written */
#define	PROT_EXEC	0x04	/* [MC2] pages can be executed */
//#include <time.h>
//# include <sys/time.h>

typedef long time_t;
#if defined(__SUSECONDS_T)
typedef __SUSECONDS_T suseconds_t;
#undef __SUSECONDS_T
#else
typedef int suseconds_t;
#endif
struct timeval {
	time_t	tv_sec;		/* seconds */
	suseconds_t		tv_usec;	/* microseconds */
};
struct tm {
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
//	long	tm_gmtoff;	/* offset from UTC in seconds */
//	char	*tm_zone;	/* timezone abbreviation */
};
//TODO...
//struct tm {
//	int	tm_sec;		/* seconds after the minute [0-60] */
//	int	tm_min;		/* minutes after the hour [0-59] */
//	int	tm_hour;	/* hours since midnight [0-23] */
//	int	tm_mday;	/* day of the month [1-31] */
//	int	tm_mon;		/* months since January [0-11] */
//	int	tm_year;	/* years since 1900 */
//	int	tm_wday;	/* days since Sunday [0-6] */
//	int	tm_yday;	/* days since January 1 [0-365] */
//	int	tm_isdst;	/* Daylight Savings Time flag */
//	long	tm_gmtoff;	/* offset from UTC in seconds */
//	char	*tm_zone;	/* timezone abbreviation */
//};

/* fcntl.h */
//#include <fcntl.h>
///*
// *  File access modes.
// */
#define O_RDONLY    000000  /*  Read-only mode  */
#define O_WRONLY    000001  /*  Write-only mode */
#define O_RDWR      000002  /*  Read-Write mode */
///*
// *  Mask for file access modes.
// */
//#define O_ACCMODE   000003
///*
// *  File status flags used for open() and fcntl().
// */
//#define O_NONBLOCK  000200  /*  Non-blocking I/O                */
//#define O_APPEND    000010  /*  Append (writes guaranteed at the end)   */
//#ifndef O_NDELAY
//#define O_NDELAY O_NONBLOCK
//#endif
///*
// *  oflag values for open()
// */
#define O_CREAT     000400  /*  Opens with file create      */
#define O_TRUNC     001000  /*  Open with truncation        */
//#define O_EXCL      002000  /*  Exclusive open          */
//#define O_NOCTTY    004000  /*  Don't assign a controlling terminal */

//TODO
//#include <setjmp.h>
#if defined(__x86_64__)
#define _JBLEN ((9 * 2) + 3 + 16)
#elif defined(__i386__)
#define _JBLEN (18)
#elif defined(__arm__) && !defined(__ARM_ARCH_7K__)
#define _JBLEN		(10 + 16 + 2)
#elif defined(__arm64__) || defined(__ARM_ARCH_7K__)
#define _JBLEN		((14 + 8 + 2) * 2)
#else
#endif

#ifdef _JBLEN
typedef int jmp_buf[_JBLEN];
#else
typedef int jmp_buf[1];
#endif
typedef __SIZE_TYPE__ uintptr_t;

