echo "KO because in docker alpine need musl?"
echo build with tcc in docker alpine

PWD=`pwd`
CCC="mkdir -p build_in_dkr_tcc &&
cd build_in_dkr_tcc &&
../configure --prefix=. --cc=../build_in_dkr_gcc_musl/tcc --extra-cflags='-Wall -g -O2 -I../include -B ../build_in_dkr_gcc_musl/' &&
make &&
./tcc -I.. -I../include -B. -run ../examples/ex3.c 33
"
echo PWD=$PWD,CCC=$CCC
echo docker run -v $PWD/:/work/ -w /work/ -i cmptech/docker_tinycc_dev bash
echo $CCC | docker run -v $PWD:/work/ -w /work/ -i cmptech/docker_tinycc_dev bash

