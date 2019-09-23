#pragma once 

namespace sort
{
/**
 * 
 * 1、基于比较和交换的排序：
 *  冒泡排序
 *  快速排序
 * 
 * 2、基于插入的排序
 *  直接插入排序、折半插入排序
 *  希尔排序
 * 
 * 3、基于堆的排序
 * 
 */
class Sort
{

    public:

    static void printArrayRange(int data[], int front, int tail);

    static void _switch(int data[], int left, int right);

    /**
     * 冒泡排序
     */
    static void bubble_sort(int data[], int n);


    static int _quicksort_partion(int data[], int front, int tail);
    static void _quicksort(int data[], int front, int tail);
    /**
     * 快速排序
     */
    static void quick_sort(int data[], int n);

    /**
     * 直接插入排序
     * 
     */
    static void insert_direct_sort(int data[], int n);

    /**
     * 折半插入排序
     */
    static void insert_binary_sort(int data[], int n);

    /**
     * 希尔排序
     */
    static void shell_sort(int data[], int n);

    static void _heapify(int data[], int n, int top);
    /**
     * 堆排序
     */
    static void heap_sort(int data[], int n);

    /**
     * 选择排序
     */
    static void choose_sort(int data[], int n);


    static void _merge(int data[], int buff[],int front_1, int tail_1, int front_2, int tail_2);
    static void _merge_sort(int data[], int buff[],int front, int tail);
    /**
     * 归并排序
     */
    static void merge_sort(int data[], int n);


    /**
     * 基数排序
     */
    static void radix_sort(int data[], int n);
};

}