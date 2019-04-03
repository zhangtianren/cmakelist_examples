#include "cpp11_header.h"
#include<iostream>
using namespace std;

/*
1 使用auto的时候，编译器根据上下文情况，确定auto变量的真正类型
2 auto作为函数返回值时，只能用于定义函数，不能用于声明函数 (不带函数实现的头文件里auto是会编译报错)
*/
auto AddTest(int a, int b)
{
	return a + b;
}

void test_auto()
{
	auto index = 10;
	auto str = "abc";
	auto ret = AddTest(1, 2);
	std::cout << "index:" << index << std::endl;
	std::cout << "str:" << str << std::endl;
	std::cout << "res:" << ret << std::endl;
}



/*
C++ 里NULL 就是0 会和空指针0混淆。nullptr 专门指的空指针
#ifdef __cplusplus
    #define NULL 0
#else
    #define NULL ((void *)0)
#endif

*/
class Test
{
public:
	void TestWork(int index)
	{
		std::cout << "TestWork 1" << std::endl;
	}
	void TestWork(int * index)
	{
		std::cout << "TestWork 2" << std::endl;
	}
};

void test_nullptr()
{
	Test test;
	test.TestWork(NULL);
	test.TestWork(nullptr);
}


/*
stl container 和 数组里都能用 for (auto i:array) 的方式访问
*/
#include <list>
typedef struct tag_MYDATA
{
	int index;
	union {
		short s[2];
		char c[4];
		int a;
	};
	tag_MYDATA(int ind, int b)
	{
		index = ind;
		a = b;
	}
	tag_MYDATA()
	{
		index = 0;
		a = 0;
	}
}MYDATA;
bool mydata_comparator(const MYDATA& a, const MYDATA& b)
{
	return a.index >= b.index;
}
void test_for()
{
	
	MYDATA array[10] = { {1,1},{ 2,2 },{ 3,3 },{ 4,4 },{ 5,5 },{ 6,6 } };
	for (auto i : array) {
		std::cout << "array for each " << i.index << " a " << i.a << std::endl;
	}

	std::list<MYDATA> list;
	list.push_back(MYDATA(1, 10000)); // short 2^16 65536
	list.push_back(MYDATA(2, 20000));
	list.push_back(MYDATA(3, 300000));
	list.push_back(MYDATA(4, 4000000));
	list.push_back(MYDATA(5, 5000000)); // i.s[1] << 16 + i.s[0] == i.a

	for (auto i : list) {
		std::cout << "list for each " << i.index << " a " << i.a << " s0 " << i.s[0] << " s1 " << i.s[1] << std::endl;
	}
}