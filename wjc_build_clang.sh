rm -Rf _build_clang
mkdir _build_clang
cd _build_clang

../configure --prefix=. --cc=clang
make clean
make
#make test
#make install

##mac clang
#../configure --prefix=. --cc=clang
#make clean
#make
##make install

cp -R ../include ./
cp -R ../include_mac ./

#cp ../libtcc1.a ./

./tcc -vv

cp ../wjc_tcc_tcc_osx_test.sh ./tcctcc.sh

#./tcc -D__APPLE__ -U_GNU_SOURCE -I. -Iinclude_mac -DTCC_TARGET_MACHO -DTCC_TARGET_X86_64 -DTCC_TARGET_MACHO -D__DEFINED_va_list -B.  -run ../tcc.c
#./tcc -D__APPLE__ -U_GNU_SOURCE -I. -Iinclude_mac -DTCC_TARGET_MACHO -DTCC_TARGET_X86_64 -DTCC_TARGET_MACHO -D__DEFINED_va_list -B. -I../lib/tcc/include -run ../examples/ex3.c
sh tcctcc.sh -vv
