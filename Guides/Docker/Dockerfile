FROM ubuntu:latest

RUN apt-get update -y && apt-get upgrade -y && \
    apt-get install -y \
    cmake \
    git \
    cppcheck \
    clang-format \
    clang-tidy \
    python3 python3-pip python3-setuptools python3-wheel \
    libboost-dev libboost-program-options-dev libboost-log-dev \
    lcov

RUN pip install cmake_format
RUN pip install gcovr
RUN pip install lcov_cobertura

RUN apt-get update -y && apt-get upgrade -y

###########################
# GTest
RUN git clone https://github.com/google/googletest.git -b release-1.11.0
RUN cd googletest && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make && \
    make install

###########################
# Adding User
ARG USERID=1000
ARG GROUPID=1000
ARG USERNAME=turtorias_user
ARG USERGROUP=turtorias_group

RUN groupadd -o -g ${GROUPID} ${USERGROUP} \
  && useradd -o --no-log-init -m -u ${USERID} -g ${USERGROUP} ${USERNAME}

USER ${USERNAME}