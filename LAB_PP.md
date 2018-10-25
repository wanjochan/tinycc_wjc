```
./build_current_Darwin_x86_64/tcc -E -P0 tcc.c > tcc.osx.pp.c 
dkrun ./build_current_Linux_x86_64/tcc -E -P0 tcc.c > tcc.lnx.pp.c 
bcomp tcc.lnx.pp.c tcc.osx.pp.c
```
