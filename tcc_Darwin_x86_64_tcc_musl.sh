echo KO for tcc in osx failed to compile yet...

mkdir -p build_Darwin_x86_64_tcc_musl/
cd build_Darwin_x86_64_tcc_musl

../configure --prefix=. --cc=../build_Darwin_x86_64/tcc --ar="../build_Darwin_x86_64/tcc -ar" --extra-cflags="-B ../build_Darwin_x86_64 -D__APPLE__"

make clean
make
#make cross

echo NOTES: the tcc for osx/mach-o is not finish TODO..

