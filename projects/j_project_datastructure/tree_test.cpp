#include "tree.h"
#include "tree_test.h"
#include "test.h"



void tree_()
{
    ElementTypeParentIndex nodearrays[10] = 
    { {new ElementType(1), -1} ,  {new ElementType(2), 0} , 
      {new ElementType(3), 0} ,  {new ElementType(4), 0} ,
      {new ElementType(5), 1} ,  {new ElementType(6), 1} ,
      {new ElementType(7), 3} ,  {new ElementType(8), 3} ,
      {new ElementType(9), 3} ,  {new ElementType(10), 5} };
    Tree* tree = tree::build_from_source( nodearrays, 10);

    printf("deep : %d \n", tree::deep(tree));
    printf("degree : %d \n", tree::degree(tree));
    printf("leafes : %d \n", tree::leaf_count(tree));
    printf("nodes : %d \n", tree::node_count(tree));

    tree::print(tree);

    int num = 0;
    ElementTypeParentIndex checkarrays[10];
    tree::build_to_source(tree, checkarrays, num);
}

void test_tree()
{
    //tree_();
    test_bitree();
}


// ElementTypeParentIndex nodearrays_1[5] = 
//     { {new ElementType(1), -1} ,  {new ElementType(2), 0} , 
//       {new ElementType(3), 0} ,  {new ElementType(4), 1} ,  {new ElementType(5), 2} };

ElementTypeParentIndex nodearrays_1[10] = 
    { {new ElementType(1), -1} ,  {new ElementType(2), 0} , 
      {new ElementType(3), 0} ,  {new ElementType(4), 1} ,
      {new ElementType(5), 1} ,  {new ElementType(6), 2} ,
      {new ElementType(7), 2} ,  {new ElementType(8), 3} ,
      {new ElementType(9), 3} ,  {new ElementType(10), 4} };

ElementTypeParentIndex nodearrays_2[16] = 
    { {new ElementType(1), -1} ,  {new ElementType(2), 0} , 
      {new ElementType(3), 0} ,  {new ElementType(4), 1} ,
      {new ElementType(5), 1} ,  {new ElementType(6), 2} ,
      {new ElementType(7), 2} ,  {new ElementType(8), 3} ,
      {new ElementType(9), 3} ,  {new ElementType(10), 4},
      {new ElementType(19), 4} ,  {new ElementType(30), 5} ,
      {new ElementType(49), 5} ,  {new ElementType(66), 6} ,
      {new ElementType(77), 6} ,  {new ElementType(90), 7}  };

ElementTypeParentIndex nodearrays_3[10] = 
    { {new ElementType(1), -1} ,  {new ElementType(2), 0} , 
      {new ElementType(3), 0} ,  {new ElementType(4), 1} ,
      {new ElementType(5), 2} ,  {new ElementType(6), 2} ,
      {new ElementType(7), 3} ,  {new ElementType(8), 3} ,
      {new ElementType(9), 4} ,  {new ElementType(10), 4} };

ElementTypeParentIndex nodearrays_4[15] = 
    { {new ElementType(1), -1} ,  {new ElementType(2), 0} , 
      {new ElementType(3), 0} ,  {new ElementType(4), 1} ,
      {new ElementType(5), 1} ,  {new ElementType(6), 2} ,
      {new ElementType(7), 2} ,  {new ElementType(8), 3} ,
      {new ElementType(9), 3} ,  {new ElementType(28), 4},
      {new ElementType(30), 4} ,  {new ElementType(40), 5} ,
      {new ElementType(41), 5} ,  {new ElementType(66), 6} ,
      {new ElementType(88), 6}  };

ElementTypeParentIndex nodearrays_5[10] = 
    { {new ElementType(1), -1} ,  {new ElementType(2), 0} , 
      {new ElementType(3), 1} ,  {new ElementType(4), 2} ,
      {new ElementType(5), 2} ,  {new ElementType(6), 3} ,
      {new ElementType(7), 4} ,  {new ElementType(8), 5} ,
      {new ElementType(9), 6} ,  {new ElementType(10), 6} };

ElementTypeParentIndex nodearrays_6[10] = 
    { {new ElementType(1), -1} ,  {new ElementType(2), 0} , 
      {new ElementType(3), 0} ,  {new ElementType(4), 1} ,
      {new ElementType(5), 1} ,  {new ElementType(6), 2} ,
      {new ElementType(7), 2} ,  {new ElementType(8), 3} ,
      {new ElementType(9), 3} ,  {new ElementType(10), 4} };

