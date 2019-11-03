FROM ubuntu:latest

RUN apt-get update \
    && apt-get install -y cppcheck doxygen clang cmake g++ valgrind gcovr python3-pip bash sudo

RUN pip3 install conan \
    && conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
