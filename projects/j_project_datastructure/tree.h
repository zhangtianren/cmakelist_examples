

#include "util.h"
#include "list.h"
#pragma once

#pragma region data-type-define
typedef struct TreeNode
{
    ElementType* data;
    TreeNode* nextChild;
    TreeNode* nextBrother;
    TreeNode()
    {
        data = nullptr;
        nextBrother = nullptr;
        nextChild = nullptr;
    }
    TreeNode(ElementType* d)
    {
        data = d;
        nextBrother = nullptr;
        nextChild = nullptr;
    }
    void print()
    {
        if (data) data->print();
    }
}TreeNode, Tree;

typedef struct BiTreeNode
{
    ElementType* data;
    BiTreeNode* left;   // 左孩子 or 线索表示的前驱
    BiTreeNode* right;  // 右孩子 or 线索表示的后继

    bool hasleft;       // 是否有左孩子， 没有左孩子 ，就存储前驱
    bool hasright;      // 是否有右孩子， 没有右孩子 ，就存储后继
    BiTreeNode()
    {
        data = nullptr;
        left = nullptr;
        right = nullptr;
        hasleft = false;
        hasright = false;
    }
    BiTreeNode(ElementType* d)
    {
        data = d;
        left = nullptr;
        right = nullptr;
        hasleft = false;
        hasright = false;
    }
    void print()
    {
        if (data) data->print();
    }
}BiTreeNode, BiTree;

typedef struct ElementTypeParentIndex
{
    ElementType* data;
    int parentindex;
}ElementTypeParentIndex;

class ElementType_Bitreenode : public ElementType
{
public:
    BiTreeNode* _node;
    ~ElementType_Bitreenode(){}
    ElementType_Bitreenode(BiTreeNode* node)
    {
        _node = node;
    }
    void print() override
    {
        _node->print();
    }
};

class ElementType_Treenode : public ElementType
{
public:
    TreeNode* _node;
    ~ElementType_Treenode(){}
    ElementType_Treenode(TreeNode* node)
    {
        _node = node;
    }
    void print() override
    {
        _node->print();
    }
};



#pragma endregion

/**
 * 普通树，多子节点，链式存储
 */
namespace tree
{

void init(Tree* ptree);
void finit(Tree* ptree);


/**
 * a -
 * b 0
 * c 0
 * d 0
 * e 1
 * f 3
 * g 3
 * h 3
 * i 4
 * j 4
 * k 6
 */
// 双亲表示法的源数据构造链式树
Tree* build_from_source(ElementTypeParentIndex nodearray[], int num);
// 还原双亲表示法的数据 (奇偶层双队列基本上能cover所有的层次相关的树的问题，属于终极手段，普通问题单队列就搞定)
void build_to_source(Tree* ptree, ElementTypeParentIndex nodearray[], int& num);

// 最大深度
int deep(Tree* ptree);

// 度
int degree(Tree* ptree);

// 叶子数
int leaf_count(Tree* ptree);

// node数 包括root
int node_count(Tree* ptree);

// 层次遍历 输出树元素
void print(Tree* ptree);
typedef struct tag_printbuff
{
    int width;
    int height;
    char* buff;

    tag_printbuff(){ width = 0; height = 0; buff = nullptr;}
    tag_printbuff(const char* str, int length){ 
        height = 1;
        width = length; 
        buff = (char*)malloc(length);
        memcpy(buff, str, length);
    }
    void release()
    {
        width = 0; height = 0;
        if (buff) free(buff);
        buff = nullptr;
    }
    void append_right(tag_printbuff* right)
    {
        if (right->height >= this->height)
        {
            int newwidth = width + right->width;
            char* newbuff = (char*)malloc(newwidth*right->height);
            memset(newbuff, (int)' ', newwidth* right->height);
            for (int i=0;i<right->height;i++)
            {
                if (i < height) memcpy(newbuff + i* newwidth, buff + i* width, width);
                memcpy(newbuff + i* newwidth + width, right->buff + i*right->width, right->width);
            }
            free(buff);
            this->buff = newbuff;
            this->width = width + right->width;
            this->height = right->height;
        }
        else 
        {   
            int newwidth = width + right->width;
            char* newbuff = (char*)malloc(newwidth* height);
            memset(newbuff, (int)' ', newwidth* height);
            for (int i=0;i<height;i++)
            {
                memcpy(newbuff + i* newwidth, buff + i* width, width);
                if (i < right->height) memcpy(newbuff + i* newwidth + width, right->buff + i*right->width, right->width);
            }
            free(buff);
            this->buff = newbuff;
            this->width = width + right->width;
            this->height = height;
        }
        
    }
    void append_up(tag_printbuff* up)
    {
        if (up->width > width)
        {
            printf( "append up fail\n");
        }
        char* newbuff = (char*)malloc((height+up->height)* width);
        memset(newbuff, (int)' ', (height+up->height)* width);
        int upbegin = (width - up->width)/2;
        for (int i=0;i<height;i++)
        {
            memcpy(newbuff + i*width +upbegin, up->buff + i*up->width, up->width);
        }
        for (int i=up->height;i<height+up->height;i++)
        {
            memcpy(newbuff + i*width, buff+(i-up->height)*width, width);
        }
        free(buff);
        this->buff = newbuff;
        this->height = height + up->height;
        this->width = width;
    }
    void printbuff()
    {
        for (int i=0;i<height;i++)
        {
            char temp[1024] = {0};
            memcpy(temp, buff +i*width, width);
            printf("%s\n", temp);
        }
    }
}Print_Buffer;
}

