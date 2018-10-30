
# debug

## for gdb
ulimit -c unlimited

## lldb (for clang compiled, as gdb/gcc)

LASTCORE=`ls -ltr /cores/ | tail -1 | awk '{print $NF}'`
echo lldb -c /cores/$LASTCORE
lldb -c /cores/$LASTCORE

## call bt in lldb shell to get the stacks
(lldb) bt


```
$ otool -L /usr/lib/libc.dylib 
/usr/lib/libc.dylib:
	/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 1252.50.4)
	/usr/lib/system/libcache.dylib (compatibility version 1.0.0, current version 80.0.0)
	/usr/lib/system/libcommonCrypto.dylib (compatibility version 1.0.0, current version 60118.50.1)
	/usr/lib/system/libcompiler_rt.dylib (compatibility version 1.0.0, current version 62.0.0)
	/usr/lib/system/libcopyfile.dylib (compatibility version 1.0.0, current version 1.0.0)
	/usr/lib/system/libcorecrypto.dylib (compatibility version 1.0.0, current version 562.50.17)
	/usr/lib/system/libdispatch.dylib (compatibility version 1.0.0, current version 913.50.12)
	/usr/lib/system/libdyld.dylib (compatibility version 1.0.0, current version 551.3.0)
	/usr/lib/system/libkeymgr.dylib (compatibility version 1.0.0, current version 28.0.0)
	/usr/lib/system/liblaunch.dylib (compatibility version 1.0.0, current version 1205.50.76)
	/usr/lib/system/libmacho.dylib (compatibility version 1.0.0, current version 906.0.0)
	/usr/lib/system/libquarantine.dylib (compatibility version 1.0.0, current version 86.0.0)
	/usr/lib/system/libremovefile.dylib (compatibility version 1.0.0, current version 45.0.0)
	/usr/lib/system/libsystem_asl.dylib (compatibility version 1.0.0, current version 356.50.1)
	/usr/lib/system/libsystem_blocks.dylib (compatibility version 1.0.0, current version 67.0.0)
	/usr/lib/system/libsystem_c.dylib (compatibility version 1.0.0, current version 1244.50.9)
	/usr/lib/system/libsystem_configuration.dylib (compatibility version 1.0.0, current version 963.50.8)
	/usr/lib/system/libsystem_coreservices.dylib (compatibility version 1.0.0, current version 51.0.0)
	/usr/lib/system/libsystem_darwin.dylib (compatibility version 1.0.0, current version 1.0.0)
	/usr/lib/system/libsystem_dnssd.dylib (compatibility version 1.0.0, current version 878.50.17)
	/usr/lib/system/libsystem_info.dylib (compatibility version 1.0.0, current version 1.0.0)
	/usr/lib/system/libsystem_m.dylib (compatibility version 1.0.0, current version 3147.50.1)
	/usr/lib/system/libsystem_malloc.dylib (compatibility version 1.0.0, current version 140.50.6)
	/usr/lib/system/libsystem_network.dylib (compatibility version 1.0.0, current version 1.0.0)
	/usr/lib/system/libsystem_networkextension.dylib (compatibility version 1.0.0, current version 1.0.0)
	/usr/lib/system/libsystem_notify.dylib (compatibility version 1.0.0, current version 172.0.0)
	/usr/lib/system/libsystem_sandbox.dylib (compatibility version 1.0.0, current version 765.50.51)
	/usr/lib/system/libsystem_secinit.dylib (compatibility version 1.0.0, current version 30.0.0)
	/usr/lib/system/libsystem_kernel.dylib (compatibility version 1.0.0, current version 4570.51.2)
	/usr/lib/system/libsystem_platform.dylib (compatibility version 1.0.0, current version 161.50.1)
	/usr/lib/system/libsystem_pthread.dylib (compatibility version 1.0.0, current version 301.50.1)
	/usr/lib/system/libsystem_symptoms.dylib (compatibility version 1.0.0, current version 1.0.0)
	/usr/lib/system/libsystem_trace.dylib (compatibility version 1.0.0, current version 829.50.17)
	/usr/lib/system/libunwind.dylib (compatibility version 1.0.0, current version 35.3.0)
	/usr/lib/system/libxpc.dylib (compatibility version 1.0.0, current version 1205.50.76)
wanjochan: ~/Downloads/github/tinycc_wjc
$ otool -L /usr/lib/libdl.dylib 
/usr/lib/libdl.dylib:
	/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 1252.50.4)
	/usr/lib/system/libcache.dylib (compatibility version 1.0.0, current version 80.0.0)
	/usr/lib/system/libcommonCrypto.dylib (compatibility version 1.0.0, current version 60118.50.1)
	/usr/lib/system/libcompiler_rt.dylib (compatibility version 1.0.0, current version 62.0.0)
	/usr/lib/system/libcopyfile.dylib (compatibility version 1.0.0, current version 1.0.0)
	/usr/lib/system/libcorecrypto.dylib (compatibility version 1.0.0, current version 562.50.17)
	/usr/lib/system/libdispatch.dylib (compatibility version 1.0.0, current version 913.50.12)
	/usr/lib/system/libdyld.dylib (compatibility version 1.0.0, current version 551.3.0)
	/usr/lib/system/libkeymgr.dylib (compatibility version 1.0.0, current version 28.0.0)
	/usr/lib/system/liblaunch.dylib (compatibility version 1.0.0, current version 1205.50.76)
	/usr/lib/system/libmacho.dylib (compatibility version 1.0.0, current version 906.0.0)
	/usr/lib/system/libquarantine.dylib (compatibility version 1.0.0, current version 86.0.0)
	/usr/lib/system/libremovefile.dylib (compatibility version 1.0.0, current version 45.0.0)
	/usr/lib/system/libsystem_asl.dylib (compatibility version 1.0.0, current version 356.50.1)
	/usr/lib/system/libsystem_blocks.dylib (compatibility version 1.0.0, current version 67.0.0)
	/usr/lib/system/libsystem_c.dylib (compatibility version 1.0.0, current version 1244.50.9)
	/usr/lib/system/libsystem_configuration.dylib (compatibility version 1.0.0, current version 963.50.8)
	/usr/lib/system/libsystem_coreservices.dylib (compatibility version 1.0.0, current version 51.0.0)
	/usr/lib/system/libsystem_darwin.dylib (compatibility version 1.0.0, current version 1.0.0)
	/usr/lib/system/libsystem_dnssd.dylib (compatibility version 1.0.0, current version 878.50.17)
	/usr/lib/system/libsystem_info.dylib (compatibility version 1.0.0, current version 1.0.0)
	/usr/lib/system/libsystem_m.dylib (compatibility version 1.0.0, current version 3147.50.1)
	/usr/lib/system/libsystem_malloc.dylib (compatibility version 1.0.0, current version 140.50.6)
	/usr/lib/system/libsystem_network.dylib (compatibility version 1.0.0, current version 1.0.0)
	/usr/lib/system/libsystem_networkextension.dylib (compatibility version 1.0.0, current version 1.0.0)
	/usr/lib/system/libsystem_notify.dylib (compatibility version 1.0.0, current version 172.0.0)
	/usr/lib/system/libsystem_sandbox.dylib (compatibility version 1.0.0, current version 765.50.51)
	/usr/lib/system/libsystem_secinit.dylib (compatibility version 1.0.0, current version 30.0.0)
	/usr/lib/system/libsystem_kernel.dylib (compatibility version 1.0.0, current version 4570.51.2)
	/usr/lib/system/libsystem_platform.dylib (compatibility version 1.0.0, current version 161.50.1)
	/usr/lib/system/libsystem_pthread.dylib (compatibility version 1.0.0, current version 301.50.1)
	/usr/lib/system/libsystem_symptoms.dylib (compatibility version 1.0.0, current version 1.0.0)
	/usr/lib/system/libsystem_trace.dylib (compatibility version 1.0.0, current version 829.50.17)
	/usr/lib/system/libunwind.dylib (compatibility version 1.0.0, current version 35.3.0)
	/usr/lib/system/libxpc.dylib (compatibility version 1.0.0, current version 1205.50.76)
```
