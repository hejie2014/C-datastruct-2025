#include <stdio.h>

int main()
{
    int x = 5;
    int *p = &x;
    *p = 6;

    int **q = &p;  // 二级指针
    int ***r = &q; // 三级指针
    //  r---->q----->p-->x
    // 打印
    printf("*p = %d\n", *p);          // x的值
    printf("value: p = %p\n", p);     // p的值--> x的地址
    printf("address: &p = %p\n", &p); // p的地址
    printf("*q = %p\n", *q);          //  p的值
    printf("**q = %d\n", **q);        //  x的值
    printf("address: q = %p\n", q);   //  q的值--> p的地址

    printf("*r = %p\n", *r);     //  q的值--> p的地址
    printf("**r = %p\n", **r);   //  p的值--> x的地址
    printf("***r = %d\n", ***r); // x的值

    ***r = 10;
    printf("x = %d\n", x); // 10

    **q = *p + 3;
    printf("x = %d\n", x); // 10 + 3 = 13

    return 0;
}