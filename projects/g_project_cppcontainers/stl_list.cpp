#include "stl_headers.h"
#include<iostream>
using namespace std;
/*
双向链表， 支持任意位置的插入删除。不能随机访问

· 迭代 (Iterator)
· list.begin() 回传指向第一个元素的 Iterator。
· list.end() 回传指向最末元素的下一个位置的 Iterator。
· list.rbegin() 回传指向最末个元素的反向 Iterator。
· list.rend() 回传指向第一个元素的前一个位置的反向 Iterator。

· Capacity/Size:
· list.empty() 若list内部为空，则回传true值。
· list.size() 回传list内实际的元素个数。
· list.resize() 重新分派list的长度。

· 存取插删元素的方法
· list.front() 存取第一个元素。
· list.back() 存取最末个元素。
· list.push_front() 增加一个新的元素在 list 的前端。
· list.pop_front() 删除 list 的第一个元素。
· list.push_back() 增加一个新的元素在 list 的尾端。
· list.pop_back() 删除 list 的最末个元素。
· list.insert() - 插入一个或多个元素至 list内的任意位置。
· list.erase() - 删除 list中一个或多个元素。
· list.clear() - 清空所有元素。

· 重新配置／重设长度
· list.reserve() - 如有必要，可改变 list的容量大小（配置更多的内存）。
· list.resize() - 改变 list目前持有的元素个数。

	swap(ls1, ls2);			//交换两个list
	reverse(ls.begin(), ls.end()); //list的翻转
	ls.merge(ls1);			//合并两个list
*/
#include <list>

//遍历list
void print_list(list<int> ls)
{
	list<int>::iterator ite = ls.begin();
	while (ite != ls.end())
	{
		std::cout << *ite << " ";
		ite++;
	}
	std::cout << std::endl;
}

void test_list()
{
	//list初始化
	std::list<int> ls;
	std::list<int> ls1(5);//定义长度，初识值为0
	std::list<int> ls2(5, 3);//定义长度，初识值为3

						//遍历lisg
	print_list(ls1);

	//最后一个元素之后插入元素
	ls.push_back(1);
	//第一个元素之前插入元素
	ls.push_front(0);
	print_list(ls);

	//获得第一个、最后一个元素
	int first_val = ls.front();
	int last_val = ls.back();
	std::cout << first_val << std::endl;

	//删除最后一个元素、第一个元素
	ls.pop_back();
	ls.pop_front();

	//判断list是否为空
	bool empty_result = ls.empty();

	//resize list的长度
	ls.resize(5);
	ls.resize(5, 3);//指定填充值
	print_list(ls);

	//清空list
	ls.clear();

	//替换list元素为5个3
	ls.assign(5, 3);
	ls.assign(ls1.begin(), ls1.end());
	print_list(ls);

	//交换两个list
	swap(ls1, ls2);
	print_list(ls1);

	//list的翻转
	reverse(ls.begin(), ls.end());

	//合并两个list
	ls.merge(ls1);
	print_list(ls);

	//在指定位置插入元素
	ls.insert(ls.begin(), 2, 100); //在开始位置插入2个100
	print_list(ls);

	//删除区间元素
	ls.erase(ls.begin(), ls.end());

	//删除指定所有值得元素
	ls.remove(0);
}



/*
源码实现, 双向链表
https://www.cnblogs.com/runnyu/p/5992839.html
*/