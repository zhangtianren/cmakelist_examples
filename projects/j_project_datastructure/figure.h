

#include "util.h"
#pragma once

#include "list.h"
#include "tree.h"

namespace figure
{

typedef struct node 
{
    ElementType data;
}Node;

typedef struct link
{
    Node* from;
    Node* to;
    int weight;
}Link;

// 点集
typedef struct nodes_set
{
    int num;
    linklist::LinkList list;
    nodes_set ()
    {
        num = 0;
        linklist::init(&list);
    }
    void add(Node* node)
    {

    }
    void remove(Node* node)
    {

    }
}Nodes_set;

// 边集
typedef struct links_set
{
    int num;
    linklist::LinkList list;
    links_set()
    {
        num = 0;
        linklist::init(&list);
    }
    void sort()
    {

    }
    void add(Link* link)
    {

    }
    void remove(Link* link)
    {

    }
}Links_set;

/**
 * 邻接矩阵表示法
 */
typedef struct figure_adjacentmatrix
{
    int num;            // 图中节点数
    Node** nodes;       // num个节点的指针顺序存储
    int** linkmatrix;   // 带权值的邻接矩阵
    figure_adjacentmatrix(int n, const Nodes_set& ns, const Links_set& links)
    {

    }
    void print()
    {

    }
}Figure_AdjacentMatrix;

/**
 * 邻接表表示法
 */
typedef struct figure_adjacenttable
{
    int num;                        // 图中节点数
    Node** nodes;                   // num个节点的指针顺序存储
    linklist::LinkList** linktable; // 节点相邻边的链式存储
    figure_adjacenttable(int n, const Nodes_set& ns, const Links_set& links)
    {

    }
    void print()
    {

    }
}Figure_AdjacentTable;
// 十字链表
// 邻接多重表 


// 图的遍历——深度优先
void DFS_adjacentmatrix(const Figure_AdjacentMatrix& figure, linklist::LinkList* res);
void DFS_adjacenttable(const Figure_AdjacentTable& figure, linklist::LinkList* res);

// 图的遍历——广度优先
void BFS_adjacentmatrix(const Figure_AdjacentMatrix& figure, linklist::LinkList* res);
void BFS_adjacenttable(const Figure_AdjacentTable& figure, linklist::LinkList* res);




// 图的应用——最小生成树 Prim Kruskal
void minist_tree_Prim_adjacenttable(const Figure_AdjacentTable& figure, Tree* tree);
void minist_tree_Kruskal_nodeslinksset(Nodes_set* nodes, Links_set* links, Tree* tree);

// 图的应用——最短路径 Dijkstra Floyd
void shortest_path_Dijkstra_adjacenttable(const Figure_AdjacentTable& figure, linklist::LinkList** res);
void shortest_path_Floyd_adjacentmatrix(const Figure_AdjacentMatrix& figure, linklist::LinkList** res);

// 图的应用——拓扑排序
void topological_sort_adjacenttable(const Figure_AdjacentTable& figure, linklist::LinkList* res);
void topological_sort_adjacentmatrix(const Figure_AdjacentMatrix& figure, linklist::LinkList* res);

// 图的应用——关键路径
// @todo


}