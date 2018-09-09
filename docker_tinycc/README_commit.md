IMID=`docker build .`
CID=`docker run -D $IMID`
docker commit cmptech/tinycc $CID
