#tcc -DONE_SOURCE=1 -D__APPLE__ -U_GNU_SOURCE -I. -I.. -Iinclude_mac -DTCC_TARGET_MACHO -DTCC_TARGET_X86_64 -DTCC_TARGET_MACHO -B.. -B. -run $*
#tcc -DONE_SOURCE=1 -D__APPLE__ -U_GNU_SOURCE -I. -I.. -Iinclude_mac -DTCC_TARGET_X86_64 -DTCC_TARGET_MACHO -B.. -B. -run $*
#tcc -DONE_SOURCE=1 -U_GNU_SOURCE -I. -I.. -DTCC_TARGET_X86_64 -B.. -B. -run $*

# call tcc (in the docker)
tcc -I. -I.. -run $*
