/*
 *  TCC - Tiny C Compiler - Support for -run switch
 *
 *  Copyright (c) 2001-2004 Fabrice Bellard
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "tcc.h"

/* only native compiler supports -run */
#ifdef TCC_IS_NATIVE

//TODO redo the backtrace again...
//using debug backtrace trick for the tcc-run
#include "tccrun_debug_bt.c"

static void set_pages_executable(void *ptr, unsigned long length);
static int tcc_relocate_ex(TCCState *s1, void *ptr, addr_t ptr_diff);

#ifdef _WIN64
static void *win64_add_function_table(TCCState *s1);
static void win64_del_function_table(void *);
#endif

/* ------------------------------------------------------------- */
/* Do all relocations (needed before using tcc_get_symbol())
   Returns -1 on error. */
//@ref tcc_run()
LIBTCCAPI int tcc_relocate(TCCState *s1, void *ptr)
{
    int size;
    addr_t ptr_diff = 0;

    if (TCC_RELOCATE_AUTO != ptr)
        return tcc_relocate_ex(s1, ptr, 0);

    size = tcc_relocate_ex(s1, NULL, 0);
    if (size < 0)
        return -1;

#ifdef HAVE_SELINUX
{
    /* Using mmap instead of malloc */
    void *prx;
    char tmpfname[] = "/tmp/.tccrunXXXXXX";
    int fd = mkstemp(tmpfname);
    unlink(tmpfname);
    ftruncate(fd, size);

    ptr = mmap (NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    prx = mmap (NULL, size, PROT_READ|PROT_EXEC, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED || prx == MAP_FAILED)
	tcc_error("tccrun: could not map memory");
    dynarray_add(&s1->runtime_mem, &s1->nb_runtime_mem, (void*)(addr_t)size);
    dynarray_add(&s1->runtime_mem, &s1->nb_runtime_mem, prx);
    ptr_diff = (char*)prx - (char*)ptr;
}
#else
    ptr = tcc_malloc(size);
#endif
    tcc_relocate_ex(s1, ptr, ptr_diff); /* no more errors expected */
    dynarray_add(&s1->runtime_mem, &s1->nb_runtime_mem, ptr);
    return 0;
}

//@ref tcc_delete()
ST_FUNC void tcc_run_free(TCCState *s1)
{
    int i;

    for (i = 0; i < s1->nb_runtime_mem; ++i) {
#ifdef HAVE_SELINUX
        unsigned size = (unsigned)(addr_t)s1->runtime_mem[i++];
        munmap(s1->runtime_mem[i++], size);
        munmap(s1->runtime_mem[i], size);
#else
#ifdef _WIN64
        win64_del_function_table(*(void**)s1->runtime_mem[i]);
#endif
        tcc_free(s1->runtime_mem[i]);
#endif
    }
    tcc_free(s1->runtime_mem);
}

/* launch the compiled program with the given arguments */
//@ref tcc.c::main()
LIBTCCAPI int tcc_run(TCCState *s1, int argc, char **argv)
{
    int (*prog_main)(int, char **);

    s1->runtime_main = "main";
    if ((s1->dflag & 16) && !find_elf_sym(s1->symtab, s1->runtime_main))
        return 0;
    if (tcc_relocate(s1, TCC_RELOCATE_AUTO) < 0)
        return -1;
    prog_main = tcc_get_symbol_err(s1, s1->runtime_main);

#ifdef CONFIG_TCC_BACKTRACE
    if (s1->do_debug) {
        set_exception_handler();
        rt_prog_main = prog_main;
    }
#endif

    //errno = 0; /* clean errno value */
		tcc_errno(0);

#ifdef CONFIG_TCC_BCHECK
    if (s1->do_bounds_check) {
        void (*bound_init)(void);
        void (*bound_exit)(void);
        void (*bound_new_region)(void *p, addr_t size);
        int  (*bound_delete_region)(void *p);
        int i, ret;

        /* set error function */
        rt_bound_error_msg = tcc_get_symbol_err(s1, "__bound_error_msg");
        /* XXX: use .init section so that it also work in binary ? */
        bound_init = tcc_get_symbol_err(s1, "__bound_init");
        bound_exit = tcc_get_symbol_err(s1, "__bound_exit");
        bound_new_region = tcc_get_symbol_err(s1, "__bound_new_region");
        bound_delete_region = tcc_get_symbol_err(s1, "__bound_delete_region");

        bound_init();
        /* mark argv area as valid */
        bound_new_region(argv, argc*sizeof(argv[0]));
        for (i=0; i<argc; ++i)
            bound_new_region(argv[i], TCC(strlen,int)(argv[i]) + 1);

        ret = (*prog_main)(argc, argv);

        /* unmark argv area */
        for (i=0; i<argc; ++i)
            bound_delete_region(argv[i]);
        bound_delete_region(argv);
        bound_exit();
        return ret;
    }
#endif
    return (*prog_main)(argc, argv);
}

#if defined TCC_TARGET_I386 || defined TCC_TARGET_X86_64
/* To avoid that x86 processors would reload cached instructions
   each time when data is written in the near, we need to make
   sure that code and data do not share the same 64 byte unit */
 #define RUN_SECTION_ALIGNMENT 63
#else
 #define RUN_SECTION_ALIGNMENT 0
#endif

/* relocate code. Return -1 on error, required size if ptr is NULL,
   otherwise copy code into buffer passed by the caller */
//@ref tcc_relocate()
static int tcc_relocate_ex(TCCState *s1, void *ptr, addr_t ptr_diff)
{
	Section *s;
	unsigned offset, length, align, max_align, i, k, f;
	addr_t mem, addr;

	if (NULL == ptr) {
		s1->nb_errors = 0;
#ifdef TCC_TARGET_PE
		pe_output_file(s1, NULL);
#else
		tcc_add_runtime(s1);
		resolve_common_syms(s1);
		build_got_entries(s1);
#endif
		if (s1->nb_errors)
			return -1;
	}

	offset = max_align = 0, mem = (addr_t)ptr;
#ifdef _WIN64
	offset += sizeof (void*); /* space for function_table pointer */
#endif
	for (k = 0; k < 2; ++k) {
		f = 0, addr = k ? mem : mem + ptr_diff;
		for(i = 1; i < s1->nb_sections; i++) {
			s = s1->sections[i];
			if (0 == (s->sh_flags & SHF_ALLOC))
				continue;
			if (k != !(s->sh_flags & SHF_EXECINSTR))
				continue;
			align = s->sh_addralign - 1;
			if (++f == 1 && align < RUN_SECTION_ALIGNMENT)
				align = RUN_SECTION_ALIGNMENT;
			if (max_align < align)
				max_align = align;
			offset += -(addr + offset) & align;
			s->sh_addr = mem ? addr + offset : 0;
			offset += s->data_offset;
#if 0
			if (mem)
				printf("%-16s %p  len %04x  align %2d\n",
						s->name, (void*)s->sh_addr, (unsigned)s->data_offset, align + 1);
#endif
		}
	}

	/* relocate symbols */
	relocate_syms(s1, s1->symtab, 1);
	if (s1->nb_errors)
		return -1;

	if (0 == mem)
		return offset + max_align;

#ifdef TCC_TARGET_PE
	s1->pe_imagebase = mem;
#endif

	/* relocate each section */
	for(i = 1; i < s1->nb_sections; i++) {
		s = s1->sections[i];
		if (s->reloc)
			relocate_section(s1, s);
	}
	relocate_plt(s1);

	for(i = 1; i < s1->nb_sections; i++) {
		s = s1->sections[i];
		if (0 == (s->sh_flags & SHF_ALLOC))
			continue;
		length = s->data_offset;
		ptr = (void*)s->sh_addr;
		if (s->sh_flags & SHF_EXECINSTR)
			ptr = (char*)ptr - ptr_diff;
		if (NULL == s->data || s->sh_type == SHT_NOBITS)
			TCC(memset)(ptr, 0, length);
		else
			TCC(memcpy)(ptr, s->data, length);
		/* mark executable sections as executable in memory */
		if (s->sh_flags & SHF_EXECINSTR)
			set_pages_executable((char*)ptr + ptr_diff, length);
	}

#ifdef _WIN64
	*(void**)mem = win64_add_function_table(s1);
#endif

	return 0;
}

/* ------------------------------------------------------------- */
/* allow to run code in memory */

static void set_pages_executable(void *ptr, unsigned long length)
{
#ifdef _WIN32
    unsigned long old_protect;
    TCC(VirtualProtect)(ptr, length, 0x40//PAGE_EXECUTE_READWRITE
				, &old_protect);
#else
    void __clear_cache(void *beginning, void *end);
# ifndef HAVE_SELINUX
    addr_t start, end;
#  ifndef PAGESIZE
#   define PAGESIZE 4096
#  endif
    start = (addr_t)ptr & ~(PAGESIZE - 1);
    end = (addr_t)ptr + length;
    end = (end + PAGESIZE - 1) & ~(PAGESIZE - 1);
    if (TCC(mprotect,int)((void *)start, end - start, PROT_READ | PROT_WRITE | PROT_EXEC))
        tcc_error("mprotect failed: did you mean to configure --with-selinux?");
# endif
# if defined TCC_TARGET_ARM || defined TCC_TARGET_ARM64
    __clear_cache(ptr, (char *)ptr + length);
# endif
#endif
}

#ifdef _WIN64
static void *win64_add_function_table(TCCState *s1)
{
    void *p = NULL;
    if (s1->uw_pdata) {
        p = (void*)s1->uw_pdata->sh_addr;
        RtlAddFunctionTable(
            (RUNTIME_FUNCTION*)p,
            s1->uw_pdata->data_offset / sizeof (RUNTIME_FUNCTION),
            s1->pe_imagebase
            );
        s1->uw_pdata = NULL;
    }
    return p;
}

static void win64_del_function_table(void *p)
{
    if (p) {
        RtlDeleteFunctionTable((RUNTIME_FUNCTION*)p);
    }
}
#endif

/* ------------------------------------------------------------- */
#ifdef CONFIG_TCC_STATIC

/* dummy function for profiling */
ST_FUNC void *dlopen(const char *filename, int flag)
{
    return NULL;
}

ST_FUNC void dlclose(void *p)
{
}

ST_FUNC const char *dlerror(void)
{
    return "error";
}

typedef struct TCCSyms {
    char *str;
    void *ptr;
} TCCSyms;


/* add the symbol you want here if no dynamic linking is done */
static TCCSyms tcc_syms[] = {
#if !defined(CONFIG_TCCBOOT)
#define TCCSYM(a) { #a, &a, },
    TCCSYM(printf)
    TCCSYM(fprintf)
    TCCSYM(fopen)
    TCCSYM(fclose)
#undef TCCSYM
#endif
    { NULL, NULL },
};

//TODO improve later.
ST_FUNC void *dlsym(void *handle, const char *symbol)
{
    TCCSyms *p;
    p = tcc_syms;
    while (p->str != NULL) {
        if (!strcmp(p->str, symbol))
            return p->ptr;
        p++;
    }
    return NULL;
}

#endif /* CONFIG_TCC_STATIC */
#endif /* TCC_IS_NATIVE */
/* ------------------------------------------------------------- */
