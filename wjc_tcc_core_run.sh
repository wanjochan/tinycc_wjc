#TODO tcc_core_run => tcc_core (bin) => tcc
#TCC=./tcc_core_run
#$TCC -D__APPLE__ -U_GNU_SOURCE -I. -I.. -Iinclude_mac -DTCC_TARGET_MACHO -DTCC_TARGET_X86_64 -DTCC_TARGET_MACHO -B. -run tcc_core_run.c $*


TCC=./_build_clang/tcc
#notes if not using one_source will report found no libtcc1.a
#$TCC -D__APPLE__ -U_GNU_SOURCE -I. -I.. -Iinclude_mac -DTCC_TARGET_MACHO -DTCC_TARGET_X86_64 -DTCC_TARGET_MACHO -B_build_clang/ -run tcc_core_run.c $*

$TCC -D__APPLE__ -U_GNU_SOURCE -I. -I.. -Iinclude_mac -DTCC_TARGET_MACHO -DTCC_TARGET_X86_64 -DTCC_TARGET_MACHO -run tcc_core_run.c $*

#TODO 
#NOTES for cross build, the osx one should auto get the define done above...?
# e.g.  tcc_osx_64.bin  etc....
