#TODO tcc_core_run => tcc_core (bin) => tcc
#TCCRUN=./tcc_core_run
#$TCCRUN -D__APPLE__ -U_GNU_SOURCE -I. -I.. -Iinclude_mac -DTCC_TARGET_MACHO -DTCC_TARGET_X86_64 -DTCC_TARGET_MACHO -B. wjc_test.c $*


#wrong TCCRUN="./tcc -D__APPLE__ -U_GNU_SOURCE -I. -I.. -Iinclude_mac -DTCC_TARGET_MACHO -DTCC_TARGET_X86_64 -DTCC_TARGET_MACHO -D__DEFINED_va_list -run"

TCCRUN="./tcc -D__APPLE__ -U_GNU_SOURCE -I. -I.. -Iinclude_mac -DTCC_TARGET_MACHO -DTCC_TARGET_X86_64 -DTCC_TARGET_MACHO -B.. -run"
$TCCRUN $*



#notes if not using one_source will report found no libtcc1.a
#$TCC -D__APPLE__ -U_GNU_SOURCE -I. -I.. -Iinclude_mac -DTCC_TARGET_MACHO -DTCC_TARGET_X86_64 -DTCC_TARGET_MACHO -B_build_clang/ -run tcc_core_run.c $*

#$TCC -D__APPLE__ -U_GNU_SOURCE -I. -I.. -Iinclude_mac -DTCC_TARGET_MACHO -DTCC_TARGET_X86_64 -DTCC_TARGET_MACHO -run tcc_core_run.c $*


#TODO 
#NOTES for cross build, the osx one should auto get the define done above...?
# e.g.  tcc_osx_64.bin  etc....
