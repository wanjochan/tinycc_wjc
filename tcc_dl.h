#ifndef _TCC_DL_H
#define _TCC_DL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "tcc_macro.h"

#ifdef _WIN32

//@ref
//https://github.com/dlfcn-win32/dlfcn-win32

#ifndef __DLFCN_H__
# define __DLFCN_H__

///* winnt.h */
//#define DECLARE_HANDLE(name) struct name##__ { int unused; }; typedef struct name##__ *name
///* windef.h */
//DECLARE_HANDLE(HINSTANCE);
//typedef HINSTANCE HMODULE;
//typedef CONST CHAR *LPCSTR,*PCSTR
//WINBASEAPI FARPROC WINAPI GetProcAddress(HMODULE hModule,LPCSTR lpProcName);
//symbol = GetProcAddress( typeof(struct {int unused}) handle, typeof(const char*) name );

//symbol = GetProcAddress( (HMODULE) handle, name );
	
//#if defined(DLFCN_WIN32_EXPORTS)
//#   define DLFCN_EXPORT __declspec(dllexport)
//#else
//#   define DLFCN_EXPORT
//#endif
//
///* POSIX says these are implementation-defined.
// * To simplify use with Windows API, we treat them the same way.
// */
//
//#define RTLD_LAZY   0
//#define RTLD_NOW    0
//
//#define RTLD_GLOBAL (1 << 1)
//#define RTLD_LOCAL  (1 << 2)
//
///* These two were added in The Open Group Base Specifications Issue 6.
// * Note: All other RTLD_* flags in any dlfcn.h are not standard compliant.
// */
//
//#define RTLD_DEFAULT    0
//#define RTLD_NEXT       0
//
//DLFCN_EXPORT void *dlopen ( const char *file, int mode );
//DLFCN_EXPORT int   dlclose(void *handle);
//DLFCN_EXPORT void *dlsym(void *handle, const char *name);
//DLFCN_EXPORT char *dlerror(void);
extern void *dlopen  (const char *file, int mode);
extern int   dlclose (void *handle);
extern void *dlsym   (void * handle, const char * name);
extern char *dlerror (void);

//#define RTLD_DEFAULT   ((void *) 0)
//#define RTLD_NEXT      ((void *) -1l)
//#define RTLD_LAZY					-1
//#define RTLD_NOW					-1
//#define RTLD_BINDING_MASK -1
//#define RTLD_NOLOAD				-1
//#define RTLD_GLOBAL				-1

#define RTLD_DEFAULT      0
#define RTLD_NEXT         -1
#define RTLD_LAZY					-1
#define RTLD_NOW					-1
#define RTLD_BINDING_MASK -1
#define RTLD_NOLOAD				-1
#define RTLD_GLOBAL				-1

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

#ifdef __APPLE__//{
//@ref https://opensource.apple.com/source/Libwrappers/Libwrappers-9/dlcompat/dlfcn.h.auto.html
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

#else//}!__APPLE__{
#define RTLD_LAZY   1
#define RTLD_NOW    2
#define RTLD_NOLOAD 4
//#define RTLD_NODELETE 4096
//#define RTLD_GLOBAL 256

#define RTLD_LAZY     0x1
#define RTLD_NOW      0x2
#define RTLD_NOLOAD   0x4
#define RTLD_GLOBAL   0x100
#define RTLD_NODELETE 0x1000
#define RTLD_LOCAL    0x0

#define RTLD_NEXT    ((void *)-1)
#define RTLD_DEFAULT ((void *)0)
#endif

//#define tcc_dlsym dlsym
//TODO make tcc_dlsym() more clever with tcc_dl.c ?
//TODO make tcc_dlopen dlopen( #LIB , RTLD_GLOBAL | RTLD_LAZY)
//TODO prepare function if speedup?
#endif/* __DLFCN_H__ */
#endif//}

// TCC( SM, TYPE=void*, LIB=c)
// cast the symbol as a function that returns type-specified or void* as default.
//#define TCC(SYM,...) ((TCC_OR_ELSE(void*,__VA_ARGS__)(*)())tcc_dlsym(#SYM))//OK
//typedef void*(*tcc_func_ptr_void)();
//#define TCC(SYM,...) (TCC_IF_ELSE(__VA_ARGS__)((__VA_ARGS__(*)())tcc_dlsym(#SYM),tcc_dlsym_(#SYM)))//OK
#define TCC(SYM,...) (TCC_IF_ELSE(__VA_ARGS__)((__VA_ARGS__(*)())tcc_dlsym(#SYM),tcc_dlsym_(#SYM)))
//TODO make TCC(SYM,TYPE,LIB) which LIB is not c....