void _bitree(ElementTypeParentIndex* nodearrays, int n)
{
    BiTree* tree = bitree::build_from_source( nodearrays, n);

    int num = 0;
    ElementTypeParentIndex checkarrays[64];
    bitree::build_to_source(tree, checkarrays, num);

    bitree::print(tree);

    printf("deep        : %d \n", bitree::deep(tree));
    printf("leafes      : %d \n", bitree::leaf_count(tree));
    printf("nodes       : %d \n", bitree::node_count(tree));
    printf("isbalance   : %s \n", bitree::isbalance(tree) ? "true" : "false");
    printf("isfull      : %s \n", bitree::isfull(tree) ? "true" : "false");
    printf("iscomplete  : %s \n", bitree::iscomplete(tree) ? "true" : "false");

    linklist::LinkList listpre,listin,listpost,listlevel;
    linklist::init(&listpre);
    linklist::init(&listin);
    linklist::init(&listpost);
    linklist::init(&listlevel);
    bitree::traverse_preorder(tree, &listpre);
    bitree::traverse_inorder(tree, &listin);
    bitree::traverse_postorder(tree, &listpost);
    //bitree::traverse_levelorder()

    printf("traverse -- pre in post - :\n");
    printf("pre   : "); linklist::print(&listpre);
    printf("in    : "); linklist::print(&listin);
    printf("post  : "); linklist::print(&listpost);

    linklist::finit(&listpre);
    linklist::finit(&listin);
    linklist::finit(&listpost);
    linklist::finit(&listlevel);

    bitree::traverse_preorder_ex(tree, &listpre);
    bitree::traverse_inorder_ex(tree, &listin);
    //bitree::traverse_postorder_ex(tree, &listpost);
    bitree::traverse_levelorder_ex(tree, &listlevel);

    printf("traverse_ex -- pre in - level :\n");
    printf("pre   : "); linklist::print(&listpre);
    printf("in    : "); linklist::print(&listin);
    //linklist::print(&listpost);
    printf("level : "); linklist::print(&listlevel);
    
    linklist::finit(&listpre);
    linklist::finit(&listin);
    linklist::finit(&listpost);
    linklist::finit(&listlevel);

    bitree::threaded_traverse_preorder(tree);
    bitree::print_threaded_traverse_preorder(tree, &listpre);
    
    bitree::threaded_traverse_inorder(tree);
    bitree::print_threaded_traverse_inorder(tree, &listin);

    // bitree::threaded_traverse_postorder(tree);
    // bitree::print_threaded_traverse_postorder(tree, &listpost);

    // bitree::threaded_traverse_levelorder(tree);
    // bitree::print_threaded_traverse_levelorder(tree, &listlevel);

    printf("threaded -- pre in post level :\n");
    printf("pre   : "); linklist::print(&listpre);
    printf("in    : "); linklist::print(&listin);
    printf("post  : "); linklist::print(&listpost);
    printf("level : "); linklist::print(&listlevel);

    linklist::finit(&listpre);
    linklist::finit(&listin);
    linklist::finit(&listpost);
    linklist::finit(&listlevel);

    bitree::finit(tree);
}
void test_bitree()
{
    // printf ("--size %d /n", sizeof(nodearrays_1) / sizeof (ElementTypeParentIndex));
    _bitree(nodearrays_1, sizeof(nodearrays_1) / sizeof (ElementTypeParentIndex));//10);
    _bitree(nodearrays_2, sizeof(nodearrays_2) / sizeof (ElementTypeParentIndex));//16);
    _bitree(nodearrays_3, sizeof(nodearrays_3) / sizeof (ElementTypeParentIndex));//10);
    _bitree(nodearrays_4, sizeof(nodearrays_4) / sizeof (ElementTypeParentIndex));//15);
    _bitree(nodearrays_5, sizeof(nodearrays_5) / sizeof (ElementTypeParentIndex));//10);
    _bitree(nodearrays_6, sizeof(nodearrays_6) / sizeof (ElementTypeParentIndex));//10);
    
}

void test_avltree()
{

}

void test_huffmanbitree()
{

}