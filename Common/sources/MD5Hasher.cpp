//
// Created by nwmqpa on 13/11/19
//

#include "Definitions.hpp"
#include "MD5Hasher.hpp"
#include <openssl/md5.h>

String MD5Hasher::hash(String const &toHash) {
    unsigned char *data = new unsigned char[toHash.length()];
    MD5(reinterpret_cast<const char unsigned *>(toHash.c_str()), toHash.length(), data);
    auto str = String(reinterpret_cast<char *>(data));
    delete[] data;
    return str;
}