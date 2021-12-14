#pragma once
#include "crypto.h"
#include "string"

class RLECompressor : public Crypto {
public:
    virtual std::string encrypt(std::string input, map_type m = map_type());
    virtual std::string decrypt(std::string input, map_type m = map_type());
    virtual void test(std::string s, map_type options = map_type());
};