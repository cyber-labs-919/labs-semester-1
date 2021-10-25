#pragma once
#include <string>
#include "crypto.h"

class SubstitutionCipherCrypto : public Crypto {
public:
    std::string encrypt(std::string inp, map_type options) override;
    std::string decrypt(std::string inp, map_type options) override;
    void test(std::string inp, map_type options) override;
};