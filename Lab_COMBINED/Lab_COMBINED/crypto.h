#pragma once
#include <string>
#include <map>

class Crypto {
public:
	typedef std::map<std::string, std::string> map_type;
	virtual std::string encrypt(std::string plaintext, map_type options=map_type()) = 0;
	virtual std::string decrypt(std::string ciphertext, map_type options=map_type()) = 0;
	virtual void test(std::string s, map_type options=map_type()) = 0;
};