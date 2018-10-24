mkdir -p build_in_osx_clang/
cd build_in_osx_clang
../configure --prefix=. --cc=clang
make cross
make
