#include "cpp11_header.h"
#include<iostream>
using namespace std;


/*
std::array相对于数组，增加了迭代器等函数
(实际上 新型的 for (auto i : array) 对于数组也是可行的)
*/
#include <array>
void test_array()
{
	std::array<int, 4> arrayDemo = { 1,2,3,4 };
	std::cout << "arrayDemo:" << std::endl;
	for (auto itor : arrayDemo)
	{
		std::cout << itor << std::endl;
	}
	int arrayDemoSize = sizeof(arrayDemo);
	std::cout << "arrayDemo size:" << arrayDemoSize << std::endl;
}

/*
std::forward_list为从++新增的线性表，与list区别在于它是单向链表
*/
#include <forward_list>
void test_forwardlist()
{
	std::forward_list<int> numbers = { 1,2,3,4,5,4,4 };
	std::cout << "numbers:" << std::endl;
	for (auto number : numbers)
	{
		std::cout << number << std::endl;
	}
	numbers.remove(4);
	std::cout << "numbers after remove:" << std::endl;
	for (auto number : numbers)
	{
		std::cout << number << std::endl;
	}
}

/*
std::unordered_map与std::map用法基本差不多，但STL在内部实现上有很大不同，
std::map使用的数据结构为二叉树，而std::unordered_map内部是哈希表的实现方式，哈希map理论上查找效率为O(1)。
但在存储效率上，哈希map需要增加哈希表的内存开销。
*/
#include <unordered_map>
void test_unorderedmap()
{
	std::unordered_map<std::string, std::string> mymap =
	{
		{ "house","maison" },
		{ "apple","pomme" },
		{ "tree","arbre" },
		{ "book","livre" },
		{ "door","porte" },
		{ "grapefruit","pamplemousse" }
	};
	unsigned n = mymap.bucket_count();
	std::cout << "mymap has " << n << " buckets.\n";
	for (unsigned i = 0; i<n; ++i)
	{
		std::cout << "bucket #" << i << " contains: ";
		for (auto it = mymap.begin(i); it != mymap.end(i); ++it)
			std::cout << "[" << it->first.c_str() << ":" << it->second.c_str() << "] ";
		std::cout << "\n";
	}
}


/*
std::unordered_set的数据存储结构也是哈希表的方式结构，
除此之外，std::unordered_set在插入时不会自动排序，这都是std::set表现不同的地方。
*/
#include <set>
#include <unordered_set>
void test_unorderedset()
{
	std::unordered_set<int> unorder_set;
	unorder_set.insert(7);
	unorder_set.insert(5);
	unorder_set.insert(3);
	unorder_set.insert(4);
	unorder_set.insert(6);
	std::cout << "unorder_set:" << std::endl;
	for (auto itor : unorder_set)
	{
		std::cout << itor << std::endl;
	}

	std::set<int> set;
	set.insert(7);
	set.insert(5);
	set.insert(3);
	set.insert(4);
	set.insert(6);
	std::cout << "set:" << std::endl;
	for (auto itor : set)
	{
		std::cout << itor << std::endl;
	}
}