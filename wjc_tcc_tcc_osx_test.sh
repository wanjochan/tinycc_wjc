#bin/tcc -D__APPLE__ -U_GNU_SOURCE -I. -Iinclude_mac -DTCC_TARGET_MACHO -DTCC_TARGET_X86_64 -DTCC_TARGET_MACHO -D__DEFINED_va_list -B. -run tcc.c $*

#./tcc -D__APPLE__ -U_GNU_SOURCE -I. -Iinclude_mac -DTCC_TARGET_MACHO -DTCC_TARGET_X86_64 -DTCC_TARGET_MACHO -D__DEFINED_va_list -B.  -run ../tcc.c $*

RT=$(cd `dirname $0`; pwd)

$RT/tcc -D__APPLE__ -U_GNU_SOURCE -I. -I.. -Iinclude_mac -DTCC_TARGET_MACHO -DTCC_TARGET_X86_64 -DTCC_TARGET_MACHO -B. -run ../tcc.c $*

