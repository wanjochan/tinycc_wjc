# fail...
#../configure --prefix=. --cc=gcc --config-musl --extra-cflags='-Wall -g -O2 -I ../include_qnx' &&

PWD=`pwd`
CCC="mkdir -p build_in_dkr_gcc_musl &&
cd build_in_dkr_gcc_musl &&
../configure --prefix=. --cc=gcc --config-musl --extra-cflags='-Wall -g -O2 -I ../include' &&
make clean &&
make &&
make cross &&
make libtcc.so
./tcc -I.. -I../include -B. -run ../examples/ex3.c 33
"
echo $CCC | docker run -v $PWD:/work/ -w /work/ -i cmptech/docker_tinycc_dev bash