//TODO....
//#define TCC_DL_IMPORT(LIB) TCC_DL_dlopen( lib##LIB##TCC_DL_EXT )

//#ifndef _WIN32
#ifndef __STDIO_H_
typedef struct __FILE FILE;
#endif
//typedef struct __sFILE FILE;
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

#else//TODO for !__APPLE__

/* Very Standard streams.  */
extern FILE *stdin;		/* Standard input stream.  */
extern FILE *stdout;		/* Standard output stream.  */
extern FILE *stderr;		/* Standard error output stream.  */

///* C89/C99 say they're macros.  Make them happy.  */
#define stdin stdin
#define stdout stdout
#define stderr stderr

#endif//__APPLE__

static inline void* tcc_dlsym(const char* sym){return dlsym(RTLD_DEFAULT,sym);}
//static inline tcc_func_ptr_void tcc_dlsym_(const char* sym){return (tcc_func_ptr_void) dlsym(RTLD_DEFAULT,sym);}//OK
static inline typeof(void*(*)()) tcc_dlsym_(const char* sym){return (void*(*)())dlsym(RTLD_DEFAULT,sym);}

static inline void* tcc_dlopen(const char* lib){return dlopen(lib,RTLD_GLOBAL|RTLD_LAZY);}

//FILE* tcc_stdfile[3]=NULL;//={stdin,stdout,stderr};

//enum{
//    TCC_C_stdin,
//    TCC_C_stdout,
//    TCC_C_stderr,
//};

#define TCC_C_stdin 1
#define TCC_C_stdout 2
#define TCC_C_stderr 3

static inline FILE* tcc_std(int std){
	if(TCC_C_stdin==std)return stdin;
	if(TCC_C_stdout==std)return stdout;
	if(TCC_C_stderr==std)return stderr;
	return (FILE*)0;
}

//failed test, the dlsym load __stderrp not same as extern FILE defined....
//static FILE* tcc_stdfile[4]={(void*)0,(void*)0,(void*)0,(void*)0};
//static inline FILE* tcc_dlsym_a_or_b(const char* a, const char* b){
//	FILE*rt;rt=dlsym(RTLD_DEFAULT,a);if(rt)return rt;rt=dlsym(RTLD_DEFAULT,b);return rt;
//}
//static inline FILE* tcc_std(int std){
//
//	((void*(*)())dlsym(RTLD_DEFAULT,"printf"))("%d,%d,%d,%d\n",
//	dlsym(RTLD_DEFAULT,"stderr"),
//	stderr,
//	dlsym(RTLD_DEFAULT,"__stderrp"),
//	((void*(*)())dlsym(RTLD_DEFAULT,"__stderrp"))()
//	);
//	
//	if(TCC_C_stdin==std)return stdin;
//	if(TCC_C_stdout==std)return stdout;
//	//if(TCC_C_stdout==std)return (FILE*)dlsym(RTLD_DEFAULT,"__stdoutp");//tcc_dlsym_a_or_b("stdout","__stdoutp");
//	if(TCC_C_stderr==std)return stderr;
//	return (FILE*)0;
//	
//	return tcc_dlsym_a_or_b("stdin","__stdinp");
//	if(tcc_stdfile[std])return tcc_stdfile[std];
//	if(std==1){
//		tcc_stdfile[std]=tcc_dlsym_a_or_b("stdin","__stdinp");
//	}else if(std==2){
//		tcc_stdfile[std]=tcc_dlsym_a_or_b("stdout","__stdoutp");
//	}else if(std==3){
//		tcc_stdfile[std]=tcc_dlsym_a_or_b("stderr","__stderrp");
//	}
//	return tcc_stdfile[std];
//}

//stdio/stdout/stderr wrapping
//TODO maybe merge to TCC() later
#define TCCSTD(STD) tcc_std(TCC_C_std##STD)
//#define TCCSTD(STD) tcc_stdfile[TCC_C_std##STD]

#ifdef __cplusplus
}
#endif

#endif//_TCC_DL_H
