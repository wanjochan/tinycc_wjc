mkdir -p build_in_osx_gcc/
cd build_in_osx_gcc
../configure --prefix=. --cc=gcc
make cross
make

cd ../
./build_in_osx_gcc/tcc -I. -Iinclude -B build_in_osx_gcc/ -run examples/ex3.c 33
