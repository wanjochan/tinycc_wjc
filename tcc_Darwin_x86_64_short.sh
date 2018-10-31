# TODO -Wno-unused-result

#../configure --prefix=. --cc=clang --config-musl --extra-cflags="-Wall -g -O2 -I ../include"

arch=$(uname -s)_$(uname -m)
echo arch=$arch
mkdir -p build_$arch/
cd build_$arch/
../configure --prefix=. --cc=clang --config-musl
make clean
make libtcc.so
make 

ls -al

echo test1
./tcc -vv

cd ..

echo ./build_Darwin_x86_64/tcc -run -B build_Darwin_x86_64/ -I build_Darwin_x86_64/ -I include -I. -D __APPLE__ examples/eg_tcc_dl.c 30
./build_Darwin_x86_64/tcc -run -B build_Darwin_x86_64/ -I build_Darwin_x86_64/ -I include -I. -D __APPLE__ examples/eg_tcc_dl.c 30

#echo ./build_Darwin_x86_64/tcc -run -B build_Darwin_x86_64/ -I include -I. -D __APPLE__ tcc.c -v
#./build_Darwin_x86_64/tcc -run -B build_Darwin_x86_64/ -I include -I. -D __APPLE__ tcc.c -v

echo ./build_Darwin_x86_64/tcc -run -B build_Darwin_x86_64/ -I. tcc.c -vv
./build_Darwin_x86_64/tcc -run -B build_Darwin_x86_64/ -I. tcc.c -vv

#echo ./build_Darwin_x86_64/tcc -run -B build_Darwin_x86_64/ -I. examples/test_tcc_error_internal.c
#./build_Darwin_x86_64/tcc -run -B build_Darwin_x86_64/ -I. examples/test_tcc_error_internal.c

echo ./build_Darwin_x86_64/tcc -run -B build_Darwin_x86_64/ -I. examples/test_tcc_h.c
./build_Darwin_x86_64/tcc -run -B build_Darwin_x86_64/ -I. examples/test_tcc_h.c

echo

#./build_Darwin_x86_64/tcc -B build_Darwin_x86_64/ -I. -E -P0 tcc.c > tcc.osx.pp.c
echo ./build_Darwin_x86_64/tcc -B build_Darwin_x86_64/ -I. -E -P0 -D__APPLE__ -DTCC_TARGET_MACHO tcc.c \> tcc.osx.pp.c
./build_Darwin_x86_64/tcc -B build_Darwin_x86_64/ -I. -E -P0 -D__APPLE__ -DTCC_TARGET_MACHO tcc.c > tcc.osx.pp.c

# testing loop self...
echo gcc tcc.osx.pp.c
echo ./a.out -run tcc.osx.pp.c -run tcc.osx.pp.c -vv

echo ./build_Darwin_x86_64/tcc tcc.osx.pp.c  
./build_Darwin_x86_64/tcc tcc.osx.pp.c

#tcc: error: undefined symbol 'memmove'
#tcc: error: undefined symbol '__floatundixf'
#tcc: error: undefined symbol '__fixunsxfdi'
#tcc: error: undefined symbol 'dlclose'
#tcc: error: undefined symbol 'memset'
#tcc: error: undefined symbol 'dlsym'
#tcc: error: undefined symbol 'dlopen'
#tcc: error: undefined symbol '__stdinp'
#tcc: error: undefined symbol '__stdoutp'
#tcc: error: undefined symbol '__stderrp'
#tcc: error: undefined symbol '__error'

# TODO failed, coz link/gen for OSX is not yet finish
#echo tcc tcc.os.pp.c

#./build_Darwin_x86_64/tcc -B build_Darwin_x86_64/ -I. -E -P0 tcc.c > tcc.osx.pp.c

#error: file './libtcc1.a' not found
#./build_Darwin_x86_64/tcc -run -I include -I. -D __APPLE__ tcc.c -v

#ls -al build_Darwin_x86_64

#TODO :failed without __APPLE__, which should be auto handle by headers or...????
#echo test3
#./build_Darwin_x86_64/tcc -run -B build_Darwin_x86_64/lib/tcc/  -I include -I.  examples/eg_tcc_dl.c 30

#notes: if wrong B and I, will seg fault without error shown, later fix the SIGSTOP catch....

