# eg.
# ./dtcc -v
# ./dtcc -run examples/ex5.c

docker run -v `pwd`:/work/ -w /work/ -ti cmptech/tinycc_dev tcc $*
