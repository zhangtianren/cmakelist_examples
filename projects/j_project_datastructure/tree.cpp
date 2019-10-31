#include "tree.h"
#include "list.h"
#include "stack.h"
#include "queue.h"
#include "string.h"

namespace tree
{
void init(Tree* ptree)
{
    ptree->data = nullptr;
    ptree->nextChild = nullptr;
    ptree->nextBrother = nullptr;
}
void finit(Tree* ptree)
{
    if (ptree == nullptr)
        return;
    Tree* root = ptree;
    int index = 0;
    linkqueue::LinkQueue queue;
    linkqueue::init(&queue);
    linkqueue::enqueue(&queue, new ElementType(index++, ptree));

    while(!linkqueue::isEmpty(&queue))
    {
        ElementType* treedata = linkqueue::dequeue(&queue);
        Tree* node = (Tree*)(treedata->data);
        if (node->nextChild != nullptr)
            linkqueue::enqueue(&queue, new ElementType(index++, node->nextChild));
        if (node->nextBrother != nullptr)
            linkqueue::enqueue(&queue, new ElementType(index++, node->nextBrother));
        if (node != root)
            delete node;
        
        delete treedata;
    }
    init(root);
}

// 双亲表示法的源数据构造链式树
Tree* build_from_source(ElementTypeParentIndex nodearray[], int num)
{
    Tree** nodes = new Tree*[num];

    for (int i = 0; i < num; i++)
    {
        nodes[i] = new Tree(nodearray[i].data);
    }

    for (int i = 0; i < num;i++)
    {
        if (nodearray[i].parentindex < 0 || nodearray[i].parentindex >= num)
            continue;

        Tree* n = nodes[nodearray[i].parentindex];
        if (n->nextChild == nullptr)
        {
            n->nextChild = nodes[i];
        }
        else
        {
            n = n->nextChild;
            while(n->nextBrother != nullptr)
            {
                n = n->nextBrother;
            }
            n->nextBrother = nodes[i];
        }
    }
    Tree* root = nodes[0];
    delete nodes;
    return root;
}

// 还原双亲表示法的数据
void build_to_source(Tree* ptree, ElementTypeParentIndex nodearray[], int& num)
{
    if (ptree == nullptr)
        return;

    int indexEnqueue = 0;
    int indexDequeue = 0;
    linkqueue::LinkQueue queue;
    linkqueue::init(&queue);
    linkqueue::enqueue(&queue, new ElementType(indexEnqueue++, ptree));

    nodearray[indexEnqueue-1].data =  ptree->data;
    nodearray[indexEnqueue-1].parentindex = -1;

    while(!linkqueue::isEmpty(&queue))
    {
        indexDequeue++;
        ElementType* treedata = linkqueue::dequeue(&queue);
        Tree* node = (Tree*)(treedata->data);

        if (node->nextChild != nullptr)
        {
            linkqueue::enqueue(&queue, new ElementType(indexEnqueue++, node->nextChild));
            nodearray[indexEnqueue-1].data =  node->nextChild->data;
            nodearray[indexEnqueue-1].parentindex = indexDequeue-1;

            Tree* child = node->nextChild;
            while (child->nextBrother != nullptr)
            {
                child = child->nextBrother;
                linkqueue::enqueue(&queue, new ElementType(indexEnqueue++, child));
                nodearray[indexEnqueue-1].data =  child->data;
                nodearray[indexEnqueue-1].parentindex = indexDequeue-1;
            }
        }
        delete treedata;
    }
    num = indexEnqueue;
    
    printf("tree to source array (%d) :\n", num);
    for (int i=0;i<num;i++)
    {
        printf(" %d:", i);
        nodearray[i].data->print();
        printf(" p(%d)\n", nodearray[i].parentindex);
    }
}

// 最大深度
int deep(Tree* ptree)
{
    Tree* subtree = ptree->nextChild;
    if (subtree == nullptr)
        return 1;

    int maxdeep = deep(subtree);
    while(subtree->nextBrother)
    {
        subtree = subtree->nextBrother;
        int d = deep(subtree);
        maxdeep = maxdeep < d ? d : maxdeep;
    }
    return maxdeep + 1;
}

// 度 (某个子树的最大子节点数)
int degree(Tree* ptree)
{
    Tree* subtree = ptree->nextChild;
    if (subtree == nullptr)
        return 0;

    int current_degree = 1;
    int max_degree = degree(subtree);
    while(subtree->nextBrother)
    {
        current_degree++;
        subtree = subtree->nextBrother;
        int d = degree(subtree);
        max_degree = max_degree < d ? d : max_degree;
    }
    return max_degree < current_degree ? current_degree : max_degree;
}

// 叶子数
int leaf_count(Tree* ptree)
{
    if (ptree == nullptr)
        return 0;
    if (ptree->nextChild == nullptr)
        return 1;
    Tree* subtree = ptree->nextChild;
    int sum = leaf_count(subtree);
    while(subtree->nextBrother)
    {
        subtree = subtree->nextBrother;
        sum += leaf_count(subtree);
    }
    return sum;
}

// node数 包括root
int node_count(Tree* ptree)
{
    if (ptree == nullptr)
        return 0;
    if (ptree->nextChild == nullptr)
        return 1;
    Tree* subtree = ptree->nextChild;
    int sum = node_count(subtree);
    while(subtree->nextBrother)
    {
        subtree = subtree->nextBrother;
        sum += node_count(subtree);
    }
    return sum+1;
}

Print_Buffer* _tree_buffer(Tree* ptree)
{
    if (ptree->nextChild == nullptr)
    {
        std::string s = " "+ ptree->data->tostring()+ " ";
        Print_Buffer* buff = new Print_Buffer((char*)s.c_str(), s.length());
        return buff;
    }

    Tree* subtree = ptree->nextChild;
    Print_Buffer* buff = _tree_buffer(subtree);
    while( subtree->nextBrother != nullptr)
    {
        subtree = subtree->nextBrother;
        Print_Buffer* brotherbuff = _tree_buffer(subtree);
        buff->append_right(brotherbuff);
        brotherbuff->release();
    }
    std::string s = " "+ ptree->data->tostring()+ " ";
    Print_Buffer* buffnode = new Print_Buffer((char*)s.c_str(), s.length());
    buff->append_up(buffnode);
    buffnode->release();
    return buff;
}
/**
 * print
 */
void print(Tree* ptree)
{
    Print_Buffer* buff = _tree_buffer(ptree);
    buff->printbuff();
    buff->release();
}
}

