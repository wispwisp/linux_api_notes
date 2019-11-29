FROM ubuntu:latest

RUN apt update && apt install -y llvm clang cmake google-mock libgtest-dev

# Compile gmock
WORKDIR /usr/src/gmock
RUN cmake CMakeLists.txt && \
    make && \
    cp *.a /usr/lib

# Compile gtest
WORKDIR /usr/src/gtest
RUN cmake CMakeLists.txt && \
    make && \
    cp *.a /usr/lib

WORKDIR /src
