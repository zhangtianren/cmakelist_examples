#include "list.h"

namespace linklist
{
void init(LinkList* plist)
{
    plist->next = nullptr;
}
void finit(LinkList* plist)
{
    LNode* pnext = plist->next;
    while (pnext)
    {
        plist->next = plist->next->next;
        delete pnext;
        pnext = plist->next;
    }
    plist->next = nullptr;
}

void insert_head(LinkList* plist, ElementType* d)
{
    LNode* pnode = new LNode(d);
    pnode->next = plist->next;
    plist->next = pnode;
}
void insert_tail(LinkList* plist, ElementType* d)
{
    LNode* pnode = new LNode(d);
    LNode* last = plist;
    while(last->next)
    {
        last = last->next;
    }
    last->next = pnode;
}
bool insert(LinkList* plist, int index, ElementType* d)
{
    if (index < 0)
        return false;
    LNode* pnode = plist;
    for (int i=0;i<index; i++)
    {
        if (pnode == nullptr)
            return false;
        
        pnode = pnode->next;
    }
    
    if (pnode == nullptr)
        return false;
    
    LNode* newnode = new LNode(d);
    newnode->next = pnode->next;
    pnode->next = newnode;
}

void remove_head(LinkList* plist)
{
    if (plist->next)
    {
        LNode* pnext = plist->next;
        plist->next = pnext->next;
        delete pnext;
    }
}
void remove_tail(LinkList* plist)
{
    LNode* pprelast = plist->next;
    if (pprelast == nullptr)
        return;
    if (pprelast->next == nullptr)
    {
        delete (pprelast->next);
        pprelast->next = nullptr;
        return;
    }

    while( pprelast->next && pprelast->next->next)
    {
        pprelast = pprelast->next;
    }
    delete (pprelast->next);
    pprelast->next = nullptr;
}

bool remove(LinkList* plist, int index)
{
    if (index < 0)
        return false;
    LNode* pnode = plist;
    for (int i=0;i<index; i++)
    {
        if (pnode == nullptr)
            return false;
        
        pnode = pnode->next;
    }
    
    if (pnode == nullptr)
        return false;
    
    LNode* rmnode = pnode->next;
    pnode->next = pnode->next->next;
    delete rmnode;
}

void reverse(LinkList* plist){}

ElementType* get(LinkList* plist, int index)
{
    if (index < 0)
        return false;
    LNode* pnode = plist;
    for (int i=0;i<index; i++)
    {
        if (pnode == nullptr)
            return nullptr;
        
        pnode = pnode->next;
    }
    
    return pnode->data;
}
ElementType* get(LinkList* plist, ElementType key, int (*comp)(const ElementType& a, const ElementType& b))
{
    LNode* pnext = plist->next;
    while (pnext)
    {
        if ( 0 == comp(key, *(pnext->data)))
            return pnext->data;
        pnext = pnext->next;
    }
    return nullptr;
}
int length(LinkList* plist)
{
    int count = 0;
    LNode* pnext = plist->next;
    while (pnext)
    {
        count++;
        pnext = pnext->next;
    }
    return count;
}
bool isEmpty(LinkList* plist)
{
    return plist->next == nullptr;
}
void print(LinkList* plist)
{
    LNode* pnext = plist->next;
    while (pnext)
    {
        pnext->print();
        pnext = pnext->next;
    }
    printf("\n");
}
}

