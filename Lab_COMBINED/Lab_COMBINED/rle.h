#pragma once
#include "crypto.h"
#include "string"

class RLECompressor : public Crypto {
public:
    std::string encrypt(std::string input, map_type m = map_type()) override;
    std::string decrypt(std::string input, map_type m = map_type()) override;
    void test(std::string s, map_type options = map_type()) override;
};