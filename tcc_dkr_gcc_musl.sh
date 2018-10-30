# fail...
#../configure --prefix=. --cc=gcc --config-musl --extra-cflags='-Wall -g -O2 -I ../include_qnx' &&

#make clean &&

PWD=`pwd`
CCC="mkdir -p build_in_dkr_gcc_musl &&
cd build_in_dkr_gcc_musl &&
../configure --prefix=. --cc=gcc --config-musl --extra-cflags='-Wall -g -O2 -I ../include' &&
make clean &&
make &&
make cross &&
echo test1 &&
./tcc -I.. -B. -run ../examples/ex3.c 33
"
#echo $CCC | docker run -v $PWD:/work/ -w /work/ -i cmptech/docker_tinycc_dev bash
DDD="docker run -v $PWD/:/work/ -w /work/ -i cmptech/docker_tinycc_dev"
echo PWD=$PWD
echo CCC=$CCC
echo DDD=$DDD

echo $CCC | $DDD bash

echo $DDD ./build_in_dkr_gcc_musl/tcc -I. -B ./build_in_dkr_gcc_musl -run ./examples/ex3.c 33
$DDD ./build_in_dkr_gcc_musl/tcc -I. -B ./build_in_dkr_gcc_musl -run ./examples/ex3.c 33

# TODO
echo $DDD ./build_in_dkr_gcc_musl/i386-win32-tcc -I. -B build_in_dkr_gcc_musl -o ex3.exe examples/ex3.c
$DDD ./build_in_dkr_gcc_musl/X86-32-WIN-tcc -I. -B build_in_dkr_gcc_musl -o ex3.exe examples/ex3.c


#make libtcc.so
#gcc -shared -Wl,-soname,libtcc.so -o libtcc.so libtcc.o tccpp.o tccgen.o tccelf.o tccasm.o tccrun.o x86_64-gen.o x86_64-link.o i386-asm.o -fPIC
#/usr/lib/gcc/x86_64-alpine-linux-musl/6.4.0/../../../../x86_64-alpine-linux-musl/bin/ld: libtcc.o: relocation R_X86_64_PC32 against symbol `define_stack' can not be used when making a shared object; recompile with -fPIC
#/usr/lib/gcc/x86_64-alpine-linux-musl/6.4.0/../../../../x86_64-alpine-linux-musl/bin/ld: final link failed: Bad value
