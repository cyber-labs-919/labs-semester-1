#include <iostream>
#include <string>
#include "rle.h"

using namespace std;

string RLECompressor::encrypt(string inp, map_type)
{
    string res = "";
    int count;

    for (int i = 0; i < inp.length(); i++) {
        if (isdigit(inp[i])) {
            throw std::runtime_error("You can't compress strings that contain numbers with this RLE compression implementation.");
        }
        if ((i + 1) == inp.length() || inp[i] != inp[i + 1]) {
            res += inp[i];
            continue;
        }

        count = 1;
        while (inp[i] == inp[i + 1]) {
            count++;
            i++;
        }

        res += to_string(count) + inp[i];
    }

    return res;
}

string RLECompressor::decrypt(string inp, map_type) {
    string res = "";

    int i = 0;
    while (i < inp.length()) {
        if (isdigit(inp[i])) {
            string digits = "";
            digits += inp[i];

            i += 1;
            while (isdigit(inp[i]) && i < inp.length()) {
                digits += inp[i++];
            }

            if (i >= inp.length()) {
                throw std::runtime_error("Unexpected end of string: there shouldn't be numbers at the end, this isn't a valid RLE comrpessed string.");
            }

            char c = inp[i];
            int count = stoi(digits);
            for (int j = count; j > 0; --j) {
                res += c;
            }

            i += 1;
            continue;
        }

        res += inp[i++];
    }

    return res;
}

void RLECompressor::test(string inp, map_type) {
    cout << "Input: " << inp << endl;
    string compressed = encrypt(inp);
    cout << "Compressed: " << compressed << endl;
    string decompressed = decrypt(compressed);
    cout << "Test: " << (decompressed == inp ? "success" : "failure") << " (decompressed = " << decompressed << ")" << endl;
}