#include <stdio.h>
// #include <windows.h>
int main()
{
    int a = 5;
    int *p = &a;
    printf("Address of a: %p\n", &a);
    printf("Address of a: %d\n", &a);
    printf("Address of p: %p\n", &p);
    printf("Value of p: %p\n", p);

    printf("Value of a: %d\n", a);
    printf("Value of *p: %d\n", *p);

    *p = 3;
    printf("Value of a: %d\n", a);
    printf("值of a: %d\n", a);
    //   system("pause");
    return 0;
}