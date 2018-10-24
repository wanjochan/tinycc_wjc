#objdump -t build_Darwin_x86_64/tcc
#nm -t d -S --size-sort build_Darwin_x86_64/tcc

nm --print-size --size-sort --radix=d build_Darwin_x86_64/tcc

size -A -d build_Darwin_x86_64/tcc

size -A -d build_in_dkr_gcc_musl/tcc

readelf.py -s build_in_dkr_gcc_musl/tcc | perl -ne 'if(/(\S+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)/) { print $3 . " " . $8. "\n";}'|sort -n

readelf -s build_in_dkr_gcc_musl/tcc | perl -ne 'if(/(\S+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)/) { print $3 . " " . $8. "\n";}'|sort -n

#build_Darwin_x86_64/tcc  :
#section               size         addr
#__text              336429   4294970160
#__stubs                 54   4295306590
#__stub_helper          108   4295306644
#__cstring            11105   4295306752
#__const              14844   4295317872
#__unwind_info          812   4295332716
#__eh_frame           14696   4295333528
#__dyld                  16   4295348224
#__got                  536   4295348240
#__la_symbol_ptr         72   4295348776
#__const               1056   4295348848
#__data                 132   4295349904
#__common             49616   4295360512
#__bss               132600   4295410128
#Total               562076

#It is also usefull to use -ffunction-sections -fdata-sections as compile parameter and -Wl,--gc-sections as linker parameter so it will delete all unused functions and data from your binary.
