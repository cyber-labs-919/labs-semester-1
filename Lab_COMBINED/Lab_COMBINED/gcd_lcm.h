#pragma once
#include <iostream>

class GCD_LCM {
public:
    static int gcd_mod(int a, int b) {
        int rem;
        while ((a % b) > 0) {
            rem = a % b;
            a = b;
            b = rem;
        }
        return b;
    }

    static void sort_two_ints_asc(int& toBeSmall, int& toBeLarge) {
        if (toBeSmall <= toBeLarge) {
            return;
        }

        int temp = toBeSmall;
        toBeSmall = toBeLarge;
        toBeLarge = temp;
    }

    // hanumov tarberak
    static int gcd_sub(int a, int b) {
        int gr = a;
        int sm = b;
        sort_two_ints_asc(sm, gr);

        do {
            gr -= sm;
            sort_two_ints_asc(sm, gr);
        } while (gr != sm);

        return gr;
    }

    static int lcm(int a, int b) {
        int gcd = gcd_mod(a, b);
        return a * b / gcd;
    }

    static void test(int a, int b) {
        int lcm_ = lcm(a, b);
        int gm = gcd_mod(a, b);
        int gs = gcd_sub(a, b);
        std::cout << "a = " << a << ", b = " << b << ", lcm = " << lcm_ << ", gcd_mod = " << gm << ", gcd_sub = " << gs << " " << (gm == gs ? "success" : "failure") << std::endl;
    }
};