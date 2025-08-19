#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int compare(const void *a, const void *b)
{
    int A = *((int *)a); // 先将void指针转换为int指针，再解引用
    int B = *((int *)b);
    return B - A; // 降序排列
}
int absolute_compare(const void *a, const void *b)
{
    return abs(*((int *)b)) - abs(*((int *)a));
}
int main()
{
    int A[] = {-31, 22, -1, 50, -6, 4}; // 排序的结果应为{-1,4，-6,22，-31,50}
    qsort(A, 6, sizeof(int), absolute_compare);
    for (int i = 0; i < 6; i++)
    {
        printf("%d ", A[i]);
    }

    return 0;
}