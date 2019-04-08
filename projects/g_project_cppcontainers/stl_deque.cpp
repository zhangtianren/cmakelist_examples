#include "stl_headers.h"
#include<iostream>
using namespace std;


/*
https://blog.csdn.net/u012940886/article/details/80529721
1 vector是单向开口的连续线性空间，deque则是一种双向开口的连续线性空间。所谓双向开口，意思是可以在头尾两端分别做元素的插入和删除操所。
vector当然也可以在头尾端进行操作（从技术观点），但是其从头部操作效率奇差，无法被接受。
2 deque和vector的最大差异，
一在于deque允许常数时间内对起头端进行元素的插入或移除操作，
二在于deque没有所谓的容量概念，因为它是动态地以分段连续空间组合而成，随时可以增加一段新的空间并链接起来
3 deque采用一块所谓的map（不是STL的map容器）作为主控。这里所谓map是一小块连续空间，其中每个元素(此处称为一个节点，node)都是指针，指向另一段(较大的)连续线性空间，称为缓冲区。缓冲区才是deque的储存空间主体
*/

#include <deque>
#include<algorithm>
void test_deque(void)
{
	std::deque<int, std::allocator<int>> ideq(20, 9);
	std::cout << "size=" << ideq.size() << std::endl;
	
	for (int i = 0; i < ideq.size(); ++i)
		ideq[i] = i;

	for (int i = 0; i < ideq.size(); ++i)
		std::cout << ideq[i] << ' ';

	std::cout << endl;
	for (int i = 0; i < 3; i++)
		ideq.push_back(i);
	
	for (int i = 0; i < ideq.size(); ++i)
		std::cout << ideq[i] << ' ';
	std::cout << endl;
	std::cout << "size=" << ideq.size() << endl;
	
	ideq.push_back(3);

	for (int i = 0; i < ideq.size(); ++i)
		std::cout << ideq[i] << ' ';
	std::cout << endl;
	std::cout << "size=" << ideq.size() << endl;

	ideq.push_front(99);
	for (int i = 0; i < ideq.size(); ++i)
		std::cout << ideq[i] << ' ';
	std::cout << endl;
	std::cout << "size=" << ideq.size() << endl;

	ideq.push_front(98);
	ideq.push_front(97);
	for (int i = 0; i < ideq.size(); ++i)
		std::cout << ideq[i] << ' ';
	std::cout << endl;
	std::cout << "size=" << ideq.size() << endl;
	deque<int>::iterator it = find(ideq.begin(), ideq.end(), 99);
	std::cout << *it << endl;
}

/*
源码
deque的中控器
template<class T, class Alloc = alloc, size_t BufSiz = 0>
class deque {
public:
	typedef T   value_type;
	typedef value_type* pointer;
	typedef size_t  size_type;
	public:
	typedef __deque_iterator<T, T&, T*, BufSiz>  iterator;
protected:
	//元素的指针的指针(pointer of pointer of T)  
	typedef pointer*    map_pointer;
protected:
	iterator    start; //表现第一节点  
	iterator    finish; //表现最后一个节点  
	map_pointer map; //指向map,map是块连续空间，其每个元素都是个指针，指向一个节点(缓冲区)  
	size_type   map_size; //map内有多少指针  
	...
};  
deque的迭代器
template<class T, class Ref, class Ptr, size_t BufSiz>
	struct __deque_iterator { //未继承std::iterator  
	typedef __deque_iterator<T, T&, T*, BufSize> iterator;
	typedef __deque_iterator<T, const T&, const T*, BufSize> const_iterator;
	static  size_t  buffer_size() { return __deque_buf_size(BufSize, sizeof(T)); }

	//未继承std::iterator，所以必须自行撰写五个必要的迭代器相应型别  
	typedef random_access_iterator_tag  iterator_category;
	typedef T   value_type;
	typedef Ptr pointer;
	typedef Ref reference;
	typedef size_t  size_type;
	typedef ptrdiff_t   difference_type;
	typedef T** map_pointer;

	typedef __deque_iterator    self;

	//保持与容器的联结  
	T *cut; //此迭代器所指之缓冲区中的现行(current)元素  
	T *first; //此迭代器所指之缓冲区的头  
	T *last;   //此迭代器所指之缓冲区的尾(含备用空间)  
	map_pointer node; //指向管控中心  
	...
};
*/
