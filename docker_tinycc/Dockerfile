FROM alpine

RUN apk update && apk upgrade \
&& apk add git autoconf build-base linux-headers bash \
&& cd /root/ \
&& git clone https://github.com/mirror/tinycc.git --depth 1 \
&& cd tinycc/ \
&& ./configure --config-musl --prefix=/gcctcc && make && make install \
&& export PATH=/gcctcc/bin:$PATH \
&& make clean && ./configure --config-musl --cc=tcc && make cross && make && make install \
&& apk del linux-headers build-base autoconf git \
&& rm -rf /gcctcc/ \
&& rm -rf /var/cache/apk/* \
&& rm -rf /root/tinycc* \
&& rm -rf /tmp/*
