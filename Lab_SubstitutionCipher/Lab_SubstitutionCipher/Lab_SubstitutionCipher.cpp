// Lab_SubstitutionCipher.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
using namespace std;

string encrypt(string inp, string keyFrom, string keyTo) {
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
                cout << "Warning: character " << c << " is in keyTo, but not in keyFrom. The ciphertext will not be possible to accurately reverse into plaintext, " <<
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

void test(string inp, string keyFrom, string keyTo) {
    string encrypted = encrypt(inp, keyFrom, keyTo);
    string decrypted = encrypt(encrypted, keyTo, keyFrom);
    cout << "Input:     " << inp << endl;
    cout << "Encrypted: " << encrypted << endl;
    cout << "Decrypted: " << decrypted << endl;
    cout << "Success:   " << (inp == decrypted ? "true" : "false (reason explained in the warning)") << endl;
}

int main()
{
    test("test123", "es2", "fra");
    cout << endl;
    test("hello, world", "abcdefgh", "qwextyui"); // sa chi ashxati vortev sxal tipi key-enq tvel, avelin kbacatrvi warningum
    cout << endl;
    test("this is a test message", "abcdef", "fedcba");
    cout << endl;
}