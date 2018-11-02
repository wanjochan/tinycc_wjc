#./../libtcc.c:464: error: invalid type

#../configure --prefix=. --cc=../build_in_dkr_gcc_musl/tcc --ar='../build_in_dkr_gcc_musl/tcc -ar' --config-musl &&

PWD=`pwd`

CCC=`cat <<CCCXXX
mkdir -p build_in_dkr_gcc_musl_tcc_musl &&
cd build_in_dkr_gcc_musl_tcc_musl &&
../configure --prefix=. --cc='../build_in_dkr_gcc_musl/tcc -B ../build_in_dkr_gcc_musl/' --ar='../build_in_dkr_gcc_musl/tcc -ar' --config-musl --extra-cflags='-Wall -g -O2 -I../include' &&
make clean && 
make ONE_SOURCE=yes && 
make ONE_SOURCE=no && 
make cross &&
cd .. &&
echo test1 &&
./build_in_dkr_gcc_musl/tcc -I. -B ./build_in_dkr_gcc_musl -run ./examples/ex3.c 33 &&
echo test2 &&
./build_in_dkr_gcc_musl_tcc_musl/tcc -I. -B ./build_in_dkr_gcc_musl_tcc_musl -run ./examples/ex3.c 33
CCCXXX
`
DDD="docker run -v $PWD/:/work/ -w /work/ -i cmptech/docker_tinycc_dev"
echo PWD=$PWD
echo CCC=$CCC
echo DDD=$DDD
#echo $CCC | docker run -v $PWD:/work/ -w /work/ -i cmptech/docker_tinycc_dev bash
echo $CCC | $DDD bash

echo test3
$DDD ./build_in_dkr_gcc_musl_tcc_musl/tcc -I. -B ./build_in_dkr_gcc_musl_tcc_musl -run ./examples/ex3.c 33

# TODO seg fault need to be solve....
echo test4
$DDD ./build_in_dkr_gcc_musl_tcc_musl/i386-win32-tcc -I. -B ./build_in_dkr_gcc_musl_tcc_musl -o ex3.exe examples/ex3.c


