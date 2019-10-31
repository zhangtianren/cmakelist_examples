
#include "stack.h"

namespace sqstack
{

void init(SqStack* pstack, int maxsize)
{
    if (maxsize <= 0)
        return;
    
    pstack->pData       = new ElementType*[maxsize];
    pstack->top         = 0;
    pstack->maxsize     = maxsize;
}
void finit(SqStack* pstack)
{
    if (pstack->pData)
    {
        delete pstack->pData; 
    }
    pstack->pData       = nullptr;
    pstack->top         = 0;
    pstack->maxsize     = 0;
}

bool isFull(SqStack* pstack)
{
    return (pstack->top == pstack->maxsize - 1); 
}
bool isEmpty(SqStack* pstack)
{
    return pstack->top == 0;
}
bool push(SqStack* pstack, ElementType* d)
{
    if (isFull(pstack))
        return false;
    pstack->pData[pstack->top++] = d;
}
ElementType* pop(SqStack* pstack)
{
    if (isEmpty(pstack))
        return nullptr;
    
    return pstack->pData[--pstack->top];
}
ElementType* getTop(SqStack* pstack)
{
    if (isEmpty(pstack))
        return nullptr;
    
    return pstack->pData[pstack->top -1];
}
void print(SqStack* pstack)
{
    // printf("maxsize: %d, top: %d. isEmpty: %d, isFull: %d\n",
    //     pstack->maxsize, pstack->top, isEmpty(pstack), isFull(pstack));

    for (int i = pstack->top-1;i>=0;i--)
    {
        printf("=>");
        pstack->pData[i]->print();
    }
    printf("\n");
}
int datasize(SqStack* pstack)
{
    return pstack->top;
}

}

namespace listack
{
void init(LiStack* pstack)
{
    //pstack->datasize = 0;
    pstack->top = nullptr;
}

void finit(LiStack* pstack)
{
    LiStackNode* nodetop = pstack->top;
    while ( nodetop != nullptr)
    {
        pstack->top = nodetop->next;
        delete nodetop;
        nodetop = pstack->top;
    }
    //pstack->datasize = 0;
}

//bool isFull(LiStack* pstack);
bool isEmpty(LiStack* pstack)
{
    return pstack->top == nullptr;
}

bool push(LiStack* pstack, ElementType* d)
{
    LiStackNode* pnode = new LiStackNode(d);
    pnode->next = pstack->top;
    pstack->top = pnode;
    return true;
}
ElementType* pop(LiStack* pstack)
{
    if (isEmpty(pstack))
    {
        printf("warning pop empty stack\n");
        return nullptr;
    }
    LiStackNode* pnode = pstack->top;
    ElementType* res = pnode->data;
    pstack->top = pstack->top->next;
    delete pnode;

    return res;
}
ElementType* getTop(LiStack* pstack)
{
    if (isEmpty(pstack))
    {
        return nullptr;
    }
    LiStackNode* pnode = pstack->top;
    return pnode->data;
}
void print(LiStack* pstack)
{
    //printf("stack size: %d, isEmpty: %d\n", datasize(pstack), isEmpty(pstack));
    LiStackNode* pnode = pstack->top;
    while (pnode!= nullptr)
    {
        printf("=>");
        pnode->print();
        pnode = pnode->next;
    }
    printf("=>\n");
}

int datasize(LiStack* pstack)
{
    int size = 0;
    LiStackNode* pnode = pstack->top;
    while (pnode!= nullptr)
    {
        size++;
        pnode = pnode->next;
    }
    return size;
}

}