#include <stdio.h>
#include <stdlib.h>

int main()
{
    // void *p = malloc(3 * sizeof(int)); void * 类型指针不能进行解引用
    int *p = malloc(3 * sizeof(int));

    // 判断内存是否分配成功
    if (p == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }
    printf("--------malloc未初始化-----------\n");
    printf("%d %d %d\n", p[0], p[1], p[2]);
    *p = 2;
    *(p + 1) = 3;
    p[2] = 4; // *p,*(P + 1),*(p + 2)等价于p[0],p[1],p[2]
    printf("---------malloc初始化----------\n");
    printf("%d %d %d\n", p[0], p[1], p[2]);
    // 释放动态分配的内存
    free(p);
    // 将指针置为 NULL
    p = NULL;
    printf("-------------------\n");
    printf("Enter size of array: ");
    int number;
    scanf("%d", &number);
    int *arr = (int *)malloc(number * sizeof(int));
    for (int i = 0; i < number; i++)
    {
        arr[i] = i + 1;
    }
    // free(arr);
    // arr = NULL; // 释放内存后，不能再使用 arr 指针，否则会导致未定义行为
    for (int i = 0; i < number; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    // 释放动态分配的内存
    free(arr);
    arr = NULL;
    return 0;
}
