#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int compare(const void *a, const void *b)
{
    int A = *((int *)a); // 先将void指针转换为int指针，再解引用
    int B = *((int *)b);
    return B - A; // 降序排列
}
int absolute_compare(const void *a, const void *b)
{
    return abs(*((int *)b)) - abs(*((int *)a));
}
int main()
{
    int A[] = {-31, 22, -1, 50, -6, 4}; // 排序的结果应为{-1,4，-6,22，-31,50}
    qsort(A, 6, sizeof(int), absolute_compare);
    for (int i = 0; i < 6; i++)
    {
        printf("%d ", A[i]);
    }

    return 0;
}

/*qsort函数是C标准库中提供的一个通用排序函数，它使用快速排序算法（或者可能根据实现使用其他排序算法）来实现排序。但是，标准并没有规定必须使用快速排序，因此不同的库实现可能不同。不过，快速排序是最常见的实现方式。
qsort的函数原型如下：
```c
void qsort(void *base, size_t nmemb, size_t size,
           int (*compar)(const void *, const void *));
```
参数说明：
- `base`: 指向要排序数组的第一个元素的指针（即数组的起始地址）。
- `nmemb`: 数组中元素的个数。
- `size`: 每个元素的大小（以字节为单位）。
- `compar`: 比较函数的指针，该函数用于比较两个元素的大小。
### 实现原理
虽然具体的实现可能不同，但快速排序的基本思想是分治法（Divide and Conquer）：
1. 选择一个基准元素（pivot）。
2. 将数组分成两部分，使得左边的元素都小于等于基准，右边的元素都大于等于基准。
3. 递归地对左右两部分进行排序。
### 实现步骤（以快速排序为例）
1. **选择基准（pivot）**：通常可以选择第一个元素、最后一个元素、中间元素或随机元素。
2. **分区（Partition）**：重新排列数组，使得所有小于基准的元素放在基准前面，大于基准的放在后面。分区完成后，基准处于数组的中间位置。
3. **递归**：递归地将小于基准的子数组和大于基准的子数组排序。
### 伪代码（快速排序）
```
function quicksort(array, left, right):
    if left < right then
        pivot_index = partition(array, left, right)
        quicksort(array, left, pivot_index - 1)
        quicksort(array, pivot_index + 1, right)
function partition(array, left, right):
    pivot = array[right]  // 选择最后一个元素作为基准
    i = left - 1
    for j = left to right - 1:
        if array[j] <= pivot then
            i = i + 1
            swap array[i] and array[j]
    swap array[i+1] and array[right]
    return i + 1
```
### qsort的通用性
由于qsort可以排序任何类型的数组，它通过以下方式实现通用性：
- 使用`void*`指针来指向数组，这样任何类型的数据都可以被指向。
- 用户提供比较函数，该函数知道如何比较两个元素。比较函数接收两个`const void*`参数，返回一个整数（负数表示第一个参数小于第二个，正数表示大于，0表示相等）。
- 元素的大小（`size`）被提供给qsort，以便在交换元素或移动指针时能够正确计算地址。
### 交换元素
在排序过程中，当需要交换两个元素时，由于不知道元素的具体类型，qsort会通过逐字节交换来实现。例如，交换两个元素（每个元素的大小为`size`字节）的代码可能如下：
```c
void swap(void *a, void *b, size_t size) {
    char *p = a, *q = b, tmp;
    for (size_t i = 0; i < size; i++) {
        tmp = p[i];
        p[i] = q[i];
        q[i] = tmp;
    }
}
```
### 递归与非递归
为了避免递归深度过大（最坏情况会导致栈溢出），一些实现可能会使用栈来模拟递归（非递归实现），或者当递归到小的子数组时切换到插入排序（混合排序策略）。
### 优化
实际的qsort实现可能会包含多种优化，例如：
- 选择中位数作为基准（median-of-three）以避免最坏情况。
- 当子数组较小时（比如元素个数小于10），使用插入排序，因为插入排序在小数组上效率更高。
- 使用循环代替递归来减少函数调用开销。
### 示例：一个简化的qsort实现
下面是一个简化的qsort实现（使用快速排序）：
```c
#include <stddef.h>  // for size_t
static void swap(void *a, void *b, size_t size) {
    char *p = a, *q = b;
    while (size--) {
        char tmp = *p;
        *p++ = *q;
        *q++ = tmp;
    }
}
static void quicksort(void *base, size_t nmemb, size_t size,
                      int (*compar)(const void *, const void *),
                      int left, int right) {
    if (left >= right) return;
    char *arr = base;
    // 选择最后一个元素作为基准
    void *pivot = arr + right * size;
    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (compar(arr + j * size, pivot) <= 0) {
            i++;
            swap(arr + i * size, arr + j * size, size);
        }
    }
    swap(arr + (i+1)*size, pivot, size);
    int pivot_index = i+1;
    quicksort(base, nmemb, size, compar, left, pivot_index-1);
    quicksort(base, nmemb, size, compar, pivot_index+1, right);
}
void qsort(void *base, size_t nmemb, size_t size,
           int (*compar)(const void *, const void *)) {
    if (nmemb <= 1) return;
    quicksort(base, nmemb, size, compar, 0, nmemb-1);
}
```
注意：上述代码没有包含优化（如小数组使用插入排序、非递归等），并且最坏情况下时间复杂度为O(n^2)。实际库实现会更加复杂和高效。
### 总结
qsort函数通过通用指针和用户提供的比较函数实现了对任意类型数组的排序。其核心算法通常是快速排序，但会包含多种优化以提高性能和避免最坏情况。理解qsort的关键在于理解快速排序算法以及如何通过字节操作来处理任意类型的数据。*/