namespace bitree
{

void init(BiTree* ptree)
{
    ptree->data = nullptr;
    ptree->left = nullptr;
    ptree->right = nullptr;
    ptree->hasleft = false;
    ptree->hasright = false;
}
void finit(BiTree* ptree)
{
    if (ptree->hasleft && ptree->left)
    {
        finit(ptree->left);
        _rmleft(ptree);
    }

    if (ptree->hasright && ptree->right)
    {
        finit(ptree->right);
        _rmright(ptree);
    }
    init(ptree);
}

// 双亲表示法的源数据构造链式树
BiTree* build_from_source(ElementTypeParentIndex* nodearray, int num)
{
    BiTree** nodes = new BiTree*[num];

    for (int i = 0; i < num; i++)
    {
        nodes[i] = new BiTree(nodearray[i].data);
    }

    for (int i = 0; i < num;i++)
    {
        if (nodearray[i].parentindex < 0 || nodearray[i].parentindex >= num)
            continue;

        BiTree* n = nodes[nodearray[i].parentindex];
        if (n->hasleft && n->hasright)
        {
            printf("error build_from_source_ex more than two child %d", i);
            continue;
        }
        if (n->hasleft) 
        {
            n->right = nodes[i];
            n->hasright = true;
        }
        else
        {
            n->left = nodes[i];
            n->hasleft = true;
        }
         
    }

    BiTree* root = nodes[0];
    delete nodes;
    return root;
}
// 还原双亲表示法的数据
void build_to_source(BiTree* ptree, ElementTypeParentIndex nodearray[], int& num)
{
    if (ptree == nullptr)
        return;

    int indexEnqueue = 0;
    int indexDequeue = 0;
    linkqueue::LinkQueue queue;
    linkqueue::init(&queue);
    linkqueue::enqueue(&queue, new ElementType(indexEnqueue++, ptree));

    nodearray[indexEnqueue-1].data =  ptree->data;
    nodearray[indexEnqueue-1].parentindex = -1;

    while(!linkqueue::isEmpty(&queue))
    {
        indexDequeue++;
        ElementType* treedata = linkqueue::dequeue(&queue);
        BiTree* node = (BiTree*)(treedata->data);

        if (node->hasleft)
        {
            linkqueue::enqueue(&queue, new ElementType(indexEnqueue++, node->left));
            nodearray[indexEnqueue-1].data =  node->left->data;
            nodearray[indexEnqueue-1].parentindex = indexDequeue-1;
        }
        if (node->hasright)
        {
            linkqueue::enqueue(&queue, new ElementType(indexEnqueue++, node->right));
            nodearray[indexEnqueue-1].data =  node->right->data;
            nodearray[indexEnqueue-1].parentindex = indexDequeue-1;
        }
        delete treedata;
    }
    num = indexEnqueue;
    
    // printf("tree to source array (%d) :\n", num);
    // for (int i=0;i<num;i++)
    // {
    //     printf(" %d:", i);
    //     nodearray[i].data->print();
    //     printf(" p(%d)\n", nodearray[i].parentindex);
    // }
}

// 完全二叉树顺序表示方式构造二叉树
BiTree* build_from_source_ex(ElementTypeParentIndex* nodearray, int num){}
// 还原二叉树为完全二叉树顺序表示方式
void build_to_source_ex(BiTree* ptree, ElementTypeParentIndex nodearray[], int& num){}


void _addleft(BiTree* ptree, ElementType* data)
{
    if (ptree->hasleft && ptree->left )
        printf("_addleft:error add left child");
    BiTreeNode* node = new BiTreeNode(data);
    ptree->left = node;
    ptree->hasleft = true;
}
void _addright(BiTree* ptree, ElementType* data)
{
    if (ptree->hasright && ptree->right )
        printf("_addright:error add right child");
    BiTreeNode* node = new BiTreeNode(data);
    ptree->right = node;
    ptree->hasright = true;
}
void _rmleft(BiTree* ptree)
{
    if (!(ptree->hasleft && ptree->left ))
    {
        printf("_rmleft:error rm left child");
        return;
    }
    delete ptree->left;
    ptree->left = nullptr;
    ptree->hasleft = false;
}
void _rmright(BiTree* ptree)
{
    if (!(ptree->hasright && ptree->right ))
    {
        printf("_rmright:error rm right child");
        return;
    }
    delete ptree->right;
    ptree->right = nullptr;
    ptree->hasright = false;
}

bool _isleaf(BiTree* ptree)
{
    return (ptree->hasleft == false && ptree->hasright == false);
}
// 是否是满二叉树, 任何子树的平衡值为0（左右子树深度相同）
bool isfull(BiTree* ptree)
{
    if (_isleaf(ptree))
        return true;
    int deep_left = ptree->hasleft ? deep(ptree->left) : 0;
    int deep_right = ptree->hasright ? deep(ptree->right) : 0;

    return deep_left == deep_right;
}

// 是否是完全二叉树, 任何子树有右子树一定有左子树, 且左深度>=右深度 XXX。。有问题
/**
 *  这题是真难。。。
 *  思路很多种，主要是一个简单的问题复杂度不能高
 *  使用还原双亲节点表示法的思路，检测层序遍历出队序号和入队序号是否满足 2n+1、2n的关系
 */
bool iscomplete(BiTree* ptree)
{
    linkqueue::LinkQueue queue;
    linkqueue::init(&queue);

    int index_enqueue = 0;
    int index_dequeue = 0;

    index_enqueue++;
    linkqueue::enqueue(&queue, new ElementType_Bitreenode(ptree));

    while (!linkqueue::isEmpty(&queue))
    {
        index_dequeue++;
        ElementType_Bitreenode* element = (ElementType_Bitreenode*)linkqueue::dequeue(&queue);
        BiTree* node = element->_node;
        delete element;
        if (node->hasleft)
        {
            index_enqueue++;
            linkqueue::enqueue(&queue, new ElementType_Bitreenode(node->left));
            if (index_enqueue != 2 * index_dequeue)
            {
                linkqueue::finit(&queue);
                return false;
            }
        }

        if (node->hasright)
        {
            index_enqueue++;
            linkqueue::enqueue(&queue, new ElementType_Bitreenode(node->right));
            if (index_enqueue != 2 * index_dequeue + 1)
            {
                linkqueue::finit(&queue);
                return false;
            }
        }
    }
    return true;
}

// 是否是平衡二叉树
bool isbalance(BiTree* ptree)
{
    int deep_left = ptree->hasleft ? deep(ptree->left) : 0;
    int deep_right = ptree->hasright ? deep(ptree->right) : 0;
    return !( (deep_left > deep_right + 1) || 
              (deep_right > deep_left + 1) );
}

// 最大深度
int deep(BiTree* ptree)
{
    if (_isleaf(ptree))
        return 1;
    int deep_left = ptree->hasleft ? deep(ptree->left) : 0;
    int deep_right = ptree->hasright ? deep(ptree->right) : 0;
    return 1 + (deep_left > deep_right ? deep_left : deep_right);
}

// 叶子数
int leaf_count(BiTree* ptree)
{
    if (_isleaf(ptree))
        return 1;
    int left_leafcount = ptree->hasleft ? leaf_count(ptree->left) : 0;
    int right_leafcount = ptree->hasright ? leaf_count(ptree->right) : 0;

    return left_leafcount+right_leafcount;
}

tree::Print_Buffer*  _bitree_buffer(BiTree* ptree)
{
    if (_isleaf(ptree))
    {
        std::string s = " "+ptree->data->tostring()+" ";
        return new tree::Print_Buffer(s.c_str(), s.length());
    }
    std::string s = " "+ptree->data->tostring()+" ";
    tree::Print_Buffer* up = new tree::Print_Buffer(s.c_str(), s.length());
    tree::Print_Buffer* left = nullptr;
    tree::Print_Buffer* right = nullptr;
    
    left = ptree->hasleft ? _bitree_buffer(ptree->left) : new tree::Print_Buffer("  /  ", 5);
    right = ptree->hasright ? _bitree_buffer(ptree->right) : new tree::Print_Buffer("  \\  ", 5);

    left->append_right(right);
    left->append_up(up);
    right->release();
    up->release();
    return left;
}
void print(BiTree* ptree)
{
    tree::Print_Buffer* buff = _bitree_buffer(ptree);
    buff->printbuff();
    buff->release();
}

/**
 * 先序遍历 收集所有的叶子
 */
void get_leafs(BiTree* ptree, linklist::LinkList* plist)
{
    if (_isleaf(ptree))
        return linklist::insert_tail(plist, new ElementType_Bitreenode(ptree));
    if (ptree->hasleft)
        get_leafs(ptree->left, plist);
    if (ptree->hasright)
        get_leafs(ptree->right, plist);
}

// node数 包括root
int node_count(BiTree* ptree)
{
    if (_isleaf(ptree))
        return 1;
    int left_count = ptree->hasleft ? node_count(ptree->left) : 0;
    int right_count = ptree->hasright ? node_count(ptree->right) : 0;
    return 1 + left_count + right_count;
}

void _visit_node(BiTreeNode* pnode)
{
    //pnode->print();
}

// 遍历_使用递归的方式实现
void traverse_preorder(BiTree* ptree, linklist::LinkList* plist)
{
    _visit_node(ptree);
    linklist::insert_tail(plist, new ElementType_Bitreenode(ptree));

    ptree->hasleft ? traverse_preorder(ptree->left, plist) : (void)0;
    ptree->hasright ? traverse_preorder(ptree->right, plist) : (void)0;
    
}
void traverse_inorder(BiTree* ptree, linklist::LinkList* plist)
{
    ptree->hasleft ? traverse_inorder(ptree->left, plist) : (void)0;

    _visit_node(ptree);
    linklist::insert_tail(plist, new ElementType_Bitreenode(ptree));
    
    ptree->hasright ? traverse_inorder(ptree->right, plist) : (void)0;
}
void traverse_postorder(BiTree* ptree, linklist::LinkList* plist) 
{
    ptree->hasleft ? traverse_postorder(ptree->left, plist) : (void)0;
    ptree->hasright ? traverse_postorder(ptree->right, plist) : (void)0;

    _visit_node(ptree);
    linklist::insert_tail(plist, new ElementType_Bitreenode(ptree));

}

// 层序用递归实现不了，队列实现
//void traverse_levelorder(BiTree* ptree, linklist::LinkList* plist) { }

// 遍历_使用循环、栈、队列的方式实现
/**
 * 树的先序遍历， 栈实现
 */
void traverse_preorder_ex(BiTree* ptree, linklist::LinkList* plist) 
{
    listack::LiStack stack;
    listack::init(&stack);

    BiTreeNode* node = ptree;
    while (node != nullptr)
    {
        _visit_node(node);
        linklist::insert_tail(plist, new ElementType_Bitreenode(node));
        if (node->hasleft)
        {
            listack::push(&stack, new ElementType_Bitreenode( node));
            node = node->left;
        } else if (node->hasright)
        {
            // listack::push(&stack, new ElementType_Bitreenode( node));
            node = node->right;
        } else {
            do {
                node = nullptr;
                if (listack::isEmpty(&stack))
                {
                    break;
                }
                ElementType_Bitreenode* pstacknode = (ElementType_Bitreenode*)listack::pop(&stack);
                BiTreeNode* parent = (BiTreeNode*)pstacknode->_node;
                if (parent->hasright)
                {
                    node = parent->right;
                }
                delete pstacknode;
            } while (node == nullptr);
        }
    }
}
/**
 * 树的中序遍历， 栈实现
 */ 
void traverse_inorder_ex(BiTree* ptree, linklist::LinkList* plist)
{
    listack::LiStack stack;
    listack::init(&stack);

    BiTreeNode* node = ptree;
    while (node != nullptr)
    {
        if (node->hasleft)
        {
            listack::push(&stack, new ElementType_Bitreenode(node));
            node = node->left;
        } else if (node->hasright)
        {
            _visit_node(node);
            linklist::insert_tail(plist, new ElementType_Bitreenode(node));
            node = node->right;
        } else {
            _visit_node(node);
            linklist::insert_tail(plist, new ElementType_Bitreenode(node));
            node = node->right;
            do {
                node = nullptr;
                if (listack::isEmpty(&stack))
                {
                    break;
                }
                ElementType_Bitreenode* pstacknode = (ElementType_Bitreenode*)listack::pop(&stack);
                BiTreeNode* parent = (BiTreeNode*)pstacknode->_node;
                //delete pstacknode;

                _visit_node(parent);
                linklist::insert_tail(plist, pstacknode);
                if (parent->hasright)
                {
                    node = parent->right;
                }
            } while (node == nullptr);
        }
    }

}
/**
 * 2019.10.16 树的后序遍历，栈实现不了。。。
 * 2019.10.21 栈实现： 先左，然后根出栈，如果有右子树，根拿到右，根再进栈（需要标识区别），再对右子树后序。所以进栈元素需要加标记
 */
// void traverse_postorder_ex(BiTree* ptree, linklist::LinkList* plist) {}

void traverse_levelorder_ex(BiTree* ptree, linklist::LinkList* plist)
{
    linkqueue::LinkQueue queue;
    linkqueue::init(&queue);
    
    linkqueue::enqueue(&queue, new ElementType_Bitreenode(ptree));
    while(!linkqueue::isEmpty(&queue))
    {
        ElementType_Bitreenode* pstacknode = (ElementType_Bitreenode*)linkqueue::dequeue(&queue);
        BiTreeNode* ptreenode = (BiTreeNode*)(pstacknode->_node);

        _visit_node(ptreenode);
        linklist::insert_tail(plist, pstacknode);
        ptreenode->hasleft ? linkqueue::enqueue(&queue, new ElementType_Bitreenode(ptreenode->left)) : (void)0;
        ptreenode->hasright ? linkqueue::enqueue(&queue, new ElementType_Bitreenode(ptreenode->right)) : (void)0;
    }
}

// 线索化_先序、中序、后续, 层序遍历线索化
/**
 * root => left[first, last]=> right[first, last]
 * root--<--left.first  , left.last-->-<--right.first
 */
Threaded_Result threaded_traverse_preorder(BiTree* ptree) 
{
    Threaded_Result res = {ptree, ptree};
    Threaded_Result left_res    = {nullptr, nullptr};
    Threaded_Result right_res   = {nullptr, nullptr};

    //_visit_node(ptree);
    if (ptree->hasleft)
    {
        left_res = threaded_traverse_preorder(ptree->left);
        //res.first = left_res.first;
    }

    if (ptree->hasright)
    {
        right_res = threaded_traverse_preorder(ptree->right);
        //res.last = right_res.last;
    }

    // 打通前驱后继经脉
    if (ptree->hasleft)
    {
        // 左的首节点  前驱到（如果没有孩子）根
        if (!left_res.first->hasleft)
            left_res.first->left = ptree;

        if (ptree->hasright)
        {
            // 左的末尾 后继到 右的首节点, 右的首节点 前驱到（如果没有孩子）左的末尾
            left_res.last->right = right_res.first;
            if (!right_res.first->hasleft)
                right_res.first->left = left_res.last;

            res.last = right_res.last;
        }
        else
        {
            res.last = left_res.last;
        }
    }
    else
    {
        if (ptree->hasright)
        {
            // 右的首节点  前驱到（如果没有孩子）根
            if(!right_res.first->hasleft)
                right_res.first->left = ptree;

            res.last = left_res.last;
        }
    }
    return res;
}

/**
 * 递归方式携带前后节点指针, 返回线索化，链式访问首节点
 * left[first, last] => root => right[first, last]
 * left.last-->--root--<--right.first
 */
Threaded_Result threaded_traverse_inorder(BiTree* ptree) 
{
    Threaded_Result res         = {ptree, ptree};
    Threaded_Result left_res    = {nullptr, nullptr};
    Threaded_Result right_res   = {nullptr, nullptr};
    
    if (ptree->hasleft)
    {
        left_res = threaded_traverse_inorder(ptree->left);
        left_res.last->right = ptree;

        res.first = left_res.first;
    }
    
    //_visit_node(ptree);

    if (ptree->hasright)
    {
        right_res = threaded_traverse_inorder(ptree->right);
        right_res.first->left = ptree;

        res.last = right_res.last;
    }
    
    // printf ("node [%d,%d]-> %d ->[%d,%d] \n", 
        
    //     left_res.first ? left_res.first->data->key : 0,
    //     left_res.last ? left_res.last->data->key : 0,
    //     ptree->data->key, 
    //     right_res.first ? right_res.first->data->key : 0,
    //     right_res.last ? right_res.last->data->key : 0);
    return res;
}

/**
 * 后序线索化，在线索中帮助性不大(叶子很傻的把自己的左右指向自己的双亲)，还是很依赖栈式顺序
 * * left[first, last] => right[first, last] => root 
 * left.last-->-<--right.first,  right->last-->root
 * 
 */
Threaded_Result threaded_traverse_postorder(BiTree* ptree) 
{
    Threaded_Result res         = {ptree, ptree};
    Threaded_Result left_res    = {nullptr, nullptr};
    Threaded_Result right_res   = {nullptr, nullptr};
    
    return res;
}
Threaded_Result threaded_traverse_levelorder(BiTree* ptree) 
{
    Threaded_Result res         = {ptree, ptree};
    Threaded_Result left_res    = {nullptr, nullptr};
    Threaded_Result right_res   = {nullptr, nullptr};
    return res;
}

// 遍历 线索化的树
void print_threaded_traverse_preorder(BiTree* ptree, linklist::LinkList* plist) 
{
    BiTreeNode* node = ptree;
    while (node)
    {
        linklist::insert_tail(plist, new ElementType_Bitreenode(node));
        if (node->hasleft)
        {
            node = node->left;
        }
        else {
            node = node->right;
        } 
    }
}
/**
 * 利用线索进行中序遍历，努力不借助栈和队列，不递归。
 */
void print_threaded_traverse_inorder(BiTree* ptree, linklist::LinkList* plist) 
{
    BiTreeNode* node = ptree;
    
    while(node)
    {
        while(node->hasleft)
        {
            node = node->left;
        }
        // printf("-%d ", node->data->key);
        linklist::insert_tail(plist, new ElementType_Bitreenode(node));
        
        // 左完成， 指向中根，访问当前根
        node = node->right;
        if (node == nullptr)
            break;
        // printf("-%d ", node->data->key);
        linklist::insert_tail(plist, new ElementType_Bitreenode(node));
        
        while (!node->hasright && node->right)
        {
            // 利用线索 递归回溯中根
            node = node->right;
            // printf("-%d ", node->data->key);
            linklist::insert_tail(plist, new ElementType_Bitreenode(node));
        }

        // 转到右子树
        node = node->right;
    }
}
void print_threaded_traverse_postorder(BiTree* ptree, linklist::LinkList* plist) 
{
    BiTreeNode* node = ptree;
    while(node->hasleft)
    {
        node = node->left;
    }

    while(node)
    {
        linklist::insert_tail(plist, new ElementType_Bitreenode(node));
        if (node->hasright)
        {
            node = node->right;
            while(node->hasleft)
            {
                node = node->left;
            }
        }
        else
        {
            node = node->right;
        }
        
    }
}
// 线索化似乎对层次遍历没多大帮助，依然需要借助 辅助队列
void print_threaded_traverse_levelorder(BiTree* ptree, linklist::LinkList* plist) 
{

}

namespace avl
{
int avl_elementtype_compare(const ElementType& e1, const ElementType& e2)
{
    return e1.key > e2.key ? 1 : (e1.key < e2.key ? -1 : 0);
}
void _ll_rotate(BiTree* ptree) { }
void _rr_rotate(BiTree* ptree) { }
void _rl_rotate(BiTree* ptree) { }
void _lr_rotate(BiTree* ptree) { }
BiTreeNode* find(BiTree* ptree, ElementType* key, int (*CompFunc)(const ElementType& e1, const ElementType& e2))
{
    return nullptr;
}
void insert(BiTree* ptree, ElementType* p, int (*CompFunc)(const ElementType& e1, const ElementType& e2)) { }
void remove(BiTree* ptree, BiTreeNode* pnode) { }
} // endnamespace avltree

namespace huffman
{
/**
 * 1 父节点权值 是两个子节点权值的和
 * 2 两个兄弟节点之间，自己比兄弟的孩子一定要大
 */
bool ishuffman(BiTree* ptree)
{
    if (!ptree->hasleft && !ptree->hasright)
    {
        return true;
    }
    if ((ptree->hasleft && !ptree->hasright) ||
        (ptree->hasright && !ptree->hasleft))
    {
        return false;
    }
    if (ptree->data->key != ptree->left->data->key + ptree->right->data->key)
    {
        return false;
    }

    if (ptree->left->hasleft && ptree->left->hasright)
    {
        if ((ptree->left->left->data->key > ptree->right->data->key) ||
            (ptree->left->right->data->key > ptree->right->data->key))
            return false;
        if (ptree->right->hasleft || ptree->right->hasright)
            return false;
        return ishuffman(ptree->left);
    }
    if (ptree->right->hasleft && ptree->right->hasright)
    {
        if ((ptree->right->left->data->key > ptree->left->data->key) ||
            (ptree->right->right->data->key > ptree->left->data->key))
            return false;
        if (ptree->left->hasleft || ptree->left->hasright)
            return false;
        return ishuffman(ptree->right);
    }

    return false;
}
/**
 * 每次从森林中取出两个 树，树根的权值是最小的两个 树 (树根的权值是自己左右子树的权值之和)
 */
BiTree* build_huffman(ElementType dataarray, int num)
{

    return nullptr;
}
} // endnamespace huffman
} // endnamespace bitree