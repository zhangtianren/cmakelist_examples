# C++ STL 容器及常用接口及，容器算法实现

list map vector set 为四大基础容器。

list 是双向链表实现， 支持任意位置的插入删除
vector 是动态数组的实现， 支持下标的随机访问，动态插入和删除会涉及数据的整体搬迁
map rb_tree(红黑树)包装实现的, 查找效率Olog(n),插入是默认有序的
set rb_tree(红黑树)包装实现的, 查找效率Olog(n),插入是默认有序的
deque 是一种双向开口的连续线性空间， 由中控器中的map指针数组指向存储数据的节点区

array 是对原始数组的包装，增加了迭代器访问
stack，queue是容器适配器，默认底层使用deque容器，是头尾插入删除等操作的定制化容器
forwardlist 是单向链表
unordered_map unordered_set是哈希实现的，查找效率Olog(1),插入是无序的
hash_map hash_table 是基于hash算法实现的一类存储容器
priority_queue 优先队列，和queue不同的就在于我们可以自定义其中数据的优先级, 让优先级高的排在队列前面,优先出队