#include "cpp11_header.h"
#include<iostream>
using namespace std;


/*
std::unique_ptr 持有对对象的独有权，同一时刻只能有一个unique_ptr指向给定对象（通过禁止拷贝语义、只有移动语义来实现）。
unique_ptr指针本身的生命周期：从unique_ptr指针创建时开始，直到离开作用域。

std::shared_ptr包装了new操作符动态分别的内存，可以自由拷贝复制，基本上是使用最多的一个智能指针类型。

std::make_shared封装了new方法，boost::make_shared之前的原则是既然释放资源delete由智能指针负责，
那么应该把new封装起来，否则会让人觉得自己调用了new，但没有调用delete，似乎与谁申请，谁释放的原则不符。
C++也沿用了这一做法。

==>  std::shared_ptr在相互引用的情况下出现的问题 ?? 
*/
#include <memory>
class Test
{
public:
	Test()
	{
		std::cout << "Test()" << std::endl;
	}
	~Test()
	{
		std::cout << "~Test()" << std::endl;
	}
};

void test_sharedptr()
{
	std::shared_ptr<Test> p1 = std::make_shared<Test>();
	std::cout << "1 ref:" << p1.use_count() << std::endl;
	{
		/*
		随着引用对象的增加std::shared_ptr<Test> p2 = p1，指针的引用计数有1变为2，
		当p2退出作用域后，p1的引用计数变回1，
		当main函数退出后，p1离开main函数的作用域，
		此时p1被销毁，当p1销毁时，检测到引用计数已经为1，就会在p1的析构函数中调用delete之前
		*/
		std::shared_ptr<Test> p2 = p1;
		std::cout << "2 ref:" << p1.use_count() << std::endl;
	}
	std::cout << "3 ref:" << p1.use_count() << std::endl;
}



/*
与std::shared_ptr最大的差别是在赋值是，不会引起智能指针计数增加。

1 std::shared_ptr相互引用会有什么后果
2 std::weak_ptr如何解决第一点的问题
*/

#ifdef _ERROR_REFER_
#include <memory>
class TestB;
class TestA
{
public:
	TestA()
	{
		std::cout << "TestA()" << std::endl;
	}
	void ReferTestB(std::shared_ptr<TestB> test_ptr)
	{
		m_TestB_Ptr = test_ptr;
	}
	~TestA()
	{
		std::cout << "~TestA()" << std::endl;
	}
private:
	std::shared_ptr<TestB> m_TestB_Ptr; //TestB的智能指针
};

class TestB
{
public:
	TestB()
	{
		std::cout << "TestB()" << std::endl;
	}

	void ReferTestB(std::shared_ptr<TestA> test_ptr)
	{
		m_TestA_Ptr = test_ptr;
	}
	~TestB()
	{
		std::cout << "~TestB()" << std::endl;
	}
	std::shared_ptr<TestA> m_TestA_Ptr; //TestA的智能指针
};

#else
class TestB;
class TestA
{
public:
	TestA()
	{
		std::cout << "TestA()" << std::endl;
	}
	void ReferTestB(std::shared_ptr<TestB> test_ptr)
	{
		m_TestB_Ptr = test_ptr;
	}
	void TestWork()
	{
		std::cout << "TestA::TestWork()" << std::endl;
	}
	~TestA()
	{
		std::cout << "~TestA()" << std::endl;
	}
private:
	std::weak_ptr<TestB> m_TestB_Ptr;
};

class TestB
{
public:
	TestB()
	{
		std::cout << "TestB()" << std::endl;
	}

	void ReferTestB(std::shared_ptr<TestA> test_ptr)
	{
		m_TestA_Ptr = test_ptr;
	}
	void TestWork()
	{
		std::cout << "TestB::TestWork()" << std::endl;
	}
	~TestB()
	{
		/* 调用std::shared_ptr<TestA> tmp = m_TestA_Ptr.lock()，把std::weak_ptr类型转换成std::shared_ptr类型 */
		std::shared_ptr<TestA> tmp = m_TestA_Ptr.lock();
		tmp->TestWork();
		std::cout << "2 ref a:" << tmp.use_count() << std::endl;
		std::cout << "~TestB()" << std::endl;
	}
	std::weak_ptr<TestA> m_TestA_Ptr;
};
#endif
void test_weakptr()
{
	std::shared_ptr<TestA> ptr_a = std::make_shared<TestA>();
	std::shared_ptr<TestB> ptr_b = std::make_shared<TestB>();
	ptr_a->ReferTestB(ptr_b);
	ptr_b->ReferTestB(ptr_a);

	std::cout << "1 ref a:" << ptr_a.use_count() << std::endl;
	std::cout << "1 ref b:" << ptr_a.use_count() << std::endl;
}