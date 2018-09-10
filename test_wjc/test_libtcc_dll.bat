@ECHO OFF

@rem tcc_i386-win32.exe -I..\win32\include -I..\include -I.. -I..\win32\include\winapi -DTCC_TARGET_I386 -Wall -g -O2 -run test_libtcc_dll.c 

@tcc_i386-win32.exe -o ../test_wjc/test_libtcc_dll.exe ../test_wjc/test_libtcc_dll.c ../test_wjc/libtcc_dll.dll

@tcc_i386-win32.exe -I..\win32\include -I..\include -I.. -I..\win32\include\winapi -DTCC_TARGET_I386 test_libtcc_dll.c libtcc_dll.dll

@test_libtcc_dll.exe %*
