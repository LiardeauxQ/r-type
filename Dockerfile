FROM ubuntu:latest

RUN apt-get update \
    && apt-get install -y software-properties-common \
    && add-apt-repository -y ppa:snaipewastaken/ppa \
    && apt-get update \
    && apt-get install -y cppcheck doxygen clang cmake g++ valgrind gcovr python3-pip bash sudo criterion-dev

RUN pip3 install conan \
    && conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