/**
 * 二叉树
 */
namespace bitree
{

void init(BiTree* ptree);
void finit(BiTree* ptree);

// 双亲表示法的源数据构造二叉树
BiTree* build_from_source(ElementTypeParentIndex* nodearray, int num);
// 还原双亲表示法的数据
void build_to_source(BiTree* ptree, ElementTypeParentIndex nodearray[], int& num);

// a b 0 c d 0 0 e 0 f g 0 0 0 0 (0 不含节点)
// 完全二叉树顺序表示方式构造二叉树
BiTree* build_from_source_ex(ElementTypeParentIndex* nodearray, int num);
// 还原二叉树为完全二叉树顺序表示方式
void build_to_source_ex(BiTree* ptree, ElementTypeParentIndex nodearray[], int& num);

void _addleft(BiTree* ptree, ElementType* data);
void _addright(BiTree* ptree, ElementType* data);
void _rmleft(BiTree* ptree);
void _rmright(BiTree* ptree);

// 是否是满二叉树
bool isfull(BiTree* ptree);
// 是否是完全二叉树
bool iscomplete(BiTree* ptree);
// 是否是平衡二叉树
bool isbalance(BiTree* ptree);

// 最大深度
int deep(BiTree* ptree);

// 叶子数
int leaf_count(BiTree* ptree);
void get_leafs(BiTree* ptree, linklist::LinkList* plist);

// node数 包括root
int node_count(BiTree* ptree);

// 遍历_使用递归的方式实现
void traverse_preorder(BiTree* ptree, linklist::LinkList* plist);
void traverse_inorder(BiTree* ptree, linklist::LinkList* plist);
void traverse_postorder(BiTree* ptree, linklist::LinkList* plist);
//void traverse_levelorder(BiTree* ptree, linklist::LinkList* plist);

// 遍历_使用循环、栈、队列的方式实现
void traverse_preorder_ex(BiTree* ptree, linklist::LinkList* plist);
void traverse_inorder_ex(BiTree* ptree, linklist::LinkList* plist);
//void traverse_postorder_ex(BiTree* ptree, linklist::LinkList* plist);
void traverse_levelorder_ex(BiTree* ptree, linklist::LinkList* plist);

// 除了 先序+后序，先序+层序(部分情况下不能唯一确定)， C42-2 = 4 其他的组合都可以试一试
// 先序，中序序列构造二叉树
BiTree* buildtree_with_preorder_inorder(linklist::LinkList* plistpre, linklist::LinkList* plistin);
// 中序，后序序列构造二叉树
BiTree* buildtree_with_inorder_postorder(linklist::LinkList* plistin, linklist::LinkList* plistpost);
// 中序，层序序列构造二叉树
BiTree* buildtree_with_inorder_levelorder(linklist::LinkList* plistin, linklist::LinkList* plistlevel);
// 后序，层序序列构造二叉树
BiTree* buildtree_with_postorder_levelorder(linklist::LinkList* plistpost, linklist::LinkList* plistlevel);

typedef struct threaded_result
{
    BiTree* first;
    BiTree* last;
}Threaded_Result;
// 线索化_先序、中序、后续, 层序遍历线索化,返回线索化之后的（链表）首节点
Threaded_Result threaded_traverse_preorder(BiTree* ptree);
Threaded_Result threaded_traverse_inorder(BiTree* ptree);
Threaded_Result threaded_traverse_postorder(BiTree* ptree);
Threaded_Result threaded_traverse_levelorder(BiTree* ptree);

// 遍历 线索化的树 (线索化之后，找到第一个节点，直接开始使用线索找前驱和后继，不用栈、队列就能完成一次性遍历)
void print_threaded_traverse_preorder(BiTree* ptree, linklist::LinkList* plist);
void print_threaded_traverse_inorder(BiTree* ptree, linklist::LinkList* plist);
void print_threaded_traverse_postorder(BiTree* ptree, linklist::LinkList* plist);
void print_threaded_traverse_levelorder(BiTree* ptree, linklist::LinkList* plist);

// 树型打印
void print(BiTree* ptree);

namespace avl
{
int avl_elementtype_compare(const ElementType& e1, const ElementType& e2);
void _ll_rotate(BiTree* ptree);
void _rr_rotate(BiTree* ptree);
void _rl_rotate(BiTree* ptree);
void _lr_rotate(BiTree* ptree);
BiTreeNode* find(BiTree* ptree, ElementType* key, int (*CompFunc)(const ElementType& e1, const ElementType& e2));
void insert(BiTree* ptree, ElementType* p, int (*CompFunc)(const ElementType& e1, const ElementType& e2));
void remove(BiTree* ptree, BiTreeNode* pnode);
} // namespace avltree

namespace huffman
{
bool ishuffman(BiTree* ptree);
BiTree* build_huffman(ElementType dataarray, int num);
}
}