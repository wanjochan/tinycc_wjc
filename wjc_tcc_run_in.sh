#TODO tcc_core_run => tcc_core (bin) => tcc
#TCCRUN=./tcc_core_run
#$TCCRUN -D__APPLE__ -U_GNU_SOURCE -I. -I.. -Iinclude_mac -DTCC_TARGET_MACHO -DTCC_TARGET_X86_64 -DTCC_TARGET_MACHO -B. wjc_test.c $*

#wrong TCCRUN="./tcc -D__APPLE__ -U_GNU_SOURCE -I. -I.. -Iinclude_mac -DTCC_TARGET_MACHO -DTCC_TARGET_X86_64 -DTCC_TARGET_MACHO -D__DEFINED_va_list -run"

TCCRUN="./tcc -D__APPLE__ -U_GNU_SOURCE -Iinclude_mac -DTCC_TARGET_MACHO -DTCC_TARGET_X86_64 -B. -I. -I.. -run"
$TCCRUN $*

