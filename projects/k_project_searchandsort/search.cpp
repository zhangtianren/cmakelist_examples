

#include "search.h"
#include <iostream>

namespace search
{
/**
 * 二分搜索, 给定的序列已经有序，折半查找，找到num 在序列中的位置
 * 如果 小于data[front] 返回front-1，大于data[tail] 返回 tail+1
 */
int Search::binary_search(int data[], int front, int tail, int num)
{
    //printf("binary_search from %d to %d \n", front, tail);

    if (data[front] > num)
        return front-1;
    if ( data[tail] < num)
        return tail +1;
    
    if (front == tail -1 || front == tail)
        return tail;

    int middle = (front + tail) / 2;
    if ( data[middle] == num)
    {
        return middle;
    }
    else if (data[middle] > num)
    {
        return binary_search(data, front, middle-1, num);
    }
    else {
        return binary_search(data, middle, tail, num);
    }
   
}

} // namespace search
