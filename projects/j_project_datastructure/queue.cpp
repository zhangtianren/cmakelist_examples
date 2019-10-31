
#include "queue.h"

namespace linkqueue
{

void init(LinkQueue* pqueue)
{
    pqueue->head.next = &pqueue->tail;
    pqueue->head.pre = nullptr;

    pqueue->tail.next = nullptr;
    pqueue->tail.pre = &pqueue->head;
}
void finit(LinkQueue* pqueue)
{
    while(! isEmpty(pqueue))
    {
        pop_front(pqueue);
    }
}

// 普通操作 头进尾出
void push_front(LinkQueue* pqueue, ElementType* d)
{
    LinkQueueNode* front = new LinkQueueNode(d);
    front->pre = &pqueue->head;
    front->next = pqueue->head.next;

    pqueue->head.next->pre = front;
    pqueue->head.next = front;
}
ElementType* pop_back(LinkQueue* pqueue)
{
    if (isEmpty(pqueue))
        return nullptr;
    
    LinkQueueNode* back = pqueue->tail.pre;
    back->pre->next = &pqueue->tail;
    pqueue->tail.pre = back->pre;

    ElementType* res = back->data;
    delete back;
    return res;
}

// 反常操作 尾进头出
void push_back(LinkQueue* pqueue, ElementType* d)
{
    LinkQueueNode* back = new LinkQueueNode(d);
    back->next = &pqueue->tail;
    back->pre = pqueue->tail.pre;

    pqueue->tail.pre->next = back;
    pqueue->tail.pre = back;
}
ElementType* pop_front(LinkQueue* pqueue)
{
    if (isEmpty(pqueue))
        return nullptr;

    LinkQueueNode* front = pqueue->head.next;
    pqueue->head.next = front->next;
    front->next->pre = &pqueue->head;

    ElementType* res = front->data;
    delete front;
    return res;
}

bool isEmpty(LinkQueue* pqueue)
{
    if (pqueue->head.next == &pqueue->tail || pqueue->tail.pre == &pqueue->head)
        return true;
    return false;

}
int length(LinkQueue* pqueue)
{
    int length = 0;
    LinkQueueNode* node = (&pqueue->head)->next;
    while (node != &pqueue->tail)
    {
        node = node->next;
        length++;
    }
}
void print(LinkQueue* pqueue)
{
    LinkQueueNode* node = (&pqueue->head)->next;
    while (node != &pqueue->tail)
    {
        node->print();
        printf("=>");
        node = node->next;
    }
    printf("\n");
}

}