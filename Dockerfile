# syntax=docker/dockerfile:1.0.0-experimental

FROM ubuntu:22.04

RUN apt update && apt upgrade -y
RUN apt install -y git

RUN mkdir -p -m 0600 ~/.ssh && \
    ssh-keyscan github.com >> ~/.ssh/known_hosts && \
    git config --global url.git@github.com:.insteadOf https://github.com/
RUN --mount=type=secret,id=ssh,target=/root/.ssh/id_rsa

RUN apt install -y cmake build-essential ffmpeg libavcodec-dev libavformat-dev libswscale-dev libdc1394-dev libfreetype6-dev libharfbuzz-dev libgtk2.0-dev libgtk-3-dev

WORKDIR /opencv
RUN --mount=type=secret,id=ssh,target=/root/.ssh/id_rsa \
    git clone git@github.com:opencv/opencv.git -b 4.6.0
RUN --mount=type=secret,id=ssh,target=/root/.ssh/id_rsa \
    git clone git@github.com:opencv/opencv_contrib.git -b 4.6.0

WORKDIR /opencv/opencv/build
RUN cmake \
    -DBUILD_DOCS=OFF \
    -DBUILD_TESTS=OFF \
    -DBUILD_PERF_TESTS=OFF \
    -DINSTALL_PYTHON_EXAMPLES=OFF \
    -DINSTALL_C_EXAMPLES=OFF \
    -DBUILD_EXAMPLES=OFF \
    -DBUILD_JAVA=OFF \
    -DBUILD_FAT_JAVA_LIB=OFF \
    -DBUILD_opencv_python2=OFF \
    -DBUILD_opencv_python3=OFF \
    -DOPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules \
    ..
RUN make install -j"$(nproc)"

WORKDIR /
RUN --mount=type=secret,id=ssh,target=/root/.ssh/id_rsa \
    git clone git@github.com:nkue-yst/TouchLED-Middleware.git tll

WORKDIR /tll/build
RUN --mount=type=secret,id=ssh,target=/root/.ssh/id_rsa \
    git submodule update --init
RUN cmake .. && \
    make -j"$(nproc)"

#######################################################################
### Build to `$ docker build --secret id=ssh,src=<path/to/id_rsa> . ###
#######################################################################