#pragma once
#include <iostream>

inline int cmp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

class MaxThreeIntProducts {
public:
    static void test(int nums[], int len) {
        qsort(nums, len, sizeof(nums[0]), cmp);
        int n1 = nums[len - 3];
        int n2 = nums[len - 2];
        int n3 = nums[len - 1];

        int nLast1 = nums[0];
        int nLast2 = nums[1];

        if (n1 * n2 * n3 > n3 * nLast1 * nLast2) {
            std::cout << "Max product = " << n1 << "*" << n2 << "*" << n3 << " = " << n1 * n2 * n3 << std::endl;
        }
        else {
            std::cout << "Max product = " << nLast1 << "*" << nLast2 << "*" << n3 << " = " << nLast1 * nLast2 * n3 << std::endl;
        }
    }
};
