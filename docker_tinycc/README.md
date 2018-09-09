# TODO

```
cmptech/docker_tinycc_builder

apk update && apk upgrade \
&& apk add git autoconf build-base linux-headers \
&& cd /root/ \
&& git clone https://github.com/mirror/tinycc.git --depth 1 \
&& cd tinycc/ \
&& ./configure --config-musl --prefix=. && make && make install \
&& rm -rf /var/cache/apk/* \
&& rm -rf /root/tinycc* \
&& rm -rf /tmp/*

cmptech/docker_tinycc_runner

copy from builder to runner
```
