#include <iostream>

using namespace std;

// modulov tarberak
int gcd_mod(int a, int b) {
    int rem;
    while ((a % b) > 0) {
        rem = a % b;
        a = b;
        b = rem;
    }
    return b;
}

void sort_two_ints_asc(int& toBeSmall, int& toBeLarge) {
    if (toBeSmall <= toBeLarge) {
        return;
    }
       
    int temp = toBeSmall;
    toBeSmall = toBeLarge;
    toBeLarge = temp;
}

// hanumov tarberak
int gcd_sub(int a, int b) {
    int gr = a;
    int sm = b;
    sort_two_ints_asc(sm, gr);

    do {
        gr -= sm;
        sort_two_ints_asc(sm, gr);
    } while (gr != sm);

    return gr;
}

int lcm(int a, int b) {
    int gcd = gcd_mod(a, b);
    return a * b / gcd;
}

void test(int a, int b) {
    int lcm_ = lcm(a, b);
    int gm = gcd_mod(a, b);
    int gs = gcd_sub(a, b);
    cout << "a = " << a << ", b = " << b << ", lcm = " << lcm_ << ", gcd_mod = " << gm << ", gcd_sub = " << gs << " " << (gm == gs ? "success" : "failure") << endl;
}

int main()
{
    test(10, 15);
    test(15, 10);
    test(1785, 546);
    test(5, 7);
}