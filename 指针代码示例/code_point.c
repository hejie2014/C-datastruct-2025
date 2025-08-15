#include <stdio.h>

int main()
{
    int a = 10;
    int *p = &a;

    printf("Address p is %p\n", p);
    printf("Value at address p is %d\n", *p);

    printf("size of integer is %d bytes.\n", sizeof(int));

    printf("address p+1 is %p\n", p + 1);
    printf("Value at address p+1 is %d\n", *(p + 1));

    return 0;
}