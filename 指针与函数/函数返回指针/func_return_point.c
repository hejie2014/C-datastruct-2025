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

// 这个警告信息是编译器在提示你：函数返回了一个局部变量的地址。在C/C++中，局部变量（也称为自动变量）存储在栈上，当函数执行结束时，这些局部变量所占用的内存会被自动回收。因此，返回一个指向局部变量的指针是危险的，因为一旦函数返回，该指针就指向了一个无效的内存地址（悬垂指针），后续使用这个指针会导致未定义行为（通常是程序崩溃或数据错误）。
//  让我们通过一个具体的例子来解释：
//  示例代码：
//  ```c
//  #include <stdio.h>
//  int* foo() {
//      int c = 10;   // c是局部变量，存储在栈上
//      return &c;    // 返回c的地址
//  }
//  int main() {
//      int* p = foo(); // p现在指向一个已经不存在的局部变量
//      printf("%d\n", *p); // 未定义行为：访问已释放的栈内存
//      return 0;
//  }
