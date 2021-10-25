#include <iostream>
#include <string>
#include "matrixEnc.h"

using namespace std;

int MatrixEncCrypto::findMinPow(int n) {
    int mSize = 1;
    while (mSize * mSize < n) {
        ++mSize;
    }
    return mSize;
}

int** MatrixEncCrypto::makeMat(string str, int m) {
    int cells = m * m;
    string newStr = "";
    for (char c : str) {
        newStr += c;
    }
    for (int i = str.length(); i < cells; ++i) {
        newStr += "=";
    }

    int** mat = new int* [m];
    for (int i = 0; i < m; ++i) {
        mat[i] = new int[m];
    }

    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < m; ++c) {
            char ch = newStr[r * m + c];
            mat[r][c] = ch;
        }
    }
    return mat;
}

string MatrixEncCrypto::rotateMat(int** mat, int m) {
    int** rotMat = new int* [m];
    for (int i = 0; i < m; ++i) {
        rotMat[i] = new int[m];
    }

    // miangamic string chem sarqum vorovhetev voncvor tenc lab-el kar togh syun poxelu matrici,
    //   miangamic stegh ka
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            rotMat[i][j] = mat[j][i];
        }
    }

    string res = "";
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            res += rotMat[i][j];
        }
        delete[] rotMat[i];
    }
    delete[] rotMat;
    return res;
}

string MatrixEncCrypto::encrypt(string input, map_type) {
    int m = findMinPow(input.length());
    int** mat = makeMat(input, m);
    string res = rotateMat(mat, m);
    for (int i = 0; i < m; ++i) {
        delete[] mat[i];
    }
    delete[] mat;
    return res;
}

string MatrixEncCrypto::decrypt(string input, map_type) {
    string decrypted = encrypt(input);
    int i = input.length() - 1;
    for (; i >= 0; --i) {
        if (decrypted[i] != '=') break;
    }
    return decrypted.substr(0, i + 1);
}

void MatrixEncCrypto::test(string s, map_type) {
    std::cout << "Input: " << s << endl;
    string encrypted = encrypt(s);
    std::cout << "Encrypted: " << encrypted << endl;
    string decrypted = decrypt(encrypted);
    std::cout << "Decrypted: " << decrypted << endl;
    std::cout <<
        "Test: " << (s == decrypted ? "success  " : "failure  ") << endl;
}