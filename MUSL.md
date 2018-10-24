# 

* https://en.wikipedia.org/wiki/Musl
	musl is a C standard library intended for operating systems based on the Linux kernel, released under the MIT License. It was developed by Rich Felker with the goal to write a clean, efficient and standards-conformant libc implementation.
* https://www.musl-libc.org/

## tcc.h

```
/* name of ELF interpreter */
#ifndef CONFIG_TCC_ELFINTERP
# if defined __FreeBSD__
#  define CONFIG_TCC_ELFINTERP "/libexec/ld-elf.so.1"
# elif defined __FreeBSD_kernel__
#  if defined(TCC_TARGET_X86_64)
#   define CONFIG_TCC_ELFINTERP "/lib/ld-kfreebsd-x86-64.so.1"
#  else
#   define CONFIG_TCC_ELFINTERP "/lib/ld.so.1"
#  endif
# elif defined __DragonFly__
#  define CONFIG_TCC_ELFINTERP "/usr/libexec/ld-elf.so.2"
# elif defined __NetBSD__
#  define CONFIG_TCC_ELFINTERP "/usr/libexec/ld.elf_so"
# elif defined __GNU__
#  define CONFIG_TCC_ELFINTERP "/lib/ld.so"
# elif defined(TCC_TARGET_PE)
#  define CONFIG_TCC_ELFINTERP "-"
# elif defined(TCC_UCLIBC)
#  define CONFIG_TCC_ELFINTERP "/lib/ld-uClibc.so.0" /* is there a uClibc for x86_64 ? */
# elif defined TCC_TARGET_ARM64
#  if defined(TCC_MUSL)
#   define CONFIG_TCC_ELFINTERP "/lib/ld-musl-aarch64.so.1"
#  else
#   define CONFIG_TCC_ELFINTERP "/lib/ld-linux-aarch64.so.1"
#  endif
# elif defined(TCC_TARGET_X86_64)
#  if defined(TCC_MUSL)
#   define CONFIG_TCC_ELFINTERP "/lib/ld-musl-x86_64.so.1"
#  else
#   define CONFIG_TCC_ELFINTERP "/lib64/ld-linux-x86-64.so.2"
#  endif
# elif !defined(TCC_ARM_EABI)
#  if defined(TCC_MUSL)
#   define CONFIG_TCC_ELFINTERP "/lib/ld-musl-arm.so.1"
#  else
#   define CONFIG_TCC_ELFINTERP "/lib/ld-linux.so.2"
#  endif
# endif
#endif

/* var elf_interp dans *-gen.c */
#ifdef CONFIG_TCC_ELFINTERP
# define DEFAULT_ELFINTERP(s) CONFIG_TCC_ELFINTERP
#else
# define DEFAULT_ELFINTERP(s) default_elfinterp(s)
#endif
```

libtcc

# if defined(TCC_MUSL)
    tcc_define_symbol(s, "__DEFINED_va_list", "");
    tcc_define_symbol(s, "__DEFINED___isoc_va_list", "");
    tcc_define_symbol(s, "__isoc_va_list", "void *");
# endif /* TCC_MUSL */

