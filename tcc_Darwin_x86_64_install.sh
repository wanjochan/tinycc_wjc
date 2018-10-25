# TODO -Wno-unused-result

#../configure --prefix=. --cc=clang --config-musl --extra-cflags="-Wall -g -O2 -I ../include"

arch=$(uname -s)_$(uname -m)
build_arch=build_${arch}_install/
echo arch=$arch
mkdir -p $build_arch/
cd $build_arch/
../configure --cc=clang --config-musl
make clean
make
make cross
make libtcc.so
make install

ls -al

echo test1
./tcc -vv

cd ..

echo test2
tcc -run -B $build_arch -I. examples/eg_tcc_dl.c 30

echo test3
tcc -run -B $build_arch tcc.c -vv
i386-win32-tcc -B $build_arch -o $build_arch/tcc-win32.exe -c tcc.c

#error: file './libtcc1.a' not found
#./build_Darwin_x86_64/tcc -run -I include -I. -D __APPLE__ tcc.c -v

#ls -al build_Darwin_x86_64

#TODO :failed without __APPLE__, which should be auto handle by headers or...????
#echo test3
#./build_Darwin_x86_64/tcc -run -B build_Darwin_x86_64/lib/tcc/  -I include -I.  examples/eg_tcc_dl.c 30

#notes: if wrong B and I, will seg fault without error shown, later fix the SIGSTOP catch....

