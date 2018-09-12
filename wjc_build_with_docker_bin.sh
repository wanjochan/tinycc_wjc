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


# TODO rebuild  "i386-win32-tcc" with libtcc1.a in same folder.....





# i386 cross test

#cp i386-libtcc1.a ../test_wjc/
#cp i386-win32-libtcc1.a ../test_wjc/
cp i386-win32-libtcc1.a ../test_wjc/lib/libtcc1.a

./i386-win32-tcc -DTCC_TARGET_I386 -DTCC_TARGET_PE -o ../test_wjc/test_c_w32.exe ../test_wjc/test_c.c

./i386-win32-tcc -DTCC_TARGET_I386 -DTCC_TARGET_PE -o ../test_wjc/tcc_i386-win32.exe ../tcc.c
./i386-win32-tcc -DTCC_TARGET_I386 -DTCC_TARGET_PE -I.. -shared -rdynamic -o ../test_wjc/libtcc_dll.dll ../test_wjc/libtcc_dll.c

./i386-win32-tcc -impdef ../test_wjc/libtcc_dll.dll
mv *.def ../test_wjc/

./i386-win32-tcc -DTCC_TARGET_I386 -DTCC_TARGET_PE -o ../test_wjc/test_libtcc_dll.exe ../test_wjc/test_libtcc_dll.c ../test_wjc/libtcc_dll.dll

cp -R lib ../test_wjc/
cp -Rf ../include ../test_wjc
cp -R ../win32/include/* ../test_wjc/include/

ls -al ../test_wjc/

echo now you can refer to README_wjc for more testing examples
