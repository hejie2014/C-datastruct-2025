#include <stdio.h>
#include <math.h>
int compare(int a, int b)
{
    if (a > b)
        return -1; // 降序
    else
        return 1;
}
// 绝对值比较函数
int absolute_compare(int a, int b)
{
    return abs(a) - abs(b);
}
void BubbleSort(int *A, int n, int (*compare)(int, int))
{                                   // int (*compare)(int, int) 函数指针
    for (int i = 0; i < n - 1; i++) // 外层循环控制一共需要排序N次
    {
        for (int j = 0; j < n - 1 - i; j++) // 内层循环，每次排完序，数据就可以不再比较
        {
            if (compare(A[j], A[j + 1]) > 0) // 核心逻辑
            {
                int temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int A[] = {3, 2, 1, 5, 6, 4};
    BubbleSort(A, 6, compare);
    for (int i = 0; i < 6; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n--------abs-------\n");
    int B[] = {-31, 22, -1, 50, -6, 4}; // 排序的结果应为{-1,4，-6,22，-31,50}
    BubbleSort(B, 6, absolute_compare);
    for (int i = 0; i < 6; i++)
    {
        printf("%d ", B[i]);
    }

    return 0;
}