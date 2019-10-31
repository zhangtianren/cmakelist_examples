
#include "util.h"
#pragma once

// 链实现的 双端队列,带首尾节点
// 普通操作 头进尾出
namespace linkqueue
{
typedef struct LinkQueueNode
{
    ElementType* data;
    LinkQueueNode* next;
    LinkQueueNode* pre;
    LinkQueueNode()
    {
        data = nullptr;
        next = nullptr;
        pre = nullptr;
    }
    LinkQueueNode(ElementType* d)
    {
        data = d;
    }
    void print() {
        if (data) data->print();
    }
}LinkQueueNode;    

typedef struct LinkQueue
{
    LinkQueueNode head;   ///< 队头元素
    LinkQueueNode tail;   ///< 队尾元素
}LinkQueue;   

void init(LinkQueue* pqueue);
void finit(LinkQueue* pqueue);


// 普通操作 头进尾出
void push_front(LinkQueue* pqueue, ElementType* d);
ElementType* pop_back(LinkQueue* pqueue);

// 反常操作 尾进头出
void push_back(LinkQueue* pqueue, ElementType* d);
ElementType* pop_front(LinkQueue* pqueue);


inline void enqueue(LinkQueue* pqueue, ElementType* d){ push_front(pqueue, d); }
inline ElementType* dequeue(LinkQueue* pqueue){return pop_back(pqueue); }

bool isEmpty(LinkQueue* pqueue);
int length(LinkQueue* pqueue);
void print(LinkQueue* pqueue);
}