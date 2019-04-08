#include "stl_headers.h"
#include<iostream>
using namespace std;


/*
连续的固定大小的空间，初始化时要指定大小，不能自动扩充。底层实现为简单数组

1 相对于vector ，不能动态扩充容量，不允许在中间做插入删除动作
2 相对于 非stl的数组 int[] ,增加了迭代器的接口
*/
#include <array>
void test_array(void)
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
源码实现, 原始数组
template<class _Ty,
size_t _Size>
class array
{	// fixed size array of values
public:
	oper ...

_Ty _Elems[_Size];
*/