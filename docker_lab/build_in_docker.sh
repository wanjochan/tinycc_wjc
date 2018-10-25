#NOTES: run me in docker(cmptech/tinycc_dev)

rm -Rf build_docker
mkdir build_docker
cd build_docker

#../configure --prefix=. --cc=clang
#../configure --config-musl --prefix=. --cc=tcc
../configure --config-musl --cc=tcc

make clean
#make ONE_SOURCE=yes
make
make cross
#make test
make install

cp -R ../examples ./

chmod +x *.sh

#alias tcc_run='tcc -I. -I.. -run'
#tcc_run examples/ex3.c 30

# i386 cross test //i386-win32-tcc -DTCC_TARGET_I386 -DTCC_TARGET_PE

i386-win32-tcc -o test_c_w32.exe ../docker_lab/test_c.c

i386-win32-tcc -o tcc_i386-win32.exe ../tcc.c

# TODO in another 
#cp tcc_i386-win32.exe tcc_upx.exe
#cp tcc_i386-win32.exe ../docker_lab/

#upx tcc_upx.exe
#
#i386-win32-tcc -DTCC_DLL -I.. -shared -rdynamic -o tcc.dll ../tcc.c
#
#i386-win32-tcc -impdef tcc.dll
#
#i386-win32-tcc -o test_tcc_dll.exe ../docker_lab/test_tcc_dll.c tcc.dll
#
#cp -R lib ../docker_lab/
#
##cp -Rf ../include ../docker_lab
##cp -R ../win32/include/* ../docker_lab/include/
#
#############################
#tcc -DTCC_DLL -I.. -shared -rdynamic -o tcc.so ../tcc.c
#tcc -o ./test_tcc_dll ../docker_lab/test_tcc_dll.c ./tcc.so
#LD_LIBRARY_PATH=. ./test_tcc_dll
#
#############################
#ls -al ../docker_lab/
#ls -al ../build_docker/
#
#
#echo now you can refer to README_wjc for more testing examples