namespace twowaylinklist
{
void init(TwowayLinkList* plist)
{
    plist->pre = plist;
    plist->next = plist;
}
void finit(TwowayLinkList* plist)
{
    Twoway_LNode* pnext = plist->next;
    while (pnext != plist)
    {
        printf("rm %d->%d(0x%08x->0x%08x)\n", pnext->pre->data ? pnext->pre->data->key : 0, pnext->data ? pnext->data->key : 0, pnext->pre, pnext);

        plist->next = pnext->next;
        delete pnext;
        pnext = plist->next;
    }
    plist->pre = plist;
    plist->next = plist;
    
    // while (!isEmpty(plist))
    // {
    //     remove_head(plist);
    // }
}

void _addnode(Twoway_LNode* pfront, Twoway_LNode* pnew)
{
    if (pfront->next)
    {
        pfront->next->pre = pnew;
    }

    pnew->pre = pfront;
    pnew->next = pfront->next;

    pfront->next = pnew;
    printf("add %d->%d(0x%08x->0x%08x)\n", pfront->data ? pfront->data->key : 0, pnew->data ? pnew->data->key : 0, pfront, pnew);
}

void _rmnode(Twoway_LNode* pdel)
{
    printf("rm %d->%d(0x%08x->0x%08x)\n", pdel->pre->data ? pdel->pre->data->key : 0, pdel->data ? pdel->data->key : 0, pdel->pre, pdel);

    if (pdel->pre)
    {
        pdel->pre->next = pdel->next;
    }

    if (pdel->next)
    {
        pdel->next->pre = pdel->pre;
    }
}

void insert_head(TwowayLinkList* plist, ElementType* d)
{
    Twoway_LNode* pnode = new Twoway_LNode(d);
    _addnode(plist, pnode);
}
void insert_tail(TwowayLinkList* plist, ElementType* d)
{
    Twoway_LNode* pnode = new Twoway_LNode(d);
    Twoway_LNode* last = plist;
    while(last->next != plist)
    {
        last = last->next;
    }
    _addnode(last, pnode);
}
bool insert(TwowayLinkList* plist, int index, ElementType* d)
{
    if (index < 0)
        return false;
    Twoway_LNode* pnode = plist->next;
    for (int i=1;i<index; i++)
    {
        if (pnode == plist)
            return false;
        
        pnode = pnode->next;
    }
    
    Twoway_LNode* newnode = new Twoway_LNode(d);
    _addnode(pnode, newnode);
    return true;
}

void remove_head(TwowayLinkList* plist)
{
    Twoway_LNode* pnode = plist->next;
    if (pnode != plist)
    {
        _rmnode(pnode);
        delete pnode;
    }
}
void remove_tail(TwowayLinkList* plist)
{
    
    // Twoway_LNode* pprelast = plist->next;
    // if (pprelast == plist)
    //     return;

    // while( pprelast->next != plist)
    // {
    //     pprelast = pprelast->next;
    // }
    // _rmnode(pprelast);
    // delete pprelast;
    Twoway_LNode* plast = plist->pre;
    if (plast != plist)
    {
        _rmnode(plast);
        delete plast;
    }
    
}

bool remove(TwowayLinkList* plist, int index)
{
    if (index < 0)
        return false;
    Twoway_LNode* pnode = plist->next;
    for (int i=1;i<index; i++)
    {
        if (pnode == plist)
            return false;
        
        pnode = pnode->next;
    }
    
    if (pnode == plist)
        return false;
    
    _rmnode(pnode);
    delete pnode;
}

void reverse(TwowayLinkList* plist)
{
    Twoway_LNode* pnode = plist->next;

    plist->next = plist->pre;
    plist->pre = pnode;

    while (pnode != plist)
    {
        Twoway_LNode* pnext = pnode->next;
        
        pnode->next = pnode->pre;
        pnode->pre = pnext;

        pnode = pnext;
    }
}

ElementType* get(TwowayLinkList* plist, int index)
{
    if (index < 0)
        return nullptr;
    Twoway_LNode* pnode = plist->next;
    for (int i=1;i<index; i++)
    {
        if (pnode == plist)
            return nullptr;
        
        pnode = pnode->next;
    }
    
    return pnode->data;
}
ElementType* get(TwowayLinkList* plist, ElementType key, int (*comp)(const ElementType& a, const ElementType& b))
{
    Twoway_LNode* pnext = plist->next;
    while (pnext != plist)
    {
        if ( 0 == comp(key, *(pnext->data)))
            return pnext->data;
        pnext = pnext->next;
    }
    return nullptr;
}
int length(TwowayLinkList* plist)
{
    int count = 0;
    Twoway_LNode* pnext = plist->next;
    while (pnext != plist)
    {
        count++;
        pnext = pnext->next;
    }
    return count;
}
bool isEmpty(TwowayLinkList* plist)
{
    return plist->next == plist;
}
void print(TwowayLinkList* plist)
{
    Twoway_LNode* pnext = plist->next;
    while (pnext != plist)
    {
        //printf("0x%04x:", pnext);
        printf("=>", pnext);
        pnext->print();
        pnext = pnext->next;
    }
    printf("\n");
}

void printReverse(TwowayLinkList* plist)
{
    Twoway_LNode* ppre = plist->pre;
    while (ppre != plist)
    {
        //printf("0x%04x:", ppre);
        printf("<=", ppre);
        ppre->print();
        ppre = ppre->pre;
    }
    printf("\n");
}
}