/*
在比较函数中，返回值的意义是告诉排序算法两个元素的相对顺序。具体来说：
   - 如果比较函数返回负数，表示第一个参数应该排在第二个参数前面（即第一个参数“小于”第二个参数）
   - 如果返回正数，表示第一个参数应该排在第二个参数后面（即第一个参数“大于”第二个参数）
   - 如果返回0，表示两个元素相等，顺序可以任意
因此，当我们定义比较函数时：
1. 升序排列（从小到大）：
   - 当a>b时，我们返回正数，这样a会被排在b的后面（因为a大于b，我们希望大的在后面）
   - 当a<b时，返回负数，这样a会被排在b的前面（因为a小于b，我们希望小的在前面）
   - 所以：return a - b;   (当a和b是数字时)
2. 降序排列（从大到小）：
   - 当a>b时，我们返回负数，这样a会被排在b的前面（因为a大于b，我们希望大的在前面）
   - 当a<b时，返回正数，这样a会被排在b的后面（因为a小于b，我们希望小的在后面）
   - 所以：return b - a;   (当a和b是数字时)
注意：这里a和b是指向数组中两个元素的指针，在比较函数内部我们需要将它们转换成正确的类型，然后进行比较。
示例：
  升序比较函数（整数）：
    int compare_asc(const void *a, const void *b) {
        int int_a = *((int*)a);
        int int_b = *((int*)b);
        return int_a - int_b;   // 升序
    }
  降序比较函数（整数）：
    int compare_desc(const void *a, const void *b) {
        int int_a = *((int*)a);
        int int_b = *((int*)b);
        return int_b - int_a;   // 降序
    }
为什么这样设计？
  排序算法在比较两个元素时，会根据比较函数的返回值来决定是否交换它们的位置。标准规定：
    返回值 < 0  -> a在b之前
    返回值 > 0  -> a在b之后
    返回值 == 0 -> 顺序不变
  因此，在升序中，我们希望当a小于b时，a在b前面（即返回负值），当a大于b时，a在b后面（返回正值）。所以用a-b就自然满足：
      a < b -> a-b < 0 -> a排在b前面（正确）
      a > b -> a-b > 0 -> a排在b后面（正确）
  降序则反过来，用b-a：
      a > b -> b-a < 0 -> 此时在比较函数中，a是第一个参数，b是第二个参数，返回负值意味着a应该排在b前面（因为a大，我们希望它在前面）
      a < b -> b-a > 0 -> 返回正值，a应该排在b后面（正确）
注意：如果使用浮点数，直接相减可能会因为精度问题导致错误，而且相减可能超出整数范围。所以更安全的做法是：
  升序：
      if (a > b) return 1;
      if (a < b) return -1;
      return 0;
  降序：
      if (a < b) return 1;
      if (a > b) return -1;
      return 0;
或者使用条件表达式：
  升序：return (a > b) ? 1 : (a < b) ? -1 : 0;
  降序：return (a < b) ? 1 : (a > b) ? -1 : 0;

*/