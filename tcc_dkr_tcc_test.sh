mkdir -p build_tcc_test/
cd build_tcc_test/

#i386-win32-tcc -o test_c_w32.exe ../docker/test_c.c

./i386-win32-tcc -o tcc_i386-win32.exe ../tcc.c
./i386-win32-tcc -o tcc_i386-win32.exe ../tcc.c

cp tcc_i386-win32.exe tcc_upx.exe
cp tcc_i386-win32.exe ../docker/

upx tcc_upx.exe

i386-win32-tcc -DTCC_DLL -I.. -shared -rdynamic -o tcc.dll ../tcc.c

i386-win32-tcc -impdef tcc.dll

i386-win32-tcc -o test_tcc_dll.exe ../docker/test_tcc_dll.c tcc.dll

cp -R lib ../docker/

#cp -Rf ../include ../docker
#cp -R ../win32/include/* ../docker/include/

############################
tcc -DTCC_DLL -I.. -shared -rdynamic -o tcc.so ../tcc.c
tcc -o ./test_tcc_dll ../docker/test_tcc_dll.c ./tcc.so
LD_LIBRARY_PATH=. ./test_tcc_dll

