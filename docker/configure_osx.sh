mkdir build_osx
cd build_osx
../configure --config-musl --prefix=. --cc=clang
make

