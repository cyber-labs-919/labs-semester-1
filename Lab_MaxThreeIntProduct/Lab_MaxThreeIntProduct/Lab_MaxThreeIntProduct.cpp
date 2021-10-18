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
    cout << "Max product = " << n1 << "*" << n2 << "*" << n3 << " = " << n1 * n2 * n3 << endl;
}

int main()
{
    int arr1[] = { 1, 3, 5, 2, 14, -4, 2, 6 };
    int arr2[] = { 4, 2, 7, 1 };
    testFindMaxProduct(arr1, sizeof(arr1) / sizeof(arr1[0]));
    testFindMaxProduct(arr2, sizeof(arr2) / sizeof(arr2[0]));
}
