echo build with tcc in docker alpine

PWD=`pwd`
CCC="mkdir -p build_in_dkr_tcc_musl &&
cd build_in_dkr_tcc_musl &&
../configure --prefix=. --cc=tcc --ar='tcc -ar' --config-musl &&
make clean && make &&
./tcc -I.. -I../include -B. -run ../examples/ex3.c 33
"
echo PWD=$PWD,CCC=$CCC
echo docker run -v $PWD/:/work/ -w /work/ -i cmptech/docker_tinycc_dev bash
echo $CCC | docker run -v $PWD:/work/ -w /work/ -i cmptech/docker_tinycc_dev bash

