#include <stdio.h>

int main()
{
    int a = 1025;
    int *p;
    p = &a;
    printf("size of integer is %d bytes.\n", sizeof(int));
    printf("address = %p, value = %d\n", p, *p);
    printf("address = %p, value = %d\n", p + 1, *(p + 1));
    // typecasting,类型转换，导致精度丢失
    char *p0;
    p0 = (char *)p;

    printf("size of integer is %d bytes.\n", sizeof(char));
    printf("address = %p, value = %d\n", p0, *p0);
    printf("address = %p, value = %d\n", p0 + 1, *(p0 + 1));

    return 0;
}