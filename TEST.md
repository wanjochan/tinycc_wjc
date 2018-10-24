```
sh tcc_Darwin_x86_64.sh && ../bin/tcc -run -B /usr/lib -B build_Darwin_x86_64/ -I build_Darwin_x86_64/ -I include -D __APPLE__ tcc.c 
sh tcc_Darwin_x86_64.sh && \
./build_Darwin_x86_64/tcc -run -B build_Darwin_x86_64/ -I build_Darwin_x86_64/ -I include -D __APPLE__ tcc.c && \
../bin/tcc -run -B /usr/lib -B build_Darwin_x86_64/ -I build_Darwin_x86_64/ -I include -I. -D __APPLE__ examples/ex3.c 30
./build_Darwin_x86_64/tcc -run -B /usr/lib -B build_Darwin_x86_64/ -I build_Darwin_x86_64/ -I include -I. -D __APPLE__ examples/eg_tcc_dl.c 33

#sh tcc_Darwin_x86_64_install.sh

# build tcc with gcc(musl) in docker
sh tcc_dkr_gcc_musl.sh
# test it with example
dkrun build_in_dkr_gcc_musl/tcc -run -B /usr/lib -B build_in_dkr_gcc_musl/ -I build_in_dkr_gcc_musl/ -I include -I . examples/ex3.c 30
# test it with tcc(run) self
dkrun build_in_dkr_gcc_musl/tcc -run -B /usr/lib -B build_in_dkr_gcc_musl/ -I build_in_dkr_gcc_musl/ -I include -I . tcc.c

# test tcc_dl.h
sh tcc_dkr_gcc_musl.sh && dkrun build_in_dkr_gcc_musl/tcc -run -B /usr/lib -B build_in_dkr_gcc_musl/ -I build_in_dkr_gcc_musl/ -I include -I . tcc.c
```

# __APPLE__

runing inside OS...
