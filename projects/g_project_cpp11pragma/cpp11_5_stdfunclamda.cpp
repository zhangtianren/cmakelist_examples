#include "cpp11_header.h"
#include<iostream>
using namespace std;



/*
主要是函数指针的类型以及函数指针调用函数
*/
#include <functional>
int add(int a, int b)
{
	std::cout << "add" << std::endl;
	return a + b;
}

class TestAdd
{
public:
	TestAdd() :c(10) {}
	int Add(int a, int b)
	{
		std::cout << "TestAdd::Add" << std::endl;
		return a + b;
	}
private:
	int c;
};

class Test
{
public:

	void Add(int a, int b)
	{
		std::cout << "sum:" << a + b << std::endl;
	}

	typedef int(*FunType)(int, int);
	/*void Add(FunType fun, int a, int b)
	{
		int sum = fun(a, b);
		std::cout << "sum:" << sum << std::endl;
	}*/

	void Add(std::function<int(int, int)> fun, int a, int b)
	{
		int sum = fun(a, b);
		std::cout << "sum:" << sum << std::endl;
	}
};

void test_functional()
{
	Test test;
	test.Add(1, 2);
	//test.Add(add, 1, 2);

	TestAdd testAdd;
	test.Add(std::bind(&TestAdd::Add, testAdd, std::placeholders::_1, std::placeholders::_2), 1, 2);
}




void test_lamda()
{

	auto localadd = [](int a, int b)->int {
         return a + b;
     };
     int ret = localadd(1, 2);
     std::cout << "ret:" << ret << std::endl;

	Test test;
	test.Add(1, 2);
	//test.Add(add, 1, 2);

	TestAdd testAdd;
	test.Add(std::bind(&TestAdd::Add, testAdd, std::placeholders::_1, std::placeholders::_2), 1, 2);

	// 这里会匹配上 两个接口,导致编译报错的
	test.Add([](int a, int b)->int {
		std::cout << "lamda add fun" << std::endl;
		return a + b;
	}, 1, 2);
}