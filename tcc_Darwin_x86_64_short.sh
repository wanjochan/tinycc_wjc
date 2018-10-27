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

echo ./build_Darwin_x86_64/tcc -run -B build_Darwin_x86_64/ -I include -I. -D __APPLE__ tcc.c -v
./build_Darwin_x86_64/tcc -run -B build_Darwin_x86_64/ -I include -I. -D __APPLE__ tcc.c -v

#error: file './libtcc1.a' not found
#./build_Darwin_x86_64/tcc -run -I include -I. -D __APPLE__ tcc.c -v

#ls -al build_Darwin_x86_64

#TODO :failed without __APPLE__, which should be auto handle by headers or...????
#echo test3
#./build_Darwin_x86_64/tcc -run -B build_Darwin_x86_64/lib/tcc/  -I include -I.  examples/eg_tcc_dl.c 30

#notes: if wrong B and I, will seg fault without error shown, later fix the SIGSTOP catch....

