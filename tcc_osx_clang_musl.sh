mkdir -p build_in_osx_clang_musl/
cd build_in_osx_clang_musl
../configure --prefix=. --cc=clang --config-musl --extra-cflags="-Wall -g -O2 -I ../include"
#make cross
make
