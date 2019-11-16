//
// Created by nwmqpa on 13/11/19
//

#include "Definitions.hpp"
#include "MD5Hasher.hpp"

#ifdef __APPLE__
    #include <CommonCrypto/CommonDigest.h>
#else
    #include <openssl/md5.h>
#endif

String MD5Hasher::hash(String const &toHash) {
    unsigned char *data = new unsigned char[toHash.length()];
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
