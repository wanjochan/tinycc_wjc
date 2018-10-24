#

* tcc_dkr_gcc.sh

```
../tcc -c ../../lib/bcheck.c -o bcheck.o -B../..
In file included from ../../lib/bcheck.c:21:
In file included from /usr/include/stdio.h:22:
/usr/include/bits/alltypes.h:6: error: ';' expected (got "va_list")
make[1]: Leaving directory '/work/build_in_dkr_gcc/lib'
make[1]: *** [Makefile:64: bcheck.o] Error 1
make: *** [Makefile:234: libtcc1.a] Error 2
```

* tcc_dkr_gcc_musl.sh => OK but to run it needs some -I -B
* tcc_dkr_gcc_musl_tcc.sh

```
make[1]: Entering directory '/work/build_in_dkr_tcc/lib'
../tcc -c ../../lib/bcheck.c -o bcheck.o -B../..
../../lib/bcheck.c:739: error: '__malloc_hook' undeclared
make[1]: Leaving directory '/work/build_in_dkr_tcc/lib
```
* tcc_dkr_gcc_musl_tcc_musl.sh
```
../build_in_dkr_gcc_musl/tcc -o i386-tcc.o -c ./../tcc.c -DTCC_TARGET_I386 -DTCC_LIBTCC1="\"i386-libtcc1.a\""      -Wall -g -O2 -I. 
In file included from ./../tcc.c:23:
./../libtcc.c:464: error: invalid type
make[1]: *** [Makefile:191: i386-tcc.o] Error 1
make: *** [Makefile:202: i386-tcc] Error 2
```
* tcc_dkr_gcc_tcc.sh
```
./tcc -I.. -I../include -B. -run ../examples/ex3.c 33
```
* tcc_dkr_tcc.sh

```
make[1]: Entering directory '/work/build_in_dkr_tcc/lib'
../tcc -c ../../lib/bcheck.c -o bcheck.o -B../..
In file included from ../../lib/bcheck.c:21:
In file included from /usr/include/stdio.h:22:
/usr/include/bits/alltypes.h:6: error: ';' expected (got "va_list")
make[1]: *** [Makefile:64: bcheck.o] Error 1
make[1]: Leaving directory '/work/build_in_dkr_tcc/lib'
make: *** [Makefile:234: libtcc1.a] Error 2
```

* tcc_dkr_tcc_musl.sh => OK but to run it needs some -I -B

* tcc_osx_clang.sh
* tcc_osx_clang_musl.sh
* tcc_osx_gcc.sh
* tcc_osx_gcc_musl.sh
* tcc_osx_tcc_tcc.sh

```
../build_in_osx_gcc_musl/tcc -o i386-tcc i386-tcc.o -lm -ldl  -flat_namespace
/usr/lib/crt1.o: error: unrecognized file type
tcc: error: file 'crt1.o' not found
tcc: error: file 'crti.o' not found
/usr/lib/libm.dylib: error: bad architecture
tcc: error: library 'm' not found
make[1]: *** [i386-tcc] Error 1
make: *** [i386-tcc] Error 2
../build_in_osx_gcc_musl/tcc -o tcc tcc.o libtcc.a -lm -ldl  -flat_namespace 
/usr/lib/crt1.o: error: unrecognized file type
tcc: error: file 'crt1.o' not found
tcc: error: file 'crti.o' not found
libtcc.a: error: '__sincosf' defined twice
libtcc.a: error: '__sincos' defined twice
libtcc.a: error: '__sincospif' defined twice
libtcc.a: error: '__sincospi' defined twice
libtcc.a: error: '__sincosf' defined twice
libtcc.a: error: '__sincos' defined twice
libtcc.a: error: '__sincospif' defined twice
libtcc.a: error: '__sincospi' defined twice
libtcc.a: error: '__sincosf' defined twice
libtcc.a: error: '__sincos' defined twice
libtcc.a: error: '__sincospif' defined twice
libtcc.a: error: '__sincospi' defined twice
libtcc.a: error: '__sincosf' defined twice
libtcc.a: error: '__sincos' defined twice
libtcc.a: error: '__sincospif' defined twice
libtcc.a: error: '__sincospi' defined twice
libtcc.a: error: '__sincosf' defined twice
libtcc.a: error: '__sincos' defined twice
libtcc.a: error: '__sincospif' defined twice
libtcc.a: error: '__sincospi' defined twice
libtcc.a: error: '__sincosf' defined twice
libtcc.a: error: '__sincos' defined twice
libtcc.a: error: '__sincospif' defined twice
libtcc.a: error: '__sincospi' defined twice
libtcc.a: error: '__sincosf' defined twice
libtcc.a: error: '__sincos' defined twice
libtcc.a: error: '__sincospif' defined twice
libtcc.a: error: '__sincospi' defined twice
libtcc.a: error: '__sincosf' defined twice
libtcc.a: error: '__sincos' defined twice
libtcc.a: error: '__sincospif' defined twice
libtcc.a: error: '__sincospi' defined twice
libtcc.a: error: '__sincosf' defined twice
libtcc.a: error: '__sincos' defined twice
libtcc.a: error: '__sincospif' defined twice
libtcc.a: error: '__sincospi' defined twice
/usr/lib/libm.dylib: error: bad architecture
tcc: error: library 'm' not found
make: *** [tcc] Error 1

```
