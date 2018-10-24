mkdir -p build_in_osx_gcc_musl/
cd build_in_osx_gcc_musl
../configure --prefix=. --cc=gcc --config-musl
make clean
make
make cross

cd ../
./build_in_osx_gcc_musl/tcc -I. -B build_in_osx_gcc_musl -D __APPLE__ -run examples/ex3.c 33

