#NOTES: run me in docker(cmptech/tinycc_dev)

rm -Rf build_docker
mkdir build_docker
cd build_docker

#../configure --prefix=. --cc=clang
../configure --config-musl --prefix=. --cc=tcc

make clean
make ONE_SOURCE=yes
make cross
#make test
make install

cp -R ../examples ./

# TODO test with dtcc then

# TODO ren later
#cp ../wjc_tcc_tcc_osx_test.sh ./tcctcc.sh
#cp ../wjc_tcc_run_in.sh ./tcc_run.sh
cp ../wjc_tcc_run_in_docker.sh ./tcc_run.sh

#chmod +x *.sh
#
#echo ---------- test examples/ex5
#./tcc_run.sh examples/ex5.c
#
#echo ---------- test examples/ex1
#./tcc_run.sh examples/ex1.c
#
#echo ---------- test examples/ex3
./tcc_run.sh examples/ex3.c 30
#
#echo ----------- test tcctcc.sh -vv
#./tcctcc.sh -vv


./i386-win32-tcc -o tcc_i386-win32.exe ../tcc.c

./i386-win32-tcc -o ../test_wjc/test_c_w32.exe ../test_wjc/test_c.c


