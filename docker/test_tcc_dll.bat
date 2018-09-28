@ECHO OFF

@tcc_i386-win32.exe -o ../test_wjc/test_tcc_dll.exe ../test_wjc/test_tcc_dll.c ../test_wjc/libtcc.dll

@tcc_i386-win32.exe -I..\win32\include -I..\include -I.. -I..\win32\include\winapi -DTCC_TARGET_I386 -DTCC_TARGET_PE test_tcc_dll.c libtcc.def

@test_tcc_dll.exe %*

@tcc_i386-win32.exe -I..\win32\include -I..\include -I.. -I..\win32\include\winapi -DTCC_TARGET_I386 -DTCC_TARGET_PE ..\tcc.c

tcc -v


