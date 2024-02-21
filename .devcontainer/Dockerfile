### BUILDER ###
FROM ubuntu:22.04 AS builder

ENV DEBIAN_FRONTEND=noninteractive
RUN apt update && apt install -y \
	git \
	wget \
	libboost-all-dev \
	asciidoc \
	source-highlight \
	doxygen \
	graphviz \
	build-essential \
	cmake

# vSomeIP
WORKDIR /root
RUN git clone https://github.com/COVESA/vsomeip.git vsomeip
RUN mkdir -p vsomeip/build
RUN cmake -S vsomeip -B vsomeip/build
WORKDIR /root/vsomeip/build
RUN make && make install

# CommonAPI
WORKDIR /root
RUN git clone --branch 3.2.0 https://github.com/COVESA/capicxx-core-runtime.git capicxx-core-runtime
RUN mkdir -p capicxx-core-runtime/build
RUN cmake -S capicxx-core-runtime -B capicxx-core-runtime/build
WORKDIR /root/capicxx-core-runtime/build
RUN make && make install

# Generator
WORKDIR /root
RUN wget https://github.com/COVESA/capicxx-core-tools/releases/download/3.2.0.1/commonapi_core_generator.zip \
	&& unzip commonapi_core_generator.zip -d core-generator
RUN wget https://github.com/COVESA/capicxx-someip-tools/releases/download/3.2.0.1/commonapi_someip_generator.zip \
	&& unzip commonapi_someip_generator.zip -d someip-generator

### IMAGE ###
FROM ubuntu:22.04

RUN apt update && apt install -y \
	git \
	vim \
	build-essential \
	cmake \
	default-jre

COPY --from=builder /usr/local/lib /usr/local/lib
COPY --from=builder /usr/local/include /usr/local/include
COPY --from=builder /root/core-generator /usr/local/bin/core-generator
COPY --from=builder /root/someip-generator /usr/local/bin/someip-generator
RUN ldconfig /etc/ld.so.conf.d
ENV LD_LIBRARY_PATH=/usr/local/lib
ENV PATH=$PATH:/usr/local/bin/core-generator:/usr/local/bin/someip-generator