FROM alpine:latest

RUN apk update \
    && apk add cppcheck doxygen clang cmake gcc valgrind gcovr python3-dev musl-dev

RUN python3 -m pip install --upgrade pip

RUN python3 -m pip install conan
