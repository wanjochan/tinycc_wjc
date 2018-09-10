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

chmod +x *.sh

#echo ---------- test examples/ex5
#./tcc_run.sh examples/ex5.c
#
#echo ---------- test examples/ex1
#./tcc_run.sh examples/ex1.c
#
#echo ---------- test examples/ex3
./tcc_run.sh examples/ex3.c 30

