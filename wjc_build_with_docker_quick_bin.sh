rm -Rf build_docker_quick
mkdir build_docker_quick
cd build_docker_quick

#../configure --prefix=. --cc=clang
../configure --config-musl --prefix=. --cc=tcc

make clean
make ONE_SOURCE=yes
#make cross
#make test
make install

cp -R ../examples ./

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

# build a test_c for i386 win32
#./i386-win32-tcc -o ../test_wjc/test_c_w32.exe ../test_wjc/test_c.c

#./i386-win32-tcc -o ../tcc_w32.exe ../tcc.c

