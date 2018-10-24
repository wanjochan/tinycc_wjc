#./../libtcc.c:464: error: invalid type

#../configure --prefix=. --cc=../build_in_dkr_gcc_musl/tcc --ar='../build_in_dkr_gcc_musl/tcc -ar' --config-musl &&

PWD=`pwd`
CCC="mkdir -p build_in_dkr_gcc_musl_tcc_musl &&
cd build_in_dkr_gcc_musl_tcc_musl &&
../configure --prefix=. --cc='../build_in_dkr_gcc_musl/tcc -B ../build_in_dkr_gcc_musl/' --ar='../build_in_dkr_gcc_musl/tcc -ar' --config-musl --extra-cflags='-Wall -g -O2 -I../include' &&
make clean && make && make cross &&
cd .. &&
./build_in_dkr_gcc_musl/tcc -I. -B ./build_in_dkr_gcc_musl -run ./examples/ex3.c 33 &&
./build_in_dkr_gcc_musl_tcc_musl/tcc -I. -B ./build_in_dkr_gcc_musl_tcc_musl -run ./examples/ex3.c 33
"
DDD="docker run -v $PWD/:/work/ -w /work/ -i cmptech/docker_tinycc_dev"
echo PWD=$PWD
echo CCC=$CCC
echo DDD=$DDD
#echo $CCC | docker run -v $PWD:/work/ -w /work/ -i cmptech/docker_tinycc_dev bash
echo $CCC | $DDD bash

$DDD ./build_in_dkr_gcc_musl_tcc_musl/tcc -I. -B ./build_in_dkr_gcc_musl_tcc_musl -run ./examples/ex3.c 33

