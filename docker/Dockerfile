FROM ubuntu:bionic as base

RUN sed -i 's/archive.ubuntu.com/mirrors.tuna.tsinghua.edu.cn/' /etc/apt/sources.list && \
    sed -i 's/security.ubuntu.com/mirrors.tuna.tsinghua.edu.cn/' /etc/apt/sources.list
ENV DEBIAN_FRONTEND=noninteractive 
RUN apt-get update && apt-get install -y --no-install-recommends \
        liblapack3 \
        libtiff5 \
        freeglut3 \
        libglu1-mesa \
        libpng16-16 \
        libreadline7 \
        libopencv-core3.2 \
        libopencv-imgproc3.2 \
        libopencv-videoio3.2 \
        libopencv-imgcodecs3.2 \
        libopencv-contrib3.2

FROM base as builder

RUN apt-get update && apt-get install -y --no-install-recommends \
        build-essential \
        liblapack-dev \
        libtiff-dev \
        freeglut3-dev \
        libpng-dev \
        libreadline-dev \
        libopencv-dev \
        unzip \
        git \
        ca-certificates

WORKDIR /src/deps
RUN git clone --branch TOON_3.2 --depth 1 https://github.com/edrosten/TooN.git
WORKDIR /src/deps/TooN
RUN ./configure && make -j8 && make install

WORKDIR /src/deps
RUN git clone --branch RELEASE_20121025.2 --depth 1 https://github.com/edrosten/libcvd.git
WORKDIR /src/deps/libcvd
RUN ./configure && make -j8 && make install

WORKDIR /src/deps
RUN git clone --depth 1 https://github.com/edrosten/gvars.git
WORKDIR /src/deps/gvars
RUN ./configure && make -j8 && make install

WORKDIR /src/deps
COPY docker/lib3ds-20080909.zip ./
RUN unzip lib3ds-20080909.zip
WORKDIR /src/deps/lib3ds-20080909
RUN LDFLAGS=-lm ./configure && make -j8 && make install

WORKDIR /src/PTAMM
COPY . .
RUN make -j8

FROM base

RUN apt-get update && apt-get install -y --no-install-recommends \
        mencoder

COPY --from=builder /usr/local/lib/lib3ds-2.so.0.0.0 \
                    /usr/local/lib/libcvd.so.0.8 \
                    /usr/local/lib/libGVars3.so.0.6 \
                    /usr/local/lib/
COPY --from=builder /src/PTAMM/PTAMM \
                    /src/PTAMM/CameraCalibrator \
                    /src/PTAMM/drawMarker \
                    /usr/local/bin/

RUN ln -s lib3ds-2.so.0.0.0 /usr/local/lib/lib3ds-2.so.0 && \
    ln -s libcvd.so.0.8 /usr/local/lib/libcvd.so.0 && \
    ln -s libGVars3.so.0.6 /usr/local/lib/libGVars3.so.0 && \
    ln -s libGVars3.so.0 /usr/local/lib/libGVars3.so && \
    ldconfig

COPY settings.cfg /data/
COPY ARData /data/ARData
WORKDIR /data
VOLUME [ "/data" ]
CMD [ "/usr/local/bin/PTAMM" ]
