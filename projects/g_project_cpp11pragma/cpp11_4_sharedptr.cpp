#include "cpp11_header.h"
#include<iostream>
using namespace std;


/*
std::unique_ptr ���жԶ���Ķ���Ȩ��ͬһʱ��ֻ����һ��unique_ptrָ���������ͨ����ֹ�������塢ֻ���ƶ�������ʵ�֣���
unique_ptrָ�뱾����������ڣ���unique_ptrָ�봴��ʱ��ʼ��ֱ���뿪������

std::shared_ptr��װ��new��������̬�ֱ���ڴ棬�������ɿ������ƣ���������ʹ������һ������ָ�����͡�

std::make_shared��װ��new������boost::make_shared֮ǰ��ԭ���Ǽ�Ȼ�ͷ���Դdelete������ָ�븺��
��ôӦ�ð�new��װ��������������˾����Լ�������new����û�е���delete���ƺ���˭���룬˭�ͷŵ�ԭ�򲻷���
C++Ҳ��������һ������

==>  std::shared_ptr���໥���õ�����³��ֵ����� ?? 
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
		�������ö��������std::shared_ptr<Test> p2 = p1��ָ������ü�����1��Ϊ2��
		��p2�˳��������p1�����ü������1��
		��main�����˳���p1�뿪main������������
		��ʱp1�����٣���p1����ʱ����⵽���ü����Ѿ�Ϊ1���ͻ���p1�����������е���delete֮ǰ
		*/
		std::shared_ptr<Test> p2 = p1;
		std::cout << "2 ref:" << p1.use_count() << std::endl;
	}
	std::cout << "3 ref:" << p1.use_count() << std::endl;
}



/*
��std::shared_ptr���Ĳ�����ڸ�ֵ�ǣ�������������ָ��������ӡ�

1 std::shared_ptr�໥���û���ʲô���
2 std::weak_ptr��ν����һ�������
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
	std::shared_ptr<TestB> m_TestB_Ptr; //TestB������ָ��
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
	std::shared_ptr<TestA> m_TestA_Ptr; //TestA������ָ��
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
		/* ����std::shared_ptr<TestA> tmp = m_TestA_Ptr.lock()����std::weak_ptr����ת����std::shared_ptr���� */
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