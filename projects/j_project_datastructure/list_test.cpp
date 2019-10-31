#include "list_test.h"
#include "list.h"


void test_list_linklist()
{
    linklist::LinkList list;
    linklist::init(&list);

    linklist::insert_head(&list, new ElementType(1));
    linklist::insert_head(&list, new ElementType(2));
    linklist::insert_head(&list, new ElementType(3));
    linklist::print(&list);

    linklist::insert_tail(&list, new ElementType(4));
    linklist::insert_tail(&list, new ElementType(5));
    linklist::insert_tail(&list, new ElementType(6));
    linklist::print(&list);

    linklist::insert(&list, 3, new ElementType(7));
    linklist::insert(&list, 3, new ElementType(8));
    linklist::insert(&list, 3, new ElementType(9));
    linklist::print(&list);

    linklist::remove(&list, 2);
    linklist::print(&list);

    ElementType* d = linklist::get(&list, 3);
    if (d)  d->print();

    d = linklist::get(&list, ElementType(7), compElement);
    if (d)  d->print();

    linklist::reverse(&list);
    linklist::print(&list);

    linklist::remove_tail(&list);
    linklist::remove_tail(&list);
    linklist::print(&list);

    linklist::remove_head(&list);
    linklist::print(&list);

    linklist::finit(&list);
    linklist::print(&list);
}
void test_list_twowaylist()
{
    twowaylinklist::TwowayLinkList list;
    twowaylinklist::init(&list);

    twowaylinklist::insert_head(&list, new ElementType(1));
    twowaylinklist::insert_head(&list, new ElementType(2));
    twowaylinklist::insert_head(&list, new ElementType(3));
    twowaylinklist::print(&list);
    twowaylinklist::printReverse(&list);

    twowaylinklist::insert_tail(&list, new ElementType(4));
    twowaylinklist::insert_tail(&list, new ElementType(5));
    twowaylinklist::insert_tail(&list, new ElementType(6));
    twowaylinklist::print(&list);
    twowaylinklist::printReverse(&list);

    twowaylinklist::insert(&list, 3, new ElementType(7));
    twowaylinklist::insert(&list, 3, new ElementType(8));
    twowaylinklist::insert(&list, 3, new ElementType(9));
    twowaylinklist::print(&list);
    twowaylinklist::printReverse(&list);

    twowaylinklist::remove(&list, 2);
    twowaylinklist::print(&list);
    twowaylinklist::printReverse(&list);

    ElementType* d = twowaylinklist::get(&list, 3);
    if (d)  d->print();

    d = twowaylinklist::get(&list, ElementType(7), compElement);
    if (d)  d->print();

    twowaylinklist::reverse(&list);
    twowaylinklist::print(&list);
    twowaylinklist::printReverse(&list);

    twowaylinklist::remove_tail(&list);
    twowaylinklist::remove_tail(&list);
    twowaylinklist::print(&list);
    twowaylinklist::printReverse(&list);

    twowaylinklist::remove_head(&list);
    twowaylinklist::print(&list);
    twowaylinklist::printReverse(&list);

    twowaylinklist::finit(&list);
    twowaylinklist::print(&list);
    twowaylinklist::printReverse(&list);
}
void test_list()
{
    test_list_linklist();
    test_list_twowaylist();

}