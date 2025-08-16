#include <stdio.h>

int main()
{
    int A[] = {2, 4, 3, 5, 6};
    // 数组名是数组的首地址
    int *p = A; // p指向数组A的首元素
    // A++;事实上是A是指针只不过他是一个常量指针常量指针的地址不可以被修改的，例如A=A+1就是不合理的，但是printf中返回的A+i是地址的四则运算并没有改变A自身的地址所以可以
    for (int i = 0; i < sizeof(A) / sizeof(A[0]); i++)
    {
        printf("address: A[%d] = %p\n", i, &A[i]);
        printf("address: A + %d = %p\n", i, A + i);
        printf("address: p + %d = %p\n", i, p + i);

        printf("value: A[%d] = %d\n", i, A[i]);
        printf("value: *(A + %d) = %d\n", i, *(A + i));
        printf("value: *(p + %d) = %d\n", i, *(p + i));
    }

    return 0;
}