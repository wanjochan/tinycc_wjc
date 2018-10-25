/* Dynmaic c libc header for TCC */
//TODO do tcc_dl_XXXX() later
#ifndef _TCC_DL_H
#define _TCC_DL_H

#include "tcc_macro.h"

#ifdef _WIN32
#ifndef __DLFCN_H__
# define __DLFCN_H__

//make them external because these are provided by sys
extern void *dlopen  (const char *file, int mode);
extern int   dlclose (void *handle);
extern void *dlsym   (void * handle, const char * name);
extern char *dlerror (void);

#define RTLD_NEXT      ((void *) -1l)
#define RTLD_DEFAULT   ((void *) 0)
#define RTLD_LAZY					-1
#define RTLD_NOW					-1
#define RTLD_BINDING_MASK -1
#define RTLD_NOLOAD				-1
#define RTLD_GLOBAL				-1

//#define tcc_dlsym dlsym
#define tcc_dlopen dlopen

#endif /* __DLFCN_H__ */
#else//not _WIN32
#ifndef __DLFCN_H__
# define __DLFCN_H__
//# include <dlfcn.h>

//will do later... damn!
////make them external because these are provided by sys
extern void *dlopen  (const char *file, int mode);
extern int   dlclose (void *handle);
extern void *dlsym   (void * handle, const char * name);
extern char *dlerror (void);
#ifdef __APPLE__
#define RTLD_LAZY	0x1
#define RTLD_NOW	0x2
#define RTLD_LOCAL	0x4
#define RTLD_GLOBAL	0x8

#if !defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE)
#define RTLD_NOLOAD	0x10
#define RTLD_NODELETE	0x80
#define RTLD_FIRST	0x100	/* Mac OS X 10.5 and later */

/*
 * Special handle arguments for dlsym().
 */
#define	RTLD_NEXT	((void *) -1)	/* Search subsequent objects. */
#define	RTLD_DEFAULT	((void *) -2)	/* Use default search algorithm. */
#define	RTLD_SELF	((void *) -3)	/* Search this and subsequent objects (Mac OS X 10.5 and later) */
#define	RTLD_MAIN_ONLY	((void *) -5)	/* Search main executable only (Mac OS X 10.5 and later) */
#endif /* not POSIX */

#else//!__APPLE__
#define RTLD_LAZY   1
#define RTLD_NOW    2
#define RTLD_NOLOAD 4
#define RTLD_NODELETE 4096
#define RTLD_GLOBAL 256
#define RTLD_LOCAL  0

#define RTLD_NEXT    ((void *)-1)
#define RTLD_DEFAULT ((void *)0)
#endif

//#define tcc_dlsym dlsym
#define tcc_dlopen dlopen
//TODO make tcc_dlsym() more clever with tcc_dl.c ?
//TODO make tcc_dlopen dlopen( #LIB , RTLD_GLOBAL | RTLD_LAZY)
//TODO prepare function if speedup?
#endif/* __DLFCN_H__ */
#endif

//TODO maybe improve tcc_dlsym() with somehou caching?

// TCC( SM, TYPE=void*, LIB=c)
// cast the symbol as a function that returns type-specified or void* as default.
#define TCC(SYM,...) ((TCC_OR_ELSE(void*,__VA_ARGS__)(*)())tcc_dlsym(#SYM))
//TODO make TCC(SYM,TYPE,LIB) which LIB is not c....

//TODO....
//#define TCC_DL_IMPORT(LIB) TCC_DL_dlopen( lib##LIB##TCC_DL_EXT )

//#ifndef _WIN32
typedef struct __FILE FILE;
//#endif

//#ifdef __APPLE__
//#define TCC_DL_EXT .dylib
//#else
//#define TCC_DL_EXT .so
//
////TODO WIN32 later
//
//#endif

#ifdef __APPLE__
extern FILE *__stdinp;
extern FILE *__stdoutp;
extern FILE *__stderrp;
#define stdin __stdinp
#define stdout __stdoutp
#define stderr __stderrp
#else

/* Very Standard streams.  */
extern FILE *stdin;		/* Standard input stream.  */
extern FILE *stdout;		/* Standard output stream.  */
extern FILE *stderr;		/* Standard error output stream.  */

///* C89/C99 say they're macros.  Make them happy.  */
//#define stdin stdin
//#define stdout stdout
//#define stderr stderr

#endif//__APPLE__

static inline void* tcc_dlsym(char* sym) {
	return dlsym(RTLD_DEFAULT,sym);
}

#endif//_TCC_DL_H

