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

#cp ../wjc_tcc_run_in_docker.sh ./tcc_run.sh

chmod +x *.sh

#echo ---------- test examples/ex5
#./tcc_run.sh examples/ex5.c
#
#echo ---------- test examples/ex1
#./tcc_run.sh examples/ex1.c
#
#echo ---------- test examples/ex3
#./tcc_run.sh examples/ex3.c 30

alias tcc_run='tcc -I. -I.. -run'
tcc_run examples/ex3.c 30

# i386 cross test

#cp i386-libtcc1.a ../test_docker/
#cp i386-win32-libtcc1.a ../test_docker/
#cp i386-win32-libtcc1.a ../test_docker/lib/libtcc1.a

./i386-win32-tcc -DTCC_TARGET_I386 -DTCC_TARGET_PE -o ../test_docker/test_c_w32.exe ../test_docker/test_c.c

./i386-win32-tcc -DTCC_TARGET_I386 -DTCC_TARGET_PE -o ../test_docker/tcc_i386-win32.exe ../tcc.c

cp ../test_docker/tcc_i386-win32.exe ../test_docker/tcc_upx.exe

upx ../test_docker/tcc_upx.exe

#./i386-win32-tcc -DTCC_LIB_DLL -I.. -shared -rdynamic -o ../test_docker/libtcc.dll ../tcc.c
./i386-win32-tcc -DTCC_TARGET_I386 -DTCC_TARGET_PE -DTCC_LIB_DLL -I.. -shared -rdynamic -o ../test_docker/libtcc.dll ../tcc.c

./i386-win32-tcc -impdef ../test_docker/libtcc.dll
mv *.def ../test_docker/

./i386-win32-tcc -DTCC_TARGET_I386 -DTCC_TARGET_PE -o ../test_docker/test_libtcc_dll.exe ../test_docker/test_libtcc_dll.c ../test_docker/libtcc.dll

cp -R lib ../test_docker/

cp -Rf ../include ../test_docker
cp -R ../win32/include/* ../test_docker/include/

ls -al ../test_docker/

############################
#tcc -DTCC_LIB_DLL -I. -I.. -shared -rdynamic -o ../test_docker/libtcc.so ./tcc.c 
tcc -DTCC_LIB_DLL -I.. -shared -rdynamic -o tcc.so ../tcc.c
tcc -o ./test_libtcc_dll ../test_docker/test_libtcc_dll.c ./tcc.so
LD_LIBRARY_PATH=. ./test_libtcc_dll

echo now you can refer to README_wjc for more testing examples
