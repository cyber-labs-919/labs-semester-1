// DavLab2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

using namespace std;

int findMinPow(int n) {
    int mSize = 1;
    while (mSize * mSize < n) {
        ++mSize;
    }
    return mSize;
}

int** makeMat(string str, int m) {
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

string rotateMat(int** mat, int m) {
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



string crypt(string inp) {
    int m = findMinPow(inp.length());
    int** mat = makeMat(inp, m);
    string res = rotateMat(mat, m);
    for (int i = 0; i < m; ++i) {
        delete[] mat[i];
    }
    delete[] mat;
    return res;
}

string decrypt(string inp) {
    string decrypted = crypt(inp);
    int i = inp.length() - 1;
    for (; i >= 0; --i) {
        if (decrypted[i] != '=') break;
    }
    return decrypted.substr(0, i + 1);
}

void test(string s) {
    std::cout << "Input: " << s << endl;
    string encrypted = crypt(s);
    std::cout << "Encrypted: " << encrypted << endl;
    string decrypted = decrypt(encrypted);
    std::cout << "Decrypted: " << decrypted << endl;
    std::cout <<
        "Test: " << (s == decrypted ? "success  " : "failure  ") << endl;
}

int main()
{
    test("123456789abcdef");
    cout << endl;
    test("Hello friends");
    cout << endl;
    test("aabb");
    cout << endl;
    test("abcd245145");
    cout << endl;
    test("test 1");
}