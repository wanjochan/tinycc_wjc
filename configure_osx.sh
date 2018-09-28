mkdir build_osx
cd build_osx
../configure --config-musl --prefix=. --cc=clang
make

#/usr/local/Cellar/gcc/8.2.0/bin/gcc-8 -o libtcc.osx.brew.gcc8 -I. -DTCC_LIB_DLL -shared -c libtcc.c
#clang -o libtcc.osx.clang -I. -DTCC_LIB_DLL -c libtcc.c 
#/usr/local/Cellar/gcc/8.2.0/bin/gcc-8 -o libtcc.osx.brew.gcc8 -DTCC_LIB_DLL -shared -rdynamic -c ../libtcc.c
#/usr/local/Cellar/gcc/8.2.0/bin/gcc-8 -o libtest.so -DTCC_LIB_DLL -shared -rdynamic -c ../tcc.c
#/usr/local/Cellar/gcc/8.2.0/bin/gcc-8 -shared -Wl,-soname,tcc.so -otcc.so -DTCC_LIB_DLL -shared -rdynamic -c ../tcc.c
