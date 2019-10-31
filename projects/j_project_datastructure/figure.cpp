
#include "figure.h"


namespace figure {
    
// 图的遍历——深度优先
void DFS_adjacentmatrix(const Figure_AdjacentMatrix& figure, linklist::LinkList* res) { }
void DFS_adjacenttable(const Figure_AdjacentTable& figure, linklist::LinkList* res) { }

// 图的遍历——广度优先
void BFS_adjacentmatrix(const Figure_AdjacentMatrix& figure, linklist::LinkList* res) { }
void BFS_adjacenttable(const Figure_AdjacentTable& figure, linklist::LinkList* res) { }




// 图的应用——最小生成树 Prim Kruskal
void minist_tree_Prim_adjacenttable(const Figure_AdjacentTable& figure, Tree* tree) { }
void minist_tree_Kruskal_nodeslinksset(Nodes_set* nodes, Links_set* links, Tree* tree) { }

// 图的应用——最短路径 Dijkstra Floyd
void shortest_path_Dijkstra_adjacenttable(const Figure_AdjacentTable& figure, linklist::LinkList** res) { }
void shortest_path_Floyd_adjacentmatrix(const Figure_AdjacentMatrix& figure, linklist::LinkList** res) { }

// 图的应用——拓扑排序
void topological_sort_adjacenttable(const Figure_AdjacentTable& figure, linklist::LinkList* res) { }
void topological_sort_adjacentmatrix(const Figure_AdjacentMatrix& figure, linklist::LinkList* res) { }

// 图的应用——关键路径
// @todo


} // figure

