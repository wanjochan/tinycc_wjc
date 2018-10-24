
# debug

## for gdb
ulimit -c unlimited

## lldb (for clang compiled, as gdb/gcc)

LASTCORE=`ls -ltr /cores/ | tail -1 | awk '{print $NF}'`
echo lldb -c /cores/$LASTCORE
lldb -c /cores/$LASTCORE

## call bt in lldb shell to get the stacks
(lldb) bt
