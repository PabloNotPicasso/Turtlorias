FROM gcc:latest

RUN apt-get update && \
    apt-get install -y \
    cmake \
    git \
    clang-format \
    python3 python3-pip \
    libboost-dev libboost-program-options-dev libboost-log-dev

RUN apt-get upgrade -y
RUN pip3 install --upgrade pip setuptools wheel
RUN pip3 install cmakelang  

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

# RUN groupadd -r $USERGROUP
# RUN useradd -r -u 1000 -g $USERGROUP $USERNAME
USER ${USERNAME}