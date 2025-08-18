#include <stdio.h>
#include <stdlib.h>

int main()
{

    int rows = 0, cols = 0, hight = 0;
    printf("Enter number of rows and columns and hight: ");
    scanf("%d %d %d", &rows, &cols, &hight);
    // 分配内存
    int ***A = malloc(hight * sizeof(int **));
    for (int i = 0; i < hight; i++)
    {
        A[i] = malloc(rows * sizeof(int *));
        for (int j = 0; j < rows; j++)
        {
            A[i][j] = malloc(cols * sizeof(int));
            for (int k = 0; k < cols; k++)
            {
                A[i][j][k] = (i * (rows * cols)) + (j * cols) + (k + 1);
            }
        }
    }
    // 打印数组
    for (int i = 0; i < hight; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            for (int k = 0; k < cols; k++)
            {
                printf("A[%d][%d][%d] = %-6d", i, j, k, A[i][j][k]);
            }
        }
        printf("\n");
    }
    // 释放内存
    for (int i = 0; i < hight; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            free(A[i][j]);
            A[i][j] = NULL;
        }
        free(A[i]);
        A[i] = NULL;
    }
    free(A);
    A = NULL;
    return 0;
}

// 方法 1：分配连续内存块（单次分配）这种方法分配一个连续的内存块，然后设置指针结构来访问不同维度：
/*
#include <stdlib.h>
int main() {
    int x = 2, y = 3, z = 4; // 维度：2x3x4
    // 分配连续内存块（所有元素）
    int *data = (int *)malloc(x * y * z * sizeof(int));
    // 分配第一维指针数组（x 个 int**）
    int ***array3D = (int ***)malloc(x * sizeof(int **));
    // 分配第二维指针数组（x*y 个 int*）
    for (int i = 0; i < x; i++) {
        array3D[i] = (int **)malloc(y * sizeof(int *));
    }
    // 设置第三维指针指向连续内存中的正确位置
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            // 计算偏移量：i*(y*z) + j*z
            array3D[i][j] = data + (i * y * z) + (j * z);
        }
    }
    // 使用数组（示例）
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            for (int k = 0; k < z; k++) {
                array3D[i][j][k] = i * 100 + j * 10 + k; // 赋值
            }
        }
    }
    // 释放内存
    free(data);            // 先释放数据块
    for (int i = 0; i < x; i++) {
        free(array3D[i]);  // 释放第二维指针
    }
    free(array3D);         // 释放第一维指针
    return 0;
}

*/
/*
#include <stdio.h>
#include <stdlib.h>
int main() {
    int x = 2, y = 3, z = 4;

    // 分配连续内存
    int *data = malloc(x * y * z * sizeof(int));

    // 创建访问结构
    int (*array)[y][z] = (int (*)[y][z])data;

    // 使用标准数组语法
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            for (int k = 0; k < z; k++) {
                array[i][j][k] = i * 100 + j * 10 + k;
                printf("array[%d][%d][%d] = %d\n", i, j, k, array[i][j][k]);
            }
        }
    }
    free(data);
    return 0;
}

*/