#

Fabrice Bellard is one of the best Programmer of the world.

# Target

* iPhone build;
* Android build;
* OSX build (need to learn objconv + mach-o); estimate 1 year later

# TODO

* remove 
* tcc_make (quick replacement for the make) auto judge plaform and arch
* cross build all binary for all platform known.. ${arch}_${os} like nodejs addon?

# More Testing...

```
#echo try test_libtcc_dll.bat in win32
echo you can:
echo sudo cp dkrun /usr/loca/bin/
echo sudo cp dtcc /usr/loca/bin/
echo 
echo test_libtcc_dll.exe should be able to run now
echo 
echo mujs (338 KB, https://mujs.com/):
echo dtcc -o main one.c main.c
echo dkrun ./main
echo 
echo mjs(214 KB, https://github.com/cesanta/mjs):
echo dtcc -DMJS_MAIN -o mjsbin mjs.c
echo dkrun ./mjsbin mjs/tests/test_1.js

#TODO
#https://duktape.org/ - https://github.com/svaarala/duktape
#
#static(docker) OK:
#dtcc -std=c99 -ohello hello.c duktape.c -lm
tcc -o eval1 eval.c duktape.c -lm
tcc -o eval2 eval.c duktape.c
i386-win32-tcc -DDUK_F_MINT -o eval.exe eval.c duktape.c
#dkrun ./hello
#
#dyn(539KB, docker) basic OK:
#dtcc -fPIC -ldl -shared -rdynamic -soname duktape.dl.lnx -o duktape.dl.lnx duktape.c
#dtcc -fPIC -ldl -O2 -Wall -shared -rdynamic -soname duktape.dl.lnx -o duktape.dl.lnx duktape.c && ls -al duktape.dl.lnx
#echo export LD_LIBRARY_PATH=\$PWD > test_c.sh && echo ./hello >> test_c.sh
#dkrun sh test_c.sh 

#i386-win32-tcc -std=c99 -DDUK_F_MINT -DTCC_TARGET_I386 -DTCC_TARGET_PE -shared -rdynamic -soname duktape.dl.win -o duktape.dl.win duktape.c
i386-win32-tcc -DDUK_F_MINT -shared -rdynamic -soname duktape.dl.win -o duktape.dl.win duktape.c
i386-win32-tcc -DDUK_F_MINT -o hello.exe hello.c duktape.dl.win
i386-win32-tcc -DDUK_F_MINT -o eval.exe eval.c duktape.dl.win

#https://github.com/espruino/Espruino
#http://jerryscript.net/
#https://code.google.com/archive/p/quad-wheel/ - https://github.com/radare/quad-wheel
#https://github.com/gfwilliams/tiny-js (cpp, give-up)
#https://github.com/cesanta/v7 (moved to mjs, give-up)

# TODO UV
#https://github.com/wanjochan/uv_callback
#https://github.com/libuv/libuv

# Smaller C
# https://github.com/alexfru/SmallerC
# need to fix readline, remove the -f
# compile pass using:
# dkrun make
```

# OSX stuffs

https://github.com/vertis/objconv/blob/master/src/elf2mac.cpp
wget https://github.com/vertis/objconv/raw/master/src/elf2mac.cpp

## llvm symbol table dumper
```
## 
nm -D /usr/lib/libc.dylib 
/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/nm: /usr/lib/libc.dylib: File format has no dynamic symbol table

##
nm /usr/lib/libc.dylib

0000000000001a6a T R8289209$_close
0000000000001a6f T R8289209$_fork
0000000000001a74 T R8289209$_fsync
0000000000001a79 T R8289209$_getattrlist
0000000000001a7e T R8289209$_getrlimit
0000000000001a83 T R8289209$_getxattr
0000000000001a88 T R8289209$_open
0000000000001a8d T R8289209$_pthread_attr_destroy
0000000000001a92 T R8289209$_pthread_attr_init
0000000000001a97 T R8289209$_pthread_attr_setdetachstate
0000000000001a9c T R8289209$_pthread_create
0000000000001aa1 T R8289209$_pthread_mutex_lock
0000000000001aa6 T R8289209$_pthread_mutex_unlock
0000000000001aab T R8289209$_pthread_self
0000000000001ab0 T R8289209$_ptrace
0000000000001ab5 T R8289209$_read
0000000000001aba T R8289209$_setattrlist
0000000000001abf T R8289209$_setrlimit
0000000000001ac4 T R8289209$_sigaction
0000000000001ac9 T R8289209$_stat
0000000000001ace T R8289209$_sysctl
0000000000001ad3 T R8289209$_time
0000000000001ad8 T R8289209$_unlink
0000000000001add T R8289209$_write
0000000000001f98 S ___System_BVersionNumber
0000000000001f60 S ___System_BVersionString
00000000000022d0 S ___crashreporter_info__
                 U ___error
                 U ___keymgr_initializer
                 U ___libdarwin_init
                 U ___libkernel_init
                 U ___libplatform_init
                 U ___malloc_init
                 U ___pthread_init
                 U ___stack_logging_early_finished
                 U __asl_fork_child
                 U __dirhelper
                 U __dyld_fork_child
                 U __dyld_initializer
                 U __libSC_info_fork_child
                 U __libSC_info_fork_parent
                 U __libSC_info_fork_prepare
                 U __libc_fork_child
                 U __libc_initializer
                 U __libcoreservices_fork_child
                 U __libsecinit_initializer
                 U __libtrace_fork_child
                 U __libtrace_init
                 U __libxpc_initializer
                 U __mach_fork_child
                 U __malloc_fork_child
                 U __malloc_fork_parent
                 U __malloc_fork_prepare
                 U __notify_fork_child
                 U __pthread_atfork_child
                 U __pthread_atfork_child_handlers
                 U __pthread_atfork_parent
                 U __pthread_atfork_parent_handlers
                 U __pthread_atfork_prepare
                 U __pthread_atfork_prepare_handlers
                 U __pthread_clear_qos_tsd
                 U __pthread_exit_if_canceled
                 U _close
                 U _dispatch_atfork_child
                 U _dispatch_atfork_parent
                 U _dispatch_atfork_prepare
                 U _dlsym
                 U _dyld_get_program_sdk_version
                 U _exit
                 U _fork
                 U _free
                 U _fsync
                 U _getattrlist
                 U _getrlimit
                 U _getxattr
0000000000001ae2 T _libSystem_atfork_child
0000000000001a47 T _libSystem_atfork_parent
0000000000001a22 T _libSystem_atfork_prepare
000000000000194a t _libSystem_initializer
00000000000022a0 s _libSystem_initializer.libc_funcs
0000000000002220 s _libSystem_initializer.libkernel_funcs
0000000000002280 s _libSystem_initializer.libpthread_funcs
                 U _libdispatch_init
0000000000001b28 t _mach_init_old
00000000000022c8 D _mach_init_routine
                 U _malloc
                 U _open
                 U _pthread_attr_destroy
                 U _pthread_attr_init
                 U _pthread_attr_setdetachstate
                 U _pthread_create
                 U _pthread_mutex_lock
                 U _pthread_mutex_unlock
                 U _pthread_self
                 U _ptrace
                 U _read
                 U _realloc
                 U _setattrlist
                 U _setrlimit
                 U _sigaction
                 U _stat
                 U _strncmp
                 U _sysctl
                 U _time
                 U _unlink
                 U _write
                 U _xpc_atfork_child
                 U _xpc_atfork_parent
                 U _xpc_atfork_prepare
                 U dyld_stub_binder
```

# Smaller C
```
//readlink remove -f...

dkrun ./configure
dkrun ./make
dkrun ./make install
```

