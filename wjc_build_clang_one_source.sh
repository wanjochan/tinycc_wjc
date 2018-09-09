rm -Rf _build_clang
mkdir _build_clang
cd _build_clang

../configure --prefix=. --cc=clang
make clean
make ONE_SOURCE=yes
make install

#make test
#make install

##mac clang
#../configure --prefix=. --cc=clang
#make clean
#make
##make install

cp -R ../include_mac ./
cp -R ../examples ./

#cp -R ../include ./

#cp ../libtcc1.a ./

#./tcc -vv

cp ../wjc_tcc_tcc_osx_test.sh ./tcctcc.sh
cp ../wjc_tcc_run_in.sh ./tcc_run.sh

#./tcc -D__APPLE__ -U_GNU_SOURCE -I. -Iinclude_mac -DTCC_TARGET_MACHO -DTCC_TARGET_X86_64 -DTCC_TARGET_MACHO -D__DEFINED_va_list -B.  -run ../tcc.c
#./tcc -D__APPLE__ -U_GNU_SOURCE -I. -Iinclude_mac -DTCC_TARGET_MACHO -DTCC_TARGET_X86_64 -DTCC_TARGET_MACHO -D__DEFINED_va_list -B. -I../lib/tcc/include -run ../examples/ex3.c

echo ---------- test examples/ex5
#sh tcc_run.sh ../examples/ex5.c
sh tcc_run.sh examples/ex5.c

echo ---------- test examples/ex1
#sh tcc_run.sh ../examples/ex1.c
sh tcc_run.sh examples/ex1.c

#./tcc -D__APPLE__ -U_GNU_SOURCE -I. -I.. -Iinclude_mac -DTCC_TARGET_MACHO -DTCC_TARGET_X86_64 -DTCC_TARGET_MACHO -D__DEFINED_va_list -run ../tcc.c

echo ----------- test tcctcc.sh -vv
sh tcctcc.sh -vv
