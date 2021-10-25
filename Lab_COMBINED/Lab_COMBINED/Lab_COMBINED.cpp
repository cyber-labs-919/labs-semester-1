// Lab_COMBINED.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "maxThreeIntProduct.h"
#include "gcd_lcm.h"

#include "crypto.h"
#include "matrixEnc.h"
#include "substitutionCipher.h"
#include "rle.h"


using namespace std;

int main()
{
    cout << "Max three int products tests:\n\n";
    int arr1[] = { 1, 3, 5, 2, 14, -4, 2, 6 };
    int arr2[] = { 4, -6, 2, 7, 1, -7 };
    MaxThreeIntProducts::test(arr1, sizeof(arr1) / sizeof(arr1[0]));
    MaxThreeIntProducts::test(arr2, sizeof(arr2) / sizeof(arr2[0]));


    cout << "\n\n\nGCD LCM tests:\n\n";
    GCD_LCM::test(10, 15);
    GCD_LCM::test(15, 10);
    GCD_LCM::test(1785, 546);
    GCD_LCM::test(5, 7);

    MatrixEncCrypto matrixCrypto;
    SubstitutionCipherCrypto subCrypto;
    RLECompressor rleCompressor;

    Crypto* c = &matrixCrypto;

    cout << "\n\n\nMatrix crypto tests:\n\n";
    c->test("123456789abcdef");
    cout << endl;
    c->test("Hello friends");
    cout << endl;
    c->test("aabb");
    cout << endl;
    c->test("abcd245145");
    cout << endl;
    c->test("test 1");

    c = &subCrypto;

    cout << "\n\n\nMatrix crypto tests:\n\n";
    c->test("test123", { {"keyFrom", "es2"}, {"keyTo", "fra"} });
    cout << endl;
    c->test("hello, world", { {"keyFrom", "abcdefgh"}, {"keyTo", "qwextyui"} }); // sa chi ashxati vortev sxal tipi key-enq tvel, avelin kbacatrvi warningum
    cout << endl;
    c->test("this is a test message", { {"keyFrom", "abcdef"}, {"keyTo", "fedcba"} });
    cout << endl;

    c = &rleCompressor;

    cout << "\n\n\nRLE tests:\n\n";
    c->test("aa");
    cout << endl;
    c->test("hellooo");
    cout << endl;
    c->test("hello world, this is a message");
    cout << endl;
    c->test("aaaaaabbbbbbbbbbbbbbbbbbbbcdeeeeeeeeefff");
}