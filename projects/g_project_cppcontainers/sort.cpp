#include "stl_headers.h"
#include<iostream>
using namespace std;
/*
1 queue/stack 使用了deque作为存储结构，不适合排序。（通常要倒出来到vector排序完成再倒回去）
2 map set 使用了rb_tree 天然是有序的.可以自定比较器来控制排序方向(插入时自然排序)
3 Effective STL 介绍了如何选择排序函数, stl提供了几个常用的sort函数
sort	对给定区间的所有元素进行排序
stable_sort	对给定区间所有元素进行稳定排序
partial_sort	对给定区间所有元素部分排序
partial_sort_copy	对给定区间复制并排序
nth_element	找出给定区间某个位置对应的元素
is_sorted	判断一个区间是否已经排好序
partition	使得符合某个条件的元素放在前面
stable_partition	相对稳定的使得符合某个条件的元素放在前面
*/

#include <algorithm>

class myclass
{
public:
	myclass(int a, int b, std::string strMsg = "abc") :first(a), second(b), msg(strMsg) {}
	int first;
	int second;
	std::string msg;
	bool operator < (const myclass &m)const
	{
		return first<m.first;
	}
	bool operator == (const myclass &m)const
	{
		return (first == m.first 
			&& second == m.second 
			&& msg == m.msg);
	}
};
bool myclass_first_compator(const myclass &m1, const myclass &m2)
{
	return m1.first<m2.first;
}
bool myclass_second_compator(const myclass &m1, const myclass &m2)
{
	return m1.second<m2.second;
}
bool myclass_msg_compator(const myclass &m1, const myclass &m2)
{
	return m1.msg.length() < m2.msg.length();
}

void sort_list()
{

}

#include <vector>
void sort_vector()
{
	std::vector <myclass> vec;
	for (int i = 0; i<10; i++)
	{
		myclass my(10 - i, i * 3);
		vec.push_back(my);
	}
	for (int i = 0; i<vec.size(); i++)
		std::cout << "(" << vec[i].first << "," << vec[i].second << ")" << endl;
	cout << endl;
	cout << endl;
	sort(vec.begin(), vec.end());
	cout << "第一次排序后：" << endl;
	cout << endl;
	for (int i = 0; i<vec.size(); i++)
		cout << "(" << vec[i].first << "," << vec[i].second << " : " << vec[i].msg.c_str() << ")" << endl;
	cout << endl;
	cout << endl;
	sort(vec.begin(), vec.end(), myclass_first_compator);
	cout << "第二排序后：" << endl;
	cout << endl;
	for (int i = 0; i<vec.size(); i++)
		cout << "(" << vec[i].first << "," << vec[i].second << " : " << vec[i].msg.c_str() << ")" << endl;
	cout << endl;
	cout << endl;

	sort(vec.begin(), vec.end(), myclass_second_compator);
	cout << "第三排序后：" << endl;
	cout << endl;
	for (int i = 0; i<vec.size(); i++)
		cout << "(" << vec[i].first << "," << vec[i].second << " : " << vec[i].msg.c_str() << ")" << endl;
	cout << endl;
}



void sort_unorderedmap()
{
}

#include <unordered_set>

struct myclass_hash
{
	size_t operator()(myclass _val) const
	{
		return static_cast<size_t>(_val.first % 27 + _val.second);
	}
};
struct myclass_hash_sort
{
	size_t operator()(myclass _val) const
	{
		return static_cast<size_t>(_val.first);
	}
};
void sort_unorderedset()
{
	std::unordered_set<myclass, myclass_hash_sort> myset;
	//std::unordered_set<myclass, myclass_hash> myset;
	for (int i = 0; i<10; i++)
	{
		myclass my(10 - i, i * 3, std::string(1, char(65 + i)));
		myset.insert(my);
	}

	for (auto itor : myset)
	{
		cout << "(" << itor.first << "," << itor.second << " : " << itor.msg.c_str() << ")" << endl;
	}
	cout << endl;
}

#include <set>
class myclass_cmp {
public:
	bool operator() (const myclass& lc, const myclass& rc) {
		//return !!(lc.num < rc.num);
		return lc.second < rc.second;
	}
};
void sort_set()
{
	//std::set<myclass> myset;
	std::set<myclass, myclass_cmp> myset;
	for (int i = 0; i<10; i++)
	{
		myclass my(10 - i, i * 3);
		myset.insert(my);
	}

	for (auto itor : myset)
	{
		cout << "(" << itor.first << "," << itor.second << " : " << itor.msg.c_str() << ")" << endl;
	}
	cout << endl;
}