
#include "util.h"
#pragma once

/**
 * 单向链表
 */
namespace linklist
{
/**
 * 线性表的单向链表节点
 * 单向链表 表头
 */
typedef struct LNode {
    ElementType* data;
    struct LNode* next;
    LNode()
    {
        data = nullptr;
        next = nullptr;
    }

    LNode(ElementType* d)
    {
        data = d;
        next = nullptr;
    }
    void print()
    {
        if (data) data->print();
    }
}LNode, LinkList;

void init(LinkList* plist);
void finit(LinkList* plist);

void insert_head(LinkList* plist, ElementType* d);
void insert_tail(LinkList* plist, ElementType* d);
bool insert(LinkList* plist, int index, ElementType* d);

void remove_head(LinkList* plist);
void remove_tail(LinkList* plist);
bool remove(LinkList* plist, int index);

void reverse(LinkList* plist);

ElementType* get(LinkList* plist, int index);
ElementType* get(LinkList* plist, ElementType key, int (*comp)(const ElementType& a, const ElementType& b));
int length(LinkList* plist);
void print(LinkList* plist);
}

/**
 * 双向链表
 */
namespace twowaylinklist
{
/**
 * 线性表双向链表节点
 * 双向链表 表头
 */
typedef struct Twoway_LNode {
    ElementType* data;
    struct Twoway_LNode* pre;
    struct Twoway_LNode* next;

    Twoway_LNode()
    {
        data = nullptr;
        pre = nullptr;
        next = nullptr;
    }

    Twoway_LNode(ElementType* d)
    {
        data = d;
        pre = nullptr;
        next = nullptr;
    }
    void print()
    {
        if (data) data->print();
    }
}Twoway_LNode, TwowayLinkList;

void init(TwowayLinkList* plist);
void finit(TwowayLinkList* plist);

void _addnode(Twoway_LNode* pfront, Twoway_LNode* pnew);
void _rmnode(Twoway_LNode* pdel);

void insert_head(TwowayLinkList* plist, ElementType* d);
void insert_tail(TwowayLinkList* plist, ElementType* d);
bool insert(TwowayLinkList* plist, int index, ElementType* d);

void remove_head(TwowayLinkList* plist);
void remove_tail(TwowayLinkList* plist);
bool remove(TwowayLinkList* plist, int index);

void reverse(TwowayLinkList* plist);

ElementType* get(TwowayLinkList* plist, int index);
ElementType* get(TwowayLinkList* plist, ElementType key, int (*comp)(const ElementType& a, const ElementType& b));
int length(TwowayLinkList* plist);
bool isEmpty(TwowayLinkList* plist);
void print(TwowayLinkList* plist);
void printReverse(TwowayLinkList* plist);
}
