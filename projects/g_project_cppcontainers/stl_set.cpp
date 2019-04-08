#include "stl_headers.h"
#include<iostream>
using namespace std;

/*
set 不重复的数据的集合
set的底层是有由红黑树实现的（与set / multimap / multiset相同）
1 用set查找数据的效率是O（logn）略逊unordered_set一筹，人家底层是哈希表，查询是O(1)
2 红黑树的实质是平衡二叉搜索树,所以map中插入的数据会自动排序。且根据你创建的map的模板参数来决定是升序排列还是降序排列
*/
#include <string>
#include <set>
void test_set(void)
{
	set<string> str;
	str.insert("zero");

	str.insert("one");
	str.insert("one");

	str.insert("two");
	str.insert("three");
	set<string> str1(str.begin(), str.end());
	for (const auto &i : str1)
		cout << i << " ";		// one three two zero
	cout << endl;
	cout << *str.begin() << " " << str.count("one") << " " << *str.find("one") << " " << endl;	// one 1 one 

}