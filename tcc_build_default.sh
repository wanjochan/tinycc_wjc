echo build mostly default

arch=$(uname -s)_$(uname -m)
build_arch=build_current_${arch}
echo arch=$arch,build_arch=$build_arch
mkdir -p $build_arch/
cd $build_arch/

#../configure --prefix=. --cc=clang --config-musl
#../configure --config-musl --prefix=.
../configure --config-musl
make clean
make
make install
cd ..
ls -al $build_arch/
#$build_arch/tcc -vv

echo $build_arch/tcc -vv
$build_arch/tcc -vv

echo tcc -vv
tcc -vv

