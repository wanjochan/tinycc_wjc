/*
 *  TCC - Tiny C Compiler
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

//TARGET: tcc_core_run as a replacement to "tcc -run"
//TARGET: tcc_core as a replacement to "tcc" so that it can compile itself and no Makefiles needed...

#include "tcc.h"

//NOTES: for ONE_SOURCE, the libtcc is built insie so that no need to gen the external libtcc1.a
#if ONE_SOURCE
# include "libtcc.c"
#endif

static const char help[] =
"Tiny C Compiler "TCC_VERSION" - Copyright (C) 2001-2006 Fabrice Bellard\n"
"Usage: $TCC_CORE_RUN [options...] in_file [arguments...]\n"
"General options:\n"
"  -fflag      set or reset (with 'no-' prefix) 'flag' (see -hh)\n"
"  -Wwarning   set or reset (with 'no-' prefix) 'warning' (see -hh)\n"
"  -w          disable all warnings\n"
"  -v -vv      show version, show search paths or loaded files\n"
"  -h -hh      show this, show more help\n"
"  -bench      show compilation statistics\n"
"  -           use stdin pipe as infile\n"
"  @listfile   read arguments from listfile\n"
"Preprocessor options:\n"
"  -Idir       add include path 'dir'\n"
"  -Dsym[=val] define 'sym' with value 'val'\n"
"  -Usym       undefine 'sym'\n"
"  -E          preprocess only\n"
"Linker options:\n"
"  -Ldir       add library path 'dir'\n"
"  -llib       link with dynamic or static library 'lib'\n"
"  -r          generate (relocatable) object file\n"
"  -shared     generate a shared library/dll\n"
"  -rdynamic   export all global symbols to dynamic linker\n"
"  -soname     set name for shared library to be used at runtime\n"
"  -Wl,-opt[=val]  set linker option (see -hh)\n"
"Debugger options:\n"
"  -g          generate runtime debug info\n"
#ifdef CONFIG_TCC_BCHECK
"  -b          compile with built-in memory and bounds checker (implies -g)\n"
#endif
#ifdef CONFIG_TCC_BACKTRACE
"  -bt N       show N callers in stack traces\n"
#endif
"Misc. options:\n"
"  -x[c|a|b|n] specify type of the next infile (C,ASM,BIN,NONE)\n"
"  -nostdinc   do not use standard system include paths\n"
"  -nostdlib   do not link with standard crt and libraries\n"
"  -Bdir       set private include/library dir\n"
"  -MD         generate dependency file for make\n"
"  -MF file    specify dependency file name\n"
;

static const char help2[] =
"Tiny C Compiler "TCC_VERSION" - More Options\n"
"Special options:\n"
"  -P -P1                        with -E: no/alternative #line output\n"
"  -dD -dM                       with -E: output #define directives\n"
"  -pthread                      same as -D_REENTRANT and -lpthread\n"
"  -On                           same as -D__OPTIMIZE__ for n > 0\n"
"  -Wp,-opt                      same as -opt\n"
"  -include file                 include 'file' above each input file\n"
"  -isystem dir                  add 'dir' to system include path\n"
"  -static                       link to static libraries (not recommended)\n"
"  -dumpversion                  print version\n"
"  -print-search-dirs            print search paths\n"
"  -dt                           with -run/-E: auto-define 'test_...' macros\n"
"Ignored options:\n"
"  --param  -pedantic  -pipe  -s  -std  -traditional\n"
"-W... warnings:\n"
"  all                           turn on some (*) warnings\n"
"  error                         stop after first warning\n"
"  unsupported                   warn about ignored options, pragmas, etc.\n"
"  write-strings                 strings are const\n"
"  implicit-function-declaration warn for missing prototype (*)\n"
"-f[no-]... flags:\n"
"  unsigned-char                 default char is unsigned\n"
"  signed-char                   default char is signed\n"
"  common                        use common section instead of bss\n"
"  leading-underscore            decorate extern symbols\n"
"  ms-extensions                 allow anonymous struct in struct\n"
"  dollars-in-identifiers        allow '$' in C symbols\n"
"-m... target specific options:\n"
"  ms-bitfields                  use MSVC bitfield layout\n"
#ifdef TCC_TARGET_ARM
"  float-abi                     hard/softfp on arm\n"
#endif
#ifdef TCC_TARGET_X86_64
"  no-sse                        disable floats on x86_64\n"
#endif
"-Wl,... linker options:\n"
"  -nostdlib                     do not link with standard crt/libs\n"
"  -[no-]whole-archive           load lib(s) fully/only as needed\n"
"  -export-all-symbols           same as -rdynamic\n"
"  -export-dynamic               same as -rdynamic\n"
"  -image-base= -Ttext=          set base address of executable\n"
"  -section-alignment=           set section alignment in executable\n"

#ifdef TCC_TARGET_PE
"  -file-alignment=              set PE file alignment\n"
"  -stack=                       set PE stack reserve\n"
"  -large-address-aware          set related PE option\n"
"  -subsystem=[console/windows]  set PE subsystem\n"
#else
"  -rpath=                       set dynamic library search path\n"
"  -enable-new-dtags             set DT_RUNPATH instead of DT_RPATH\n"
"  -soname=                      set DT_SONAME elf tag\n"
"  -Bsymbolic                    set DT_SYMBOLIC elf tag\n"
"  -init= -fini= -as-needed -O   (ignored)\n"
#endif

"See also the manual for more details.\n"
;

//ARCH
static const char version[] =
"tcc version "TCC_VERSION" ("
#ifdef TCC_TARGET_I386
"i386"
#elif defined TCC_TARGET_X86_64
"x86_64"
#elif defined TCC_TARGET_C67
"C67"
#elif defined TCC_TARGET_ARM
"ARM"
#elif defined TCC_TARGET_ARM64
"AArch64"
#endif
#ifdef TCC_ARM_HARDFLOAT
" Hard Float"
#endif
#ifdef TCC_TARGET_PE
" Windows"
#elif defined(TCC_TARGET_MACHO)
" Darwin"
#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
" FreeBSD"
#else
" Linux"
#endif
")\n"
;

static void print_dirs(const char *msg, char **paths, int nb_paths)
{
	int i;
	printf("%s:\n%s", msg, nb_paths ? "" : "  -\n");
	for(i = 0; i < nb_paths; i++)
		printf("  %s\n", paths[i]);
}

static void print_search_dirs(TCCState *s)
{
	printf("install: %s\n", s->tcc_lib_path);
	/* print_dirs("programs", NULL, 0); */
	print_dirs("include", s->sysinclude_paths, s->nb_sysinclude_paths);
	print_dirs("libraries", s->library_paths, s->nb_library_paths);
