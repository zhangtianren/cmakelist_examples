
#include "util.h"
#pragma once

namespace sqstack
{

/**
 * 顺序栈
 */
typedef struct SqStack
{
    int maxsize;
    int top;
    ElementType** pData;
}SqStack;

void init(SqStack* pstack, int maxsize);
void finit(SqStack* pstack);

bool isFull(SqStack* pstack);
bool isEmpty(SqStack* pstack);
bool push(SqStack* pstack, ElementType* d);
ElementType* pop(SqStack* pstack);
ElementType* getTop(SqStack* pstack);
void print(SqStack* pstack);
int datasize(SqStack* pstack);
}

namespace listack
{

typedef struct LiStackNode
{
    ElementType* data;
    struct LiStackNode* next;

    LiStackNode()
    {
        data = nullptr;
        next = nullptr;
    }

    LiStackNode(ElementType* d)
    {
        data = d;
        next = nullptr;
    }
    void print()
    {
        if (data) data->print();
    }
}LiStackNode;
/**
 * 链式栈
 */
typedef struct LiStack
{
    //int datasize;
    LiStackNode* top;
}LiStack;

void init(LiStack* pstack);//, int maxsize);
void finit(LiStack* pstack);

//bool isFull(LiStack* pstack);
bool isEmpty(LiStack* pstack);
bool push(LiStack* pstack, ElementType* d);
ElementType* pop(LiStack* pstack);
ElementType* getTop(LiStack* pstack);
void print(LiStack* pstack);
int datasize(LiStack* pstack);

}