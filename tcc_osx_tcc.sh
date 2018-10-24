echo KO for tcc in osx failed to compile yet...

mkdir -p build_in_osx_tcc/
cd build_in_osx_tcc
#../configure --prefix=. --cc=../build_in_osx_gcc/tcc --extra-cflags="-Wall -g -O2 -I../include"
#rcs libtcc.a libtcc.o tccpp.o tccgen.o tccelf.o tccasm.o tccrun.o x86_64-gen.o x86_64-link.o i386-asm.o
../configure --prefix=. --cc=tcc --ar='tcc -ar' --config-musl --extra-cflags="-Wall -g -O2 -I../include -D__APPLE__"
make cross
make

