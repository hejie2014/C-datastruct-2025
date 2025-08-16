#include <stdio.h.>

int sumOfElement(int a[], int size);
int sumOfElementPtr(int *a, int size);
int sumOfElement2(int a[]);
int main()
{
    int a[] = {1, 3, 4, 4, 5};
    int size = sizeof(a) / sizeof(a[0]);
    int total = sumOfElement(a, size);
    printf("sum of element = %d\n", total);
    printf("--------使用指针的方式--------\n");

    // 数组作为函数参数，会退化成指针，在其内部不要使用sizeof,因为是指针的大小，固定不变8(64),4(32)字节
    int total2 = sumOfElementPtr(a, size); // 数组作为函数参数，会退化成指针，在其内部不要使用sizeof
    printf("sum of element = %d\n", total2);
    // 在函数内部使用sizeof
    printf("--------sizeof-------\n");
    int total3 = sumOfElement2(a);
    printf("sum of element = %d\n", total3); // 4(1 + 3)
    return 0;
}

int sumOfElement(int a[], int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += a[i];
    }
    return sum;
}
// 在函数内部使用sizeof
int sumOfElement2(int a[])
{
    int sum = 0;
    int size = sizeof(a) / sizeof(a[0]);
    printf("sizeof(a) = %zu\n", sizeof(a));
    printf("sizeof(a[0]) = %zu\n", sizeof(a[0]));
    for (int i = 0; i < size; i++)
    {
        sum += a[i];
    }
    return sum;
}
int sumOfElementPtr(int *a, int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += a[i];
    }
    return sum;
}