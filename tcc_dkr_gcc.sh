echo "NOT YET OK (docker alpine is musl)"
echo build with gcc in docker alpine

#../configure --prefix=. --cc=gcc --extra-cflags=\"-Wall -g -O2 -I../include\" &&

PWD=`pwd`
CCC="mkdir -p build_in_dkr_gcc &&
cd build_in_dkr_gcc &&
../configure --prefix=. --cc=gcc --extra-cflags='-Wall -g -O2 -I../include -I. -I.. -Iinclude' &&
make cross &&
make"
echo $CCC | docker run -v $PWD:/work/ -w /work/ -i cmptech/docker_tinycc_dev bash

