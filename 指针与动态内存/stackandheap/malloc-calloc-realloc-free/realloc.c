#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n = 0;
    printf("Enter size of array: ");
    scanf("%d", &n);
    // 分配动态内存
    int *p = malloc(n * sizeof(int));
    // 内存是否分配成功
    if (p == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }
    // 初始化数组
    for (int i = 0; i < n; i++)
    {
        p[i] = i + 1;
    }
    // 重新分配内存
    /*
      int *B = realloc(p, 0); 相当于free(p)
      int *B = realloc(NULL, n * sizeof(int));相当于malloc
      因此，如果传入的参数恰当，realloc可以作为malloc与free的替代。
    */
    // int *newPtr = realloc(p, n * 2 * sizeof(int));
    int *newPtr = realloc(p, (n / 2) * sizeof(int));
    printf("Prev block address = %p, new address = %p\n", p, newPtr);
    // 打印数组
    printf("------p块数据----------\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", p[i]);
    }
    printf("\n------newPtr数据----------\n");
    for (int i = 0; i < 2 * n; i++)
    {
        printf("%d ", newPtr[i]);
    }
    printf("\n");

    // 释放动态分配的内存
    free(p);
    free(newPtr);
    p = NULL;
    newPtr = NULL;

    return 0;
}