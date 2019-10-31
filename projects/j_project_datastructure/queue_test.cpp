

#include "queue_test.h"
#include "queue.h"
#include "test.h"


void test_queue()
{

    linkqueue::LinkQueue queue;
    linkqueue::init(&queue);

    linkqueue::push_front(&queue, new ElementType(1));
    linkqueue::push_front(&queue, new ElementType(2));
    linkqueue::push_front(&queue, new ElementType(3));
    linkqueue::print(&queue);

    linkqueue::push_back(&queue, new ElementType(4));
    linkqueue::push_back(&queue, new ElementType(5));
    linkqueue::push_back(&queue, new ElementType(6));
    linkqueue::print(&queue);

    linkqueue::push_front(&queue, new ElementType(10));
    linkqueue::push_front(&queue, new ElementType(20));
    linkqueue::push_front(&queue, new ElementType(30));
    linkqueue::print(&queue);

    ElementType* d;
    d = linkqueue::pop_back(&queue);
    if (d)  d->print();
    printf("\n");
    linkqueue::print(&queue);

    d = linkqueue::pop_front(&queue);
    if (d)  d->print();
    printf("\n");

    linkqueue::print(&queue);

    linkqueue::pop_back(&queue);
    linkqueue::pop_back(&queue);
    linkqueue::print(&queue);
    linkqueue::pop_front(&queue);

    linkqueue::pop_front(&queue);
    linkqueue::print(&queue);

    linkqueue::finit(&queue);
    linkqueue::print(&queue);

}