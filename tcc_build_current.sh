#arch=$(uname -s)_$(uname -m)
##echo arch=$arch
#sh $(dirname $0)/tcc_$arch.sh

arch=$(uname -s)_$(uname -m)
build_arch=build_current_${arch}
echo arch=$arch,build_arch=$build_arch
mkdir -p $build_arch/
cd $build_arch/
#../configure --prefix=. --cc=clang --config-musl
../configure --config-musl
make clean
make
make install
cd ..
#ls -al $build_arch/
#$build_arch/tcc -vv
tcc -vv
