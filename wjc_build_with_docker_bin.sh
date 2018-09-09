#NOTES: run me in docker(cmptech/tinycc_dev)

rm -Rf build_docker
mkdir build_docker
cd build_docker

#../configure --prefix=. --cc=clang
../configure --config-musl --prefix=. ONE_SOURCE=yes --cc=tcc

make clean
make ONE_SOURCE=yes
make install

#cp -R ../include_mac ./

cp -R ../examples ./

# TODO ren later
#cp ../wjc_tcc_tcc_osx_test.sh ./tcctcc.sh
#cp ../wjc_tcc_run_in.sh ./tcc_run.sh
#
#chmod +x *.sh
#
#echo ---------- test examples/ex5
#./tcc_run.sh examples/ex5.c
#
#echo ---------- test examples/ex1
#./tcc_run.sh examples/ex1.c
#
#echo ---------- test examples/ex3
#./tcc_run.sh examples/ex3.c 30
#
#echo ----------- test tcctcc.sh -vv
#./tcctcc.sh -vv
