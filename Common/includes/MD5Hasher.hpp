//
// Created by nwmqpa on 13/11/19
//

#include "Definitions.hpp"

class MD5Hasher {

    public:
        static String hash(String const &toHash);
        static String genRandomString(size_t length);

};
