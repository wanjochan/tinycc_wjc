#ifndef _TCC_PLATFORM_H
#define _TCC_PLATFORM_H

///////////////////////////////////////////////////////////////////////////
// __TCC_CPU__ : current cpu type
#if defined(__X86__)||defined(_X86_)||defined(__i386__)||defined(__x86_64__)||defined(_AMD64_)
# if (defined __x86_64__ || defined _AMD64_)
#  define __TCC_CPU_BIT__ 64
# endif
#	define __TCC_CPU__  X86
#elif defined(__PPC__)
#	define __TCC_CPU__  PPC
#elif defined(__MIPS__)
#	define __TCC_CPU__  MIPS
#elif defined(__SH__)
#	define __TCC_CPU__  SH
#elif defined(__arm__) || defined(__aarch64__)
# if defined(__aarch64__)
#  define __TCC_CPU_BIT__ 64
# endif
#	define __TCC_CPU__  ARM
#else
//TODO getenv ?
# define __TCC_CPU__
#endif

// __TCC_CPU_BIT__ : current cpu bits
#ifndef __TCC_CPU_BIT__
# ifdef __TCC_CPU_BIT_DEFAULT__
#  define __TCC_CPU_BIT__ __TCC_CPU_BIT__
# else
#  define __TCC_CPU_BIT__ 32
# endif
#endif

// __TCC_OS__ : current os

///////////////////////////////////////////////////////////////////////////
#ifndef __TCC_OS__//{

#if defined(_WIN32)||defined(_WIN64)
#	define __TCC_OS__  WIN
# define __TCC_OS_FORMAT__  PE
#elif defined(__APPLE__)
#	define __TCC_OS__  OSX
# define __TCC_OS_FORMAT__  MACHO
#elif defined(__linux__)||defined(__LINUX__)
#	define __TCC_OS__  LNX
# define __TCC_OS_FORMAT__  ELF
#elif defined(__FreeBSD__)
#	define __TCC_OS__  FREEBSD
# define __TCC_OS_FORMAT__  ELF
#elif defined(__NetBSD__)
#	define __TCC_OS__  NETBSD
# define __TCC_OS_FORMAT__  ELF
#elif defined(__QNXNTO__)
#	define __TCC_OS__  QNXNTO
# define __TCC_OS_FORMAT__  ELF
#elif defined(__QNX__)
#	define __TCC_OS__  QNX
# define __TCC_OS_FORMAT__  ELF
#elif defined(__TccOS__)
#	define __TCC_OS__  TCCOS
# define __TCC_OS_FORMAT__  ELF
#else
//# define __TCC_OS__
#endif

#endif //}__TCC_OS__

//TODO iOS@Darwin/Android@Linux?

///////////////////////////////////////////////////////////////////////////
#ifndef __TCC_CC__//{

#if defined(__MWERKS__)
# define __TCC_CC__  MWERKS
#elif defined(__WATCOMC__)
# define __TCC_CC__  WATCOMC
#elif defined(__GNUC__)
# define __TCC_CC__  GNUC
#elif defined(__HIGHC__)
# define __TCC_CC__  HIGHC
#elif defined(__INTEL_COMPILER)
# define __TCC_CC__  INTEL
#elif defined(__TINYC__)
# define __TCC_CC__  TINYCC
#else
# define __TCC_CC__
#endif

#endif //}__TCC_CC__

///////////////////////////////////////////////////////////////////////////
#ifndef __TCC_TARGET_CPU__//{

#if defined(TCC_TARGET_I386)
# define __TCC_TARGET_CPU__ X86
#elif defined(TCC_TARGET_X86_64)
# define __TCC_TARGET_CPU__ X86
#elif defined(TCC_TARGET_ARM)
# define __TCC_TARGET_CPU__ ARM
#elif defined(TCC_TARGET_ARM64)
# define __TCC_TARGET_CPU__ ARM
#elif defined(TCC_TARGET_PPC)
# define __TCC_TARGET_CPU__ PPC
#elif defined(TCC_TARGET_MIPS)
# define __TCC_TARGET_CPU__ MIPS
#elif defined(TCC_TARGET_SH)
# define __TCC_TARGET_CPU__ SH
#else
//# define __TCC_TARGET_CPU__
#endif

#endif//}__TCC_TARGET_CPU__

#ifndef __TCC_TARGET_CPU__
# define __TCC_TARGET_CPU__ __TCC_CPU__
#endif
///////////////////////////////////////////////////////////////////////////
#ifndef __TCC_TARGET_CPU_BIT__//{

#if defined(TCC_TARGET_I386)
# define __TCC_TARGET_CPU_BIT__ 32
#elif defined(TCC_TARGET_X86_64)
# define __TCC_TARGET_CPU_BIT__ 64
#elif defined(TCC_TARGET_X86_ARM)
#elif defined(TCC_TARGET_PPC)
#elif defined(TCC_TARGET_MIPS)
#elif defined(TCC_TARGET_SH)
#endif

#endif//}__TCC_TARGET_CPU_BIT__

#ifndef __TCC_TARGET_CPU_BIT__
# define __TCC_TARGET_CPU_BIT__ __TCC_CPU_BIT__
#endif

///////////////////////////////////////////////////////////////////////////
#ifdef __TCC_TARGET_FORMAT__
//SKIP THEN
#elif defined(TCC_TARGET_MACHO)
# define __TCC_TARGET_FORMAT__  MACHO
# define __TCC_TARGET_OS__  OSX
#elif defined(TCC_TARGET_PE)
# define __TCC_TARGET_FORMAT__  PE
# define __TCC_TARGET_OS__  WIN
#else
//#ifdef __TCC_OS_FORMAT__
//# define __TCC_TARGET_FORMAT__ __TCC_OS_FORMAT__
//#else
//# define __TCC_TARGET_FORMAT__  ELF
//#endif
# define __TCC_TARGET_FORMAT__  ELF
#endif

///////////////////////////////////////////////////////////////////////////
//TODO not good, need to adjust Makefile better?
#ifndef __TCC_TARGET_OS__
//# define __TCC_TARGET_OS__ __TCC_OS__
# define __TCC_TARGET_OS__ LNX
#endif

///////////////////////////////////////////////////////////////////////////
//TODO
//#define TCC_CPU_X86  1
//#define TCC_CPU_ARM  2
//#define TCC_CPU_MIPS 3
//#define TCC_CPU_PPC  4
//#define TCC_CPU_SH   5
//#if (EXPAND(TCC_CPU_##__TCC_TARGET_CPU__)==EXPAND(TCC_CPU_##__TCC_CPU__))
//# define __TCC_TARGET_CROSS__ 0
//#else
//# define __TCC_TARGET_CROSS__ 1
//#endif
# define __TCC_TARGET_CROSS__  TODO

//TODO redefine for cross build... for tcc_define_symbol later

#endif//_TCC_PLATFORM_H
