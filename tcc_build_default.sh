arch=$(uname -s)_$(uname -m)
#echo arch=$arch
sh $(dirname $0)/tcc_$arch.sh
