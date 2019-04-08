#include "stl_headers.h"
#include<iostream>
using namespace std;

/*
map的底层是有由红黑树实现的（与set / multimap / multiset相同）
1 用map查找数据的效率是O（logn）略逊unordered_map一筹，人家底层是哈希表，查询是O(1)
2 红黑树的实质是平衡二叉搜索树,所以map中插入的数据会自动排序。且根据你创建的map的模板参数来决定是升序排列还是降序排列
3 通过key值比较来确认每一个pair的存储位置，所以，在map中存储的数据必须能够比较大小
4 不能够修改map中的每个pair的键值key，这是因为红黑树是搜索树，且按照key值排列的，修改key值会破坏整个红黑树的结构。但是修改pair中的实值value是被允许
5 map中键值不能够重复,这也是他和multimap的唯一区别
*/
#include <map>
void test_map(void)
{
	// 构造一个空的map，此时m中一个元素都没有
	map<string, string> m;
	m["苹果"] = "apple";
	m["香蕉"] = "banana";
	/*
	operator[]的原理是：
	用<key, T()>构造一个键值对，然后调用insert()函数将该键值对插入到map中
	如果key已经存在，插入失败，insert函数返回该key所在位置的迭代器
	如果key不存在，插入成功，insert函数返回新插入元素所在位置的迭代器
	operator[]函数最后将insert返回值键值对中的value返回
	*/

	// 将<"apple", "">插入map中，插入成功，返回value的引用，将“苹果”赋值给该引用结果，
	// 即修改与"apple"对应的value""为"苹果"

	m["apple"] = "苹果";

	// 将<"apple", "">插入map中，插入失败，将<"apple", "苹果">中的"苹果"返回

	std::cout << m["apple"].c_str() << endl;
	std::cout << m.size() << endl;

	// “banan不在map中，该函数抛异常”
	m.at("banan");

	

	m.insert(pair<string, string>("不行", "no"));
	m.insert(make_pair("你好", "hello"));

	m.erase("香蕉");

	auto it1 = m.find("你好");;

	cout << "查找成功: " << it1->first.c_str() << "  ->>>  " << it1->second.c_str() << endl;
}


/*
源码

template<class _T1, class _T2>
struct pair
{
	typedef _T1 first_type;    /// @c first_type is the first bound type
	typedef _T2 second_type;   /// @c second_type is the second bound type

	_T1 first;                //注意，他是pulbic
	_T2 second;

	pair() : first(T1()) , second(T2())   //构造一个key和value都为空的pair
	{}

	pair（const T1& a，const T2& b）: first(a)，second（b）//构造一个键值为a，
	//实值为b的pair
	{}
}

template <class Key, class Compare = less<Key>, class Alloc = alloc>
class set {
public:
	// typedefs:

	typedef Key key_type;//键值key
	typedef Key value_type;//实值value（其实底层红黑树中key和value都是key值，
	//只是取名不同）

	typedef Compare key_compare;//比较器，默认传的是less，
	//也可以显示的传函数指针或仿函数。

	typedef Compare value_compare;
private:
	typedef rb_tree<key_type, value_type,
	identity<value_type>, key_compare, Alloc> rep_type;
	rep_type t;  // red-black tree representing set
};
*/