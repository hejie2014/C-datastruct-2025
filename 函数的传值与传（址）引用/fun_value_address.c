#include <stdio.h>

void Increment(int a);
void IncrementRef(int *a);
int main()
{
    int a = 3;
    Increment(a);
    printf("a = %d\n", a);
    printf("address of variable a in main = %p\n", &a);
    printf("------传引用--------\n");
    IncrementRef(&a);
    printf("a = %d\n", a);
}

void Increment(int a)
{
    a = a + 1;
    printf("address of variable a in increment = %p\n", &a);
}
void IncrementRef(int *a)
{
    *a = *a + 1;
    printf("address of variable a in incrementref = %p\n", a);
}