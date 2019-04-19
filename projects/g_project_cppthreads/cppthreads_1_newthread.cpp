#include "cppthread_header.h"
#include<iostream>
using namespace std;



// cout不是线程安全的
// printf是线程安全的
/*
http://www.cplusplus.com/reference/multithreading/
c++的线程使用 <thread> SGI标准中对多线程的支持，有thread, mutex, future, atomic, condition_variable
*/
#include <thread>
typedef struct tag_thread_param
{
	std::string str;
	char c;
	int index;
	tag_thread_param() {}
	tag_thread_param(std::string s,char cc, int i)
	{
		str = s; c = cc, index = i;
	}
	void operator=(tag_thread_param &param)
	{
		this->str = param.str + "cp";
		this->c = param.c;
		this->index = param.index + 1;
	}

}thread_param;

void thread_method1()
{
	std::thread::id this_id = std::this_thread::get_id();
	//std::cout << "thread_method1 thread id " << this_id <<std::endl;

	for (int i = 0; i < 5; i++)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		//std::cout << this_id << " index " << i << std::endl;
		printf("[%s] %d %s %d\n", __FUNCTION__, this_id, "inxde", i);
	}
}

void thread_method2()
{
	std::thread::id this_id = std::this_thread::get_id();
	//std::cout << "thread_method2 thread id " << this_id << std::endl;

	for (int i = 0; i < 5; i++)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		//std::cout << this_id << " index " << i << std::endl;
		printf("[%s] %d %s %d\n", __FUNCTION__, this_id, "inxde", i);
	}
}


void thread_method_withparam1(thread_param stParam)
{
	std::thread::id this_id = std::this_thread::get_id();
	//std::cout << "thread_method_withparam1 thread id " << this_id << std::endl;

	for (int i = 0; i < 5; i++)
	{
		//std::cout << this_id << " index " << i << " param " << stParam.str.c_str() << std::endl;
		printf("[%s] %d %s %d %s %s \n", __FUNCTION__, this_id, "inxde", i, "param", stParam.str.c_str());

		std::this_thread::sleep_for(std::chrono::seconds(1));//1秒
		//std::this_thread::sleep_for(std::chrono::milliseconds(1));//1毫秒
		//std::this_thread::sleep_for(std::chrono::microseconds(1));//1微秒
	}
}

void thread_method_withparam2(thread_param* pstParam)
{
	std::thread::id this_id = std::this_thread::get_id();
	//std::cout << "thread_method_withparam2 thread id " << this_id << std::endl;

	for (int i = 0; i < 5; i++)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		//std::cout << this_id << " index " << i << " param " << pstParam->str.c_str() << std::endl;
		printf("[%s] %d %s %d %s %s \n", __FUNCTION__, this_id, "inxde", i, "param", pstParam->str.c_str());
	}
}

class ThreadClass
{
public:
	ThreadClass() { stParamInner.str = "abc"; stParamInner.index = 2; stParamInner.c = 'b'; }

	std::thread makethread_method1() { return std::thread(&ThreadClass::thread_inclass_method1, this); }
	std::thread makethread_method2() { return std::thread(&ThreadClass::thread_inclass_method2, this); }
	std::thread makethread_withparam1() { return std::thread(&ThreadClass::thread_inclass_withparam1, this, stParamInner); }
	std::thread makethread_withparam2() { return std::thread(&ThreadClass::thread_inclass_withparam2, this, &stParamInner); }

	void thread_inclass_method1()
	{
		std::thread::id this_id = std::this_thread::get_id();
		//std::cout << "thread_inclass_method1 thread id " << this_id << std::endl;

		for (int i = 0; i < 5; i++)
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
			//std::cout << this_id << " index " << i << std::endl;
			printf("[%s] %d %s %d\n", __FUNCTION__, this_id, "inxde", i);
		}
	}
	void thread_inclass_method2()
	{
		std::thread::id this_id = std::this_thread::get_id();
		//std::cout << "thread_inclass_method2 thread id " << this_id << std::endl;

		for (int i = 0; i < 5; i++)
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
			//std::cout << this_id << " index " << i << std::endl;
			printf("[%s] %d %s %d\n", __FUNCTION__, this_id, "inxde", i);
		}
	}

	void thread_inclass_withparam1(thread_param stParam)
	{
		std::thread::id this_id = std::this_thread::get_id();
		//std::cout << "thread_inclass_withparam1 thread id " << this_id << std::endl;

		for (int i = 0; i < 5; i++)
		{
			//std::cout << this_id << " index " << i << " param " << stParam.str.c_str() << std::endl;
			printf("[%s] %d %s %d %s %s \n", __FUNCTION__, this_id, "inxde", i, "param", stParam.str.c_str());
			std::this_thread::sleep_for(std::chrono::seconds(1));//1秒
																 //std::this_thread::sleep_for(std::chrono::milliseconds(1));//1毫秒
																 //std::this_thread::sleep_for(std::chrono::microseconds(1));//1微秒
		}
	}
	void thread_inclass_withparam2(thread_param* pstParam)
	{
		std::thread::id this_id = std::this_thread::get_id();
		//std::cout << "thread_inclass_withparam2 thread id " << this_id << std::endl;

		for (int i = 0; i < 5; i++)
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
			//std::cout << this_id << " index " << i << " param " << pstParam->str.c_str() << std::endl;
			printf("[%s] %d %s %d %s %s \n", __FUNCTION__, this_id, "inxde", i, "param", pstParam->str.c_str());
		}
	}

private:
	thread_param stParamInner;
};

void test_newthread()
{
	ThreadClass obj;
	thread_param param = { "sss", 'a', 99 };

	std::thread thread1 = std::thread(thread_method1);
	std::thread thread2 = std::thread(thread_method2);
	std::thread thread3 = std::thread(thread_method_withparam1, param);
	std::thread thread4 = std::thread(thread_method_withparam2, &param);
	
	std::thread thread1x = obj.makethread_method1();
	std::thread thread2x = obj.makethread_method2();
	std::thread thread3x = obj.makethread_withparam1();
	std::thread thread4x = obj.makethread_withparam2();

	// 两种都可行 参数没有执行拷贝的动作
	/*std::thread thread1x = std::thread(&ThreadClass::thread_inclass_method1, &obj);
	std::thread thread2x = std::thread(&ThreadClass::thread_inclass_method2, &obj);
	std::thread thread3x = std::thread(&ThreadClass::thread_inclass_withparam1, &obj, param);
	std::thread thread4x = std::thread(&ThreadClass::thread_inclass_withparam2, &obj, &param);*/

	thread1.join();
	thread2.join();
	thread3.join();
	thread4.join();

	thread1x.join();
	thread2x.join();
	thread3x.join();
	thread4x.join();
}