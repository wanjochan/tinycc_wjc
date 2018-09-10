RT=$(cd `dirname $0`; pwd)

#docker run -v `pwd`:/work/ -w /work/ -ti cmptech/tinycc_dev tcc $*
sh $RT/dkrun.sh tcc $*
