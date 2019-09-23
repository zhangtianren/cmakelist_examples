
#include <iostream>
#include "util.h"

void printArray(int data[], int n)
{
    for (int i = 0; i < n; i ++)
    {
        printf("%d ", data[i]);
    }
    printf("\n");
}

void printCheckArray(int data[], int n, bool isIncrease)
{
    bool isCheck = false;
    
    int index = 0;
    printf("%d ", data[0]);
    
    for (int i = 1; i < n; i ++)
    {
        if (data[i] < data[i-1] && isIncrease)
        {
            printf(" ^ ");
            isCheck = true;
            index = i;
        }
        if (data[i] > data[i-1] && !isIncrease)
        {
            printf(" ^ ");
            isCheck = true;
            index = i;
        }
        printf("%d ", data[i]);
    }

    if (isCheck)
    {
        printf("\n error index %d, num %d\n", index, data[index]);
    }
    else
    {
        printf("\n OK\n");
    }
    
}

int checkArray(int data[], int n, bool isIncrease)
{
    if (isIncrease)
    {
        for (int i = 1; i < n; i ++)
        {
            if (data[i] < data[i-1] && isIncrease)
                return i;
            if (data[i] > data[i-1] && !isIncrease)
                return i;
        }
    }
    return 0;
}
