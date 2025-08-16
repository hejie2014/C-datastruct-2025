#include <stdio.h>
#include <string.h.>

void print(const char *string);
int main()
{
    char name[20] = "haha";
    // name[0] = 'h';
    // name[1] = 'a';
    // name[2] = 'h';
    // name[3] = 'a';
    // name[4] = '\0';
    printf("%s\n", name);
    printf("sizeof in bytes = %d\n", sizeof(name)); // 20
    int len = strlen(name);                         // 只计算实际的大小 4
    printf("length = %d\n", len);
    printf("--------------\n");
    char name2[] = "haha";
    printf("sizeof in bytes = %d\n", sizeof(name2)); // 5
    printf("length = %d\n", strlen(name2));          // 只计算实际的大小 4

    printf("----------------\n");
    char string[20] = "hello world!";
    print(string);
    printf("---------字符指针----------------\n");
    // char *c = "hello";
    char c[20] = "hello";
    print(c);
    // c[0] = 'A';
    /*
    char *c = "hello";"hello" 是一个字符串字面量（string literal），存储在内存的只读区域（如 .rodata 段）。
 指针 c 指向这个只读区域的起始地址。
 c[0] = 'A';试图修改只读区域的内容（将 'h' 改为 'A'）。
 由于该内存受操作系统保护，此操作会触发运行时错误（例如在 Linux/Unix 中引发 SIGSEGV 信号，导致段错误）。

    */
    printf("%s", c);
    return 0;
}

void print(const char *string)
{
    //   string[0] = 'A'; // 不合法
    while (*string != '\0')
    {
        printf("%c", *string);
        string++; // 移动到下一个字符
    }
    printf("\n");
}
/*
永远不要修改通过 char *ptr = "literal"; 方式创建的字符串。若需要修改，必须使用字符数组（char[]）或动态内存（malloc）。
1. 字符串字面量的存储位置
"hello" 是字符串字面量，编译器会将其存储在只读内存段（如 .rodata 或文本段），这部分内存受操作系统保护，禁止修改。
2. 指针 c 指向只读内存
char *c = "hello"; 使 c 指向这个只读区域的起始地址。
● 是否崩溃完全取决于 c 指向的内存区域：
  ○ ✅ 可写内存（栈/堆）→ 成功修改并打印
  ○ ❌ 只读内存（字面量）→ 运行时崩溃
*/