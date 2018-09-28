From ubuntu:bionic 
MAINTAINER Injae Lee <8687lee@gmail.com>


# install dependencies
From 1njaelee/boost:lastest
    
RUN apt-get -y -qq install cmake git dh-autoreconf 
RUN git clone https://github.com/a2o/snoopy.git && cd snoopy && ./bootstrap.sh


RUN mkdir -p /usr/local/lib/cppm
WORKDIR /usr/local/lib/cppm

RUN    git clone https://github.com/INJAE/nieel.git \
    && cd nieel    \
    && mkdir build \
    && cd build    \
    && cmake ..    \
    && make        \
    && make install

RUN cat /var/log/auth.log