#ifdef TCC_TARGET_PE
	printf("libtcc1:\n  %s/lib/"TCC_LIBTCC1"\n", s->tcc_lib_path);
#else
	printf("libtcc1:\n  %s/"TCC_LIBTCC1"\n", s->tcc_lib_path);
	print_dirs("crt", s->crt_paths, s->nb_crt_paths);
	printf("elfinterp:\n  %s\n",  DEFAULT_ELFINTERP(s));
#endif
}

static void set_environment(TCCState *s)
{
	char * path;

	path = getenv("C_INCLUDE_PATH");
	if(path != NULL) {
		tcc_add_sysinclude_path(s, path);
	}
	path = getenv("CPATH");
	if(path != NULL) {
		tcc_add_include_path(s, path);
	}
	path = getenv("LIBRARY_PATH");
	if(path != NULL) {
		tcc_add_library_path(s, path);
	}
}

static unsigned getclock_ms(void)
{
#ifdef _WIN32
	return GetTickCount();
#else
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec*1000 + (tv.tv_usec+500)/1000;
#endif
}

int main(int argc0, char **argv0)
{
	TCCState *s;
	int ret, opt, n = 0, t = 0;
	unsigned start_time = 0;
	const char *first_file;
	int argc; char **argv;
	FILE *ppfp = stdout;

redo:
	argc = argc0, argv = argv0;
	s = tcc_new();
	opt = tcc_parse_args(s, &argc, &argv, 1);

	if ((n | t) == 0) {
		if (opt == OPT_HELP)
			return printf(help), 1;
		if (opt == OPT_HELP2)
			return printf(help2), 1;

		if (s->verbose)
			printf(version);
#ifdef TCC_TARGET_PE
		if (opt == OPT_IMPDEF)
			return tcc_tool_impdef(s, argc, argv);
#endif
		if (opt == OPT_V)
			return 0;
		if (opt == OPT_PRINT_DIRS) {
			/* initialize search dirs */
			set_environment(s);
			tcc_set_output_type(s, TCC_OUTPUT_MEMORY);
			print_search_dirs(s);
			return 0;
		}

		n = s->nb_files;
		if (n == 0)
			tcc_error("no input files\n");

		if (s->output_type == TCC_OUTPUT_PREPROCESS) {
			if (s->outfile) {
				ppfp = fopen(s->outfile, "w");
				if (!ppfp)
					tcc_error("could not write '%s'", s->outfile);
			}
		} else if (s->output_type == TCC_OUTPUT_OBJ && !s->option_r) {
			if (s->nb_libraries)
				tcc_error("cannot specify libraries with -c");
			if (n > 1 && s->outfile)
				tcc_error("cannot specify output file with -c many files");
		} else {
			if (s->option_pthread) {
				tcc_set_options(s, "-lpthread");
				n = s->nb_files;
			}
		}

		if (s->do_bench)
			start_time = getclock_ms();
	}

	set_environment(s);
	if (s->output_type == 0)
		s->output_type = TCC_OUTPUT_EXE;
	tcc_set_output_type(s, s->output_type);

	s->ppfp = ppfp;

	//TODO add notes to explain dflag
	s->dflag |= t ? 32 : 0, s->run_test = ++t, n = s->nb_files;

	/* compile or add each files or library */
	for (first_file = NULL, ret = 0;;) {
		struct filespec *f = s->files[s->nb_files - n];
		s->filetype = f->type;
		if (f->type & AFF_TYPE_LIB) {
			if (tcc_add_library_err(s, f->name) < 0)
				ret = 1;
		} else {
			if (1 == s->verbose)
				printf("-> %s\n", f->name);
			if (!first_file)
				first_file = f->name;
			if (tcc_add_file(s, f->name) < 0)
				ret = 1;
		}
		if (--n == 0 || ret
				|| (s->output_type == TCC_OUTPUT_OBJ && !s->option_r))
			break;
	}

	if (s->run_test) {
		t = 0;
	} else if (s->output_type == TCC_OUTPUT_PREPROCESS) {
		;
	} else if (0 == ret) {
		ret = tcc_run(s, argc, argv);
	}

	if (s->do_bench && (n | t | ret) == 0)
		tcc_print_stats(s, getclock_ms() - start_time);
	tcc_delete(s);
	if (ret == 0 && n)
		goto redo; /* compile more files with -c */
	if (t)
		goto redo; /* run more tests with -dt -run */
	if (ppfp && ppfp != stdout)
		fclose(ppfp);
	return ret;
}