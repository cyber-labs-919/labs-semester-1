#pragma once
#include <string>
#include "crypto.h"

class SubstitutionCipherCrypto : public Crypto {
public:
    virtual std::string encrypt(std::string inp, map_type options);
    virtual std::string decrypt(std::string inp, map_type options);
    virtual void test(std::string inp, map_type options);
};
