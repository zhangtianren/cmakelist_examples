

#include "sort.h"
#include "search.h"
#include <iostream>

// https://github.com/hustcc/JS-Sorting-Algorithm

namespace sort
{

void Sort::printArrayRange(int data[], int front, int tail)
{
    for (int i = front; i <= tail; i ++)
    {
        printf("%d ", data[i]);
    }
    printf("\n");
}

void Sort::_switch(int data[], int left, int right)
{
    int temp = data[left];
    data[left] = data[right];
    data[right] = temp;
}


/**
 * 冒泡排序
 */
void Sort::bubble_sort(int data[], int n)
{
    printf("bubble_sort \n");
    int tmp;
    for (int j = 0; j < n; j ++)
    {
        for (int i = 0; i < n-j-1; i ++)
        {
            if (data[i] > data[i+1])
            {
                _switch(data, i, i+1);
            }
        }
    }
    
}


/**
 * 以flag为分界线， 将data[]划分为两个部分，大于flag和小于flag的两部分
 * @return 最终flag的位置
 */
int Sort::_quicksort_partion(int data[], int front, int tail)
{
    //int flag = data[front] + data[tail] + data[(front + tail)/2];
    //int flag = data[front];

    while (front < tail)
    {
        while(data[tail] >= data[front] && tail > front)   tail--;
        _switch(data, front, tail);

        //flag = tail;

        while(data[front] <= data[tail] && tail > front)    front++;
        _switch(data, front, tail);

    }
    return tail;
}

/**
 * 基本思想是分治策略
 */
void Sort::_quicksort(int data[], int front, int tail)
{
    if (front < tail)
    {
        int middle = _quicksort_partion(data, front, tail);

        //printArrayRange(data, front, tail);

        _quicksort(data, front, middle);
        _quicksort(data, middle+1, tail);
    }
}

/**
 * 快速排序
 */
void Sort::quick_sort(int data[], int n)
{
    printf("quick_sort\n");
    _quicksort(data, 0, n-1);
}

/**
 * 直接插入排序
 * 基本思想是：前面一段数据已经基本有序，从后面一段中拿到数据插入到前面已经有序的数据中
 * 1、找到插入的位置
 * 2、移动（也可以在比较中移动）
 */
void Sort::insert_direct_sort(int data[], int n)
{
    printf("insert_direct_sort\n");
    for (int i = 1;i < n; i++)
    {
        for (int j = i;j > 0; j--)
        {
            if (data[j] < data[j-1])
            {
                _switch(data, j-1, j);
            }
            else
            {
                break;
            }
        }
    }
}

/**
 * 折半插入排序
 *  * 基本思想是：前面一段数据已经基本有序，从后面一段中拿到数据插入到前面已经有序的数据中
 * 1、找到插入的位置(前面一段已经有序，可以使用二分搜索的思想，减少比较次数)
 * 2、批量移动
 */
void Sort::insert_binary_sort(int data[], int n)
{
    printf("insert_binary_sort\n");
    for (int i = 1;i < n; i++)
    {
        int pos =search::Search::binary_search(data, 0, i-1, data[i]);
        //printf("at %d find pos %d \n", i, pos);
        if (pos == i)
        {
            continue;
        }
        else
        {
            if (pos > 0)
            {
                int curr = data[i];
                memcpy(data + pos+1, data +pos, (i - pos) * sizeof(int));
                data[pos] = curr;
            }
            else
            {
                pos = 0;
                int curr = data[i];
                memcpy(data + pos+1, data +pos, (i - pos) * sizeof(int));
                data[pos] = curr;
            }
        }
        
        //printArrayRange(data, 0, n-1);
    }
}

/**
 * 希尔排序
 * 插入排序的一种
 * 给定一个步长，以此步长，将原序列划分为多个子序列， 对每个子序列排序(使用直接插入排序)
 * 缩小步长，再次让每个子序列有序
 * 直到步长缩小到1，最终达到完全有序
 */
void Sort::shell_sort(int data[], int n)
{
    printf("shell_sort \n");
    int step = n/2;

    for (int step_inc = step; step_inc >0 ; step_inc = step_inc -2)
    {
        
        for (int i = step_inc;i < n; i++)
        {
            //printf("step %d i %d\n", step_inc, i);
            for (int j = i;j > 0; j= j- step_inc)
            {
                if (data[j] < data[j-step_inc])
                {
                    _switch(data, j-step_inc, j);
                }
                else
                {
                    break;
                }
            }
        }
        printArrayRange(data, 0, n-1);
    }
}

/**
 * 将以top为根的二叉树，调整为大根堆
 */
void Sort::_heapify(int data[], int n, int top)
{
    int left = top*2 +1;
    int right = top*2+2;
    int max = top;

    if (left < n && data[max] < data[left])
    {
        max = left;
    }

    if (right < n && data[max] < data[right])
    {
        max = right;
    }

    if (max != top)
    {
        _switch(data, max, top);
        _heapify(data, n, max);
    }
}

/**
 * 堆排序
 * 将带排序序列看做一个完全二叉树
 * 1、将二叉树调整，使其成为一个大根堆的二叉树（满足所有的根节点元素值小于其子节点元素值）
 * 2、然后将堆顶最大的数 与末尾节点对调，一轮调整完成（最大节点归位到末尾）
 * 3、再将二叉树调整，成为一个大根堆二叉树，与末尾节点（倒数第二个）对调，二轮调整完成。
 * 4、依次循环，直到大根堆最后只有一个节点
 * 利用完全二叉树的性质：
 * 1、每个节点都有两个子节点，
 * 2、根节点序号n 则左子节点序号2*n+1,右子节点序号2*n+2 
 * 3、任意一个节点序号 n / 2 是他的父节点的序号
 */
void Sort::heap_sort(int data[], int n)
{
    printf("heap_sort \n");
    for (int i = n/2 - 1; i >= 0;i--)
    {
        _heapify(data, n, i);
    }
    //printf("max heap is ");
    //printArrayRange(data, 0, n-1);

    for (int j = 0; j < n -1; j++)
    {
        _switch(data, 0, n-j-1);
        _heapify(data, n-j-1, 0);
        //printArrayRange(data, 0, n-1);
    }
}


int _choose_min(int data[], int front, int tail)
{
    int min = data[front];
    for (int i=front+1;i<=tail;i++)
    {
        if (data[i] < tail)
            min = data[i];
    }
    return min;
}

/**
 * 选择排序
 * 每一次序列中选出最小的一个元素，存放在序列的起始位置，
 * 然后，再从剩余未排序元素中继续寻找最小元素，然后放到已排序序列的末尾
 */
void Sort::choose_sort(int data[], int n)
{
    printf("choose_sort \n");
    for (int i =0; i< n; i++)
    {
        int minIndex = i;
        for (int j = i +1;j<n;j++ )
        {
            if(data[j] < data[minIndex])
                minIndex = j;
        }
        _switch(data, i, minIndex);
    }
}

void Sort::_merge(int data[], int buff[],int front_1, int tail_1, int front_2, int tail_2)
{
    int index = 0;
    int startIndex = front_1;
    while(front_1 <= tail_1 && front_2 <= tail_2)
    {
        if (data[front_1] <= data[front_2])
        {
            buff[index] = data[front_1];
            index++;
            front_1++;
        }
        else
        {
            buff[index] = data[front_2];
            index ++;
            front_2++;
        }
    }

    while(front_1 <= tail_1)
    {
        buff[index] = data[front_1];
        index++;
        front_1++;
    }

    while (front_2 <= tail_2)
    {
        buff[index] = data[front_2];
        index ++;
        front_2++;
    }

    memcpy(data + startIndex, buff, index * sizeof(int));
}

/**
 * 分治，划分为更小的规模，然后 merge
 * 当规模足够小（只有两个元素，直接做交换）
 */
void Sort::_merge_sort(int data[],int buff[], int front, int tail)
{
    if (tail - front <= 0)
        return;
    
    if (tail - front == 1)
    {
        if (data[front] > data[tail])
        {
            _switch(data, front, tail);
        }
        return;
    }
    int middle = (front + tail) /2;
    _merge_sort(data, buff, front, middle);
    _merge_sort(data, buff, middle +1, tail);
    _merge(data, buff, front, middle, middle+1, tail);
    //printArrayRange(data, front, tail);
}

/**
 * 核心操作：使用额外的存储空间O(n)，使用存储，将两个已经有序的序列，进行归并。
 * 总体思想：分治策略将待排序序列划分为更小的规模
 */
void Sort::merge_sort(int data[], int n)
{
    if (n <= 1)
        return;
    int* buff = (int*)malloc(sizeof(int) * n);

    int middle = (n-1)/2;
    _merge_sort(data, buff, 0, middle);
    _merge_sort(data, buff, middle+1, n-1);
    _merge(data, buff, 0, middle, middle+1, n-1);

    free(buff);
}


/*
 * 对数组按照"某个位数"进行排序(桶排序)
 *
 * 参数说明：
 *     a -- 数组
 *     n -- 数组长度
 *     exp -- 指数。对数组a按照该指数进行排序。
 *
 * 例如，对于数组a={50, 3, 542, 745, 2014, 154, 63, 616}；
 *    (01) 当exp=1表示按照"个位"对数组a进行排序
 *    (02) 当exp=10表示按照"十位"对数组a进行排序
 *    (03) 当exp=100表示按照"百位"对数组a进行排序
 *    ...
 */
void count_sort(int a[], int n, int exp)
{
    int output[n];             // 存储"被排序数据"的临时数组
    int i, buckets[10] = {0};   

    // 将数据出现的次数存储在buckets[]中
    for (i = 0; i < n; i++)
        buckets[ (a[i]/exp)%10 ]++;  // +9 

    // 更改buckets[i]。目的是让更改后的buckets[i]的值，是该数据在output[]中的位置。
    for (i = 1; i < 10; i++)
        buckets[i] += buckets[i - 1];

    // 将数据存储到临时数组output[]中
    for (i = n - 1; i >= 0; i--)
    {
        output[buckets[ (a[i]/exp)%10 ] - 1] = a[i];
        buckets[ (a[i]/exp)%10 ]--;
    }

    // 将排序好的数据赋值给a[]
    for (i = 0; i < n; i++)
        a[i] = output[i];
}

// 支持负数 @todo
void count_sort_2(int a[], int n, int exp)
{
    int output[n];             // 存储"被排序数据"的临时数组
    int i, buckets[19] = {0};   // 负数和正数  buckets[0]为-9

    // 将数据出现的次数存储在buckets[]中
    for (i = 0; i < n; i++)
        buckets[ (a[i]/exp)%10 ]++;  // +9 

    // 更改buckets[i]。目的是让更改后的buckets[i]的值，是该数据在output[]中的位置。
    for (i = 1; i < 10; i++)
        buckets[i] += buckets[i - 1];

    // 将数据存储到临时数组output[]中
    for (i = n - 1; i >= 0; i--)
    {
        output[buckets[ (a[i]/exp)%10 ] - 1] = a[i];
        buckets[ (a[i]/exp)%10 ]--;
    }

    // 将排序好的数据赋值给a[]
    for (i = 0; i < n; i++)
        a[i] = output[i];
}


/**
 * 基数排序
 * LSD (Least significant digital)基数排序, 用于数值排序，使用桶的方法按照数据键值（mod/10）分桶. **不是基于比较的**
 * MSD（Most significant digital）相反, 由键值的最左边开始
 * 暂不支持负数
 * 
 * 基数下有序
 * （取基数10，则一趟排序完成后，序列个位上是有序的）
 * （再取基数200，则第二趟排序后，在一趟排序的基础上，十位上的数是有序的）
 * （类推，最后一趟，所有数的最高位数目，之后，各个位上的数据的顺序都是有序的，即整体有序）
 */
void Sort::radix_sort(int data[], int n)
{
    int max = data[0];     
    for (int i=0;i<n;i++)
    {
        if (data[i] > max)
            max = data[i];
    }

    for (int exp = 1; max / exp >0; exp = exp *10)
    {
        count_sort(data, n, exp);
    }
    
}
}
