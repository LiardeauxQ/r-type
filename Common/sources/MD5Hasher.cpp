//
// Created by nwmqpa on 13/11/19
//

#include <iostream>
#include <algorithm>
#include <string.h>
#include "Definitions.hpp"
#include "MD5Hasher.hpp"

#ifdef __APPLE__
    #include <CommonCrypto/CommonDigest.h>
#else
    #include <openssl/md5.h>
#endif

String MD5Hasher::hash(String const &toHash) {
    unsigned char *data = new unsigned char[toHash.length()];
    memset(data, 0, toHash.length());
#ifdef __APPLE__
    CC_MD5_CTX context;
    CC_MD5_Init(&context);
    CC_MD5_Update(&context, toHash.c_str(), (CC_LONG)strlen(toHash.c_str()));
    CC_MD5_Final(data, &context);
#else
    MD5(reinterpret_cast<const char unsigned *>(toHash.c_str()), toHash.length(), data);
#endif
    auto str = String(reinterpret_cast<char *>(data));
    delete[] data;
    return str;
}

String MD5Hasher::genRandomString(size_t length) {
    auto randchar = []() -> char
    {
        const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[rand() % max_index];
    };
    String str(length, 0);
    std::generate_n(str.begin(), length, randchar);
    return str;
}