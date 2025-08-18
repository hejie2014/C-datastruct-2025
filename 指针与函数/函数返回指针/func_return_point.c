#include <stdio.h>
#include <stdlib.h>

int add(int a, int b) // called function(被调函数)
{                     // 按值传递
    printf("Address of a in add = %p\n", &a);
    printf("Address of b in add = %p\n", &b);
    int c = a + b;
    return c;
}
int addRef(int *a, int *b) // called function(被调函数)
{                          // 传引用
    printf("Address of a in add = %p\n", a);
    // printf("Address of b in add = %p\n", b);
    int c = *a + *b;
    return c;
}
int *addPtr(int *a, int *b) // called function(被调函数)
{                           // 传引用
    // 在heap上分配一块内存
    int *c = malloc(sizeof(int));
    *c = *a + *b;
    return c;
}
int main() // calling function(主调函数)
{
    int a = 2, b = 3;
    printf("Address of a in main = %p\n", &a);
    // printf("Address of b in main = %p\n", &b);
    // int c = add(a, b);
    // int c = addRef(&a, &b);
    int *ptr = addPtr(&a, &b);
    printf("Sum = %d\n", *ptr);
    free(ptr); // 释放内存
    /*
    现在这个 ptr 指针不能指向其他地方，要不然无法再堆上释放内存
    要指向其他地方，必须将 ptr 指针复制一份备用。
    打印完成后 ，写free(ptr)；就释放了.
    */
    return 0;
}