#include <stdio.h>
#include <stdlib.h>

int add(int a, int b)
{
    return a + b;
}
int *sub(int *a, int *b)
{
    // 在堆上分配一块内存
    int *c = malloc(sizeof(int));
    *c = *a - *b;
    return c; // 返回指向结果的指针
}
void printHello(char *name)
{
    printf("Hello, %s\n", name);
}
void test()
{
    // 两种初始化方式
    int (*p1)(int, int) = add;
    int (*p2)(int, int) = &add;
    // 两种调用方式
    printf("p1(2,3) = %d\n", p1(2, 3));
    printf("p2(2,3) = %d\n", p2(2, 3));
    printf("(*p1)(2,3) = %d\n", (*p1)(2, 3));
    printf("(*p2)(2,3) = %d\n", (*p2)(2, 3));
    // 验证地址
    printf("add = %p\n", add);
    printf("&add = %p\n", &add);
    printf("p1 = %p\n", (void *)p1);
    printf("p2 = %p\n", (void *)p2);
}
// int *Func(int, int); // 这是声明一个函数，该函数返回一个指向整数的指针
int main()
{
    int result = 0;
    int (*p)(int, int) = add; // 定义函数指针 p，指向 add 函数

    // result = (*p)(2, 3); // 通过函数指针调用 add 函数
    //  也可以使用指针名调用函数
    result = p(2, 3); // 通过函数指针调用 add 函数
    printf("result = %d\n", result);

    int a = 5, b = 3;
    int *(*ptr)(int *, int *) = sub; // 定义函数指针 ptr，指向 sub 函数
    // ptr(&a, &b)为指针，这部分会造成内存泄漏，详见注释部分
    printf("sub result = %d\n", *(ptr(&a, &b))); // 通过函数指针调用 sub 函数并打印结果
    free(ptr(&a, &b));                           // 释放动态分配的内存
    /*
         printf("sub result = %d\n", *ptr(&a, &b));   // 这里调用一次，打印结果
     free(ptr(&a, &b));                           // 这里又调用了一次，但返回的是另一个新分配的指针
    这样写会有两个问题：
    1. 两次调用`sub`函数，分配两次内存，第一次分配的内存没有释放，内存泄漏。
    2. 两次调用的结果虽然理论上相同（因为a,b没变），但两次分配的内存地址不同，而且第二次分配的内存我们释放了，第一次的没释放。
    所以，我们强烈建议使用临时变量来保存结果。
    但是，我们也可以这样写（不推荐，因为两次调用可能有副作用，这里虽然没有，但分配两次内存且只释放一次，会漏掉一次）：
        // 不推荐：因为分配了两次内存，只释放一次
        printf("sub result = %d\n", *ptr(&a, &b));   // 第一次调用，分配内存A，打印后没有释放
        free(ptr(&a, &b));                           // 第二次调用，分配内存B，然后释放了B
    这样，内存A就泄漏了。
    因此，我们选择使用临时变量来保存指针，然后打印并释放。
    // 修改后（避免两次调用）：
     int *res = ptr(&a, &b);
     printf("sub result = %d\n", *res);
     free(res);
    这样，我们只调用了一次`sub`函数，分配了一次内存，然后打印并释放。
    */

    void (*ptr2)(char *) = printHello; // 定义函数指针 ptr，指向 printHello 函数
    char *name = "dfdfdfd";
    ptr2(name); // 通过函数指针调用 printHello 函数
    test();
    return 0;
}
/*
我们来看一下代码中的问题。错误提示是：`error: passing argument 1 of 'free' makes pointer from integer without a cast [-Wint-conversion]`，发生在`free(*ptr(&a, &b));`这一行。
 首先，我们分析一下`free(*ptr(&a, &b))`的执行步骤：
 1. `ptr`是一个函数指针，指向`sub`函数。
 2. `ptr(&a, &b)`调用了`sub`函数，该函数返回一个`int*`，即指向整数的指针（假设这个指针为`c`）。
 3. 然后，我们使用`*`操作符解引用这个指针，即`*(ptr(&a, &b))`，得到的是指针所指向的整数值（即`*c`，一个整数）。
 4. 最后，将这个整数值传递给`free`函数。但是`free`函数要求参数是一个`void*`指针，而这里我们传递的是一个整数（int），因此编译器报错。
 正确的做法是：我们不应该解引用返回的指针，而是直接将指针传递给`free`函数。因为`free`需要释放的是之前由`malloc`分配的内存块，我们需要传递的是内存块的起始地址（指针），而不是这个地址上存储的整数值。
 所以，应该修改为：
     free(ptr(&a, &b));   // 直接传递指针，而不是解引用
 但是注意，`ptr(&a, &b)`返回的指针正是`sub`函数中分配的内存地址，我们直接将它传给`free`即可。
 另外，我们还需要注意：在`sub`函数中，我们分配了一块内存，并将结果存储在那里，然后返回该指针。在`main`函数中，我们通过函数指针`ptr`调用`sub`函数，得到返回的指针。然后我们使用这个指针做了两件事：
  1. 解引用它，打印出结果。
  2. 释放它。
 但是，在`printf`语句中，我们使用了`*(*ptr)(&a, &b)`，这相当于：
     第一步：调用函数：`ptr(&a, &b)` 返回一个指针，假设为`res`（类型是`int*`）。
     第二步：然后解引用：`*res`，得到整数。
     第三步：打印这个整数。
 而在`free`的时候，我们不应该解引用，因为我们需要的是指针（即`res`），而不是整数（`*res`）。
 因此，修改后的代码应该是：
     printf("sub result = %d\n", *ptr(&a, &b));   // 这里使用*解引用得到整数，用于打印
     free(ptr(&a, &b));                           // 这里直接传递指针给free
 但是注意，上面的两行代码中，我们调用了两次`ptr(&a, &b)`，也就是调用了两次`sub`函数。这意味着我们分配了两块内存，一次在打印时，一次在释放时。然而，我们只释放了第二次分配的内存，第一次分配的内存没有释放，造成了内存泄漏。
 所以，更好的做法是只调用一次`sub`函数，将返回的指针保存起来，然后使用它来打印，再释放。
 修改后的main函数相关部分：
     int *result_ptr = ptr(&a, &b);   // 调用一次，保存指针
     printf("sub result = %d\n", *result_ptr);
     free(result_ptr);
 但是，原代码中为了展示函数指针的使用，可能更倾向于直接调用。为了避免两次调用，我们可以先调用一次，将结果保存，然后使用。
 不过，原代码中已经有一次调用用于打印，然后紧接着又调用一次用于释放。这样不仅效率低，而且有内存泄漏（第一次调用分配的内存没有释放）。
 因此，我们调整如下：
     // 修改前：
     // printf("sub result = %d\n", *(*ptr)(&a, &b));
     // free(*ptr(&a, &b));
     // 修改后（避免两次调用）：
     int *res = ptr(&a, &b);
     printf("sub result = %d\n", *res);
     free(res);
 这样，我们只调用了一次`sub`函数，分配了一次内存，然后打印并释放。
 但是，如果为了保持原代码的风格（即不引入临时变量），我们可以这样做：
     // 先打印，然后释放同一块内存
     int *temp = ptr(&a, &b);
     printf("sub result = %d\n", *temp);
     free(temp);
 或者，如果我们不想引入临时变量，也可以这样写（但可读性稍差）：
     printf("sub result = %d\n", *ptr(&a, &b));   // 这里调用一次，打印结果
     free(ptr(&a, &b));                           // 这里又调用了一次，但返回的是另一个新分配的指针
 这样写会有两个问题：
  1. 两次调用`sub`函数，分配两次内存，第一次分配的内存没有释放，内存泄漏。
  2. 两次调用的结果虽然理论上相同（因为a,b没变），但两次分配的内存地址不同，而且第二次分配的内存我们释放了，第一次的没释放。
 所以，我们强烈建议使用临时变量来保存结果。
 但是，我们也可以这样写（不推荐，因为两次调用可能有副作用，这里虽然没有，但分配两次内存且只释放一次，会漏掉一次）：
     // 不推荐：因为分配了两次内存，只释放一次
     printf("sub result = %d\n", *ptr(&a, &b));   // 第一次调用，分配内存A，打印后没有释放
     free(ptr(&a, &b));                           // 第二次调用，分配内存B，然后释放了B
 这样，内存A就泄漏了。
 因此，我们选择使用临时变量来保存指针，然后打印并释放。
 所以，修改后的main函数为：
int main()
{
    int result = 0;
    int (*p)(int, int) = add; // 定义函数指针 p，指向 add 函数
    result = p(2, 3); // 通过函数指针调用 add 函数
    printf("result = %d\n", result);
    int a = 5, b = 3;
    int *(*ptr)(int *, int *) = sub;
    // 调用sub函数，将返回的指针保存
    int *sub_result = ptr(&a, &b);
    printf("sub result = %d\n", *sub_result); // 打印结果
    free(sub_result);                         // 释放内存
    return 0;
}
 这样修改后，就不会有编译错误，也不会有内存泄漏。
 但是，原代码中有一行注释：`// ptr(&a, &b)`，下面我们使用了`*(*ptr)(&a, &b)`，现在我们已经修改了。
 另外，原代码中`printf`语句中使用了`*(*ptr)(&a, &b)`，这实际上等价于`* ( (*ptr)(&a, &b) )`，即先调用函数，然后解引用。我们修改为`*sub_result`，效果一样。

*/