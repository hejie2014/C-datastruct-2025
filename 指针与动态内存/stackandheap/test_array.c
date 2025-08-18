#include <stdio.h>
#include <stdlib.h>

int main()
{

    int rows = 0, cols = 0;
    printf("Enter number of rows and columns: ");
    scanf("%d %d", &rows, &cols);
    // 分配内存
    int **A = malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
    {
        A[i] = malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++)
        {
            A[i][j] = (i * cols) + (j + 1);
        }
    }
    // 打印数组
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("A[%d][%d] = %-6d", i, j, A[i][j]);
        }
        printf("\n");
    }
    // 释放内存
    for (int i = 0; i < rows; i++)
    {
        free(A[i]);
        A[i] = NULL;
    }
    free(A);
    A = NULL;
    return 0;
}
/*
#include <stdio.h>
#include <stdlib.h>
int main() {
    int rows = 3, cols = 4;
    int **array;
    int i, j;
    // 分配行指针数组
    array = (int **)malloc(rows * sizeof(int *));
    if (array == NULL) {
        fprintf(stderr, "内存分配失败\n");
        return 1;
    }
    // 分配一个连续的内存块，包含所有元素
    array[0] = (int *)malloc(rows * cols * sizeof(int));
    if (array[0] == NULL) {
        fprintf(stderr, "内存分配失败\n");
        free(array); // 释放之前分配的行指针数组
        return 1;
    }
    // 将行指针指向连续内存块中的对应位置
    for (i = 1; i < rows; i++) {
        array[i] = array[0] + i * cols;
    }
    // 初始化数组
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            array[i][j] = i * cols + j;
        }
    }
    // 打印数组
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
    // 释放内存：先释放元素数组，再释放行指针数组
    free(array[0]);
    free(array);
    return 0;
}

*/
/*
### 方法2：分配一个指针数组，然后为每一行独立分配内存（行可以不等长，内存不连续）
 步骤：
 1. 分配一个指针数组（第一维）。
 2. 为每一行分配内存（第二维）。
 代码示例：
#include <stdio.h>
#include <stdlib.h>
int main() {
    int rows = 3, cols = 4;
    int **array;
    int i, j;
    // 分配行指针数组
    array = (int **)malloc(rows * sizeof(int *));
    if (array == NULL) {
        fprintf(stderr, "内存分配失败\n");
        return 1;
    }
    // 为每一行分配内存
    for (i = 0; i < rows; i++) {
        array[i] = (int *)malloc(cols * sizeof(int));
        if (array[i] == NULL) {
            fprintf(stderr, "内存分配失败\n");
            // 释放之前已分配的行
            for (int k = 0; k < i; k++) {
                free(array[k]);
            }
            free(array);
            return 1;
        }
    }
    // 初始化数组
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            array[i][j] = i * cols + j;
        }
    }
    // 打印数组
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
    // 释放内存：先释放每一行，再释放行指针数组
    for (i = 0; i < rows; i++) {
        free(array[i]);
    }
    free(array);
    return 0;
}
*/
/*
- **方法1**（连续内存）：
  - 优点：内存连续，缓存友好；只需两次`malloc`和两次`free`。
  - 缺点：每行长度必须相等（即矩形数组）。
- **方法2**（非连续内存）：
  - 优点：可以创建不等长的行（锯齿数组）；分配更灵活。
  - 缺点：内存不连续，可能影响性能；需要多次分配和释放。
*/