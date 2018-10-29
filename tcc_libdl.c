/*
gcc -o examples/tcc_libdl.o -c tcc_libdl.c -DTCC_TARGET_X86_64 -DTCC_TARGET_MACHO -DTCC_MUSL -DONE_SOURCE=0 -Wall -g -O2 -Wdeclaration-after-statement -fno-strict-aliasing -Wno-pointer-sign -Wno-sign-compare -Wno-unused-result -Wno-unused-function -D_FORTIFY_SOURCE=0 -I.-fPIC
gcc -shared -Wl,-install_name,tcc_libdl.so -o examples/tcc_libdl.so examples/tcc_libdl.o -flat_namespace -fPIC
gcc -shared -export-symbols -Wl,-install_name,tcc_libdl.so -o examples/tcc_libdl.so examples/tcc_libdl.o -flat_namespace -fPIC
#gcc -static -o tcc_libdl.a examples/tcc_libdl.o -flat_namespace -fPIC

gcc -I. examples/test_gcc_libdl.c examples/tcc_libdl.so -o test_gcc_libdl
./test_gcc_libdl 
dyld: Library not loaded: tcc_libdl.so
  Referenced from: /Users/wanjochan/Downloads/github/tinycc_wjc/./test_gcc_libdl
  Reason: image not found
Abort trap: 6

clang -o examples/tcc_libdl.o -c tcc_libdl.c -DTCC_TARGET_X86_64 -DTCC_TARGET_MACHO -DTCC_MUSL -DONE_SOURCE=0 -Wall -g -O2 -Wdeclaration-after-statement -fno-strict-aliasing -fheinous-gnu-extensions -Wno-pointer-sign -Wno-sign-compare -Wno-unused-result -Wno-unused-function -Wno-string-plus-int -I.  -fPIC
clang -shared -Wl,-install_name,tcc_libdl.so -o examples/tcc_libdl.so examples/tcc_libdl.o -flat_namespace -fPIC
#clang -static -o tcc_libdl.a examples/tcc_libdl.o -flat_namespace -fPIC

ar rcs examples/tcc_libdl.a examples/tcc_libdl.o

#
gcc -I. examples/test_gcc_libdl.c examples/tcc_libdl.a
./a.out
clang -I. examples/test_gcc_libdl.c examples/tcc_libdl.a

gcc -I. examples/test_gcc_libdl.c examples/tcc_libdl.a
DYLD_LIBRARY_PATH=examples ./test_gcc_libdl

# WORK: OSX/tcc
DYLD_INSERT_LIBRARIES=examples/tcc_libdl.so ./build_Darwin_x86_64/tcc -run -B build_Darwin_x86_64 -I. examples/test_gcc_libdl.c

#
tcc -run  -B build_Darwin_x86_64 -I. examples/test_gcc_libdl.c examples/tcc_libdl.a 
./build_Darwin_x86_64/tcc -run -B build_Darwin_x86_64 -I. examples/test_gcc_libdl.c examples/tcc_libdl.so
error: tccelf: undefined symbol 'tcc_libdl_open'

*/

//#include <dlfcn.h>
#include "tcc_dl.h"
//#include "tcc_libdl.h"

void * tcc_libdl_open(const char* lib)
{
	return dlopen(lib, RTLD_GLOBAL | RTLD_LAZY);
}

