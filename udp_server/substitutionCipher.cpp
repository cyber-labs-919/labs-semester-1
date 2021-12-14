#include <iostream>
#include <string>
#include "substitutionCipher.h"

using namespace std;

string SubstitutionCipherCrypto::encrypt(string inp, map_type options) {
    if (!options.count("keyTo") || !options.count("keyFrom")) {
        throw std::runtime_error("Substitution cipher requires options keyTo and keyFrom.");
    }

    string keyTo = options["keyTo"];
    string keyFrom = options["keyFrom"];

    if (keyFrom.length() != keyTo.length()) {
        throw std::runtime_error("keyFrom and keyTo must have an equal length.");
    }

    bool warned = false;
    string encrypted = "";
    for (char c : inp) {
        int pos = keyFrom.find(c);
        if (pos == string::npos) {
            int secPos = keyTo.find(c);
            if (secPos != string::npos) {
                warned = true;
                cout << "Warning: character " << c << " in the plaintext is in keyTo, but not in keyFrom. The ciphertext will not be possible to accurately reverse into plaintext, " <<
                    "because " << c << " will remain the same in the ciphertext, and during decryption we won't be able to determine if it was initially " << c <<
                    ", or if it was " << keyFrom[secPos] << " and was encrypted into " << c << "." << endl;
            }
            encrypted += c;
        }
        else {
            encrypted += keyTo[pos];
        }
    }
    return encrypted;
}

string SubstitutionCipherCrypto::decrypt(std::string inp, map_type options)
{
    if (!options.count("keyTo") || !options.count("keyFrom")) {
        throw std::runtime_error("Substitution cipher requires options keyTo and keyFrom.");
    }

    return encrypt(inp, { {"keyFrom", options["keyTo"]}, {"keyTo", options["keyFrom"]} });
}

void SubstitutionCipherCrypto::test(string inp, map_type options) {
    string encrypted = encrypt(inp, options);
    string decrypted = decrypt(encrypted, options);
    cout << "Input:     " << inp << endl;
    cout << "Encrypted: " << encrypted << endl;
    cout << "Decrypted: " << decrypted << endl;
    cout << "Success:   " << (inp == decrypted ? "true" : "false (reason explained in the warning)") << endl;
}