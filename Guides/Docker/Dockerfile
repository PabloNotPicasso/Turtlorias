FROM ubuntu:latest

RUN apt-get update -y && apt-get upgrade -y && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        ca-certificates \
        build-essential \
        cmake \
        git \
        cppcheck \
        clang-format \
        clang-tidy \
        python3 python3-pip python3-setuptools python3-wheel python3-venv \
        pipx \
        libboost-dev libboost-program-options-dev libboost-log-dev \
        lcov && \
    rm -rf /var/lib/apt/lists/*

ENV PIPX_HOME=/usr/local/pipx \
    PIPX_BIN_DIR=/usr/local/bin
ENV PATH="${PIPX_BIN_DIR}:${PATH}"

RUN pipx install "cmakelang==0.6.13" \
 && pipx install "gcovr==7.2" \
 && pipx install "lcov_cobertura==2.0"

###########################
# GTest
RUN git clone --depth 1 -b release-1.11.0 https://github.com/google/googletest.git /tmp/googletest && \
    cmake -S /tmp/googletest -B /tmp/googletest/build -DCMAKE_BUILD_TYPE=Release && \
    cmake --build /tmp/googletest/build -j && \
    cmake --install /tmp/googletest/build && \
    rm -rf /tmp/googletest

###########################
# Adding User
ARG USERID=1000
ARG GROUPID=1000
ARG USERNAME=turtorias_user
ARG USERGROUP=turtorias_group

RUN groupadd -o -g ${GROUPID} ${USERGROUP} \
 && useradd -o --no-log-init -m -u ${USERID} -g ${USERGROUP} ${USERNAME}

USER ${USERNAME}
