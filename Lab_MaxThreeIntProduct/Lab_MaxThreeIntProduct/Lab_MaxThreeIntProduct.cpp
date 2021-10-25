#include <iostream>
using namespace std;

int cmp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void testFindMaxProduct(int nums[], int len) {
    qsort(nums, len, sizeof(nums[0]), cmp);
    int n1 = nums[len-3];
    int n2 = nums[len-2];
    int n3 = nums[len-1];

    int nLast1 = nums[0];
    int nLast2 = nums[1];

    if (n1*n2*n3 > n3*nLast1*nLast2) {
        cout << "Max product = " << n1 << "*" << n2 << "*" << n3 << " = " << n1 * n2 * n3 << endl;
    }
    else {
        cout << "Max product = " << nLast1 << "*" << nLast2 << "*" << n3 << " = " << nLast1 * nLast2 * n3 << endl;
    }

}

int main()
{
    int arr1[] = { 1, 3, 5, 2, 14, -4, 2, 6 };
    int arr2[] = { 4, -6, 2, 7, 1, -7 };
    testFindMaxProduct(arr1, sizeof(arr1) / sizeof(arr1[0]));
    testFindMaxProduct(arr2, sizeof(arr2) / sizeof(arr2[0]));
}
