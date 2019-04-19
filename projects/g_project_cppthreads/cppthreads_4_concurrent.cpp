#include "cppthread_header.h"
#include<iostream>


using namespace std;
#include <condition_variable>
#include <thread>             
#include <mutex> 
/*
条件变量

*/


std::mutex mtx_condition; // 全局互斥锁.
std::condition_variable cv; // 全局条件变量.
bool ready = false; // 全局标志位.

void do_print_id(int id)
{
	std::unique_lock <std::mutex> lck(mtx_condition);
	while (!ready) // 如果标志位不为 true, 则等待...
		cv.wait(lck); // 当前线程被阻塞, 当全局标志位变为 true 之后,
						// 线程被唤醒, 继续往下执行打印线程编号id.
	std::cout << "thread " << id << '\n';
}

void go()
{
	std::unique_lock <std::mutex> lck(mtx_condition);
	ready = true; // 设置全局标志位为 true.
	cv.notify_all(); // 唤醒所有线程.
}

void test_threadcondition()
{
	std::thread threads[10];
	// spawn 10 threads:
	for (int i = 0; i < 10; ++i)
		threads[i] = std::thread(do_print_id, i);

	std::cout << "10 threads ready to race...\n";
	go(); // go!

	for (auto & th : threads)
		th.join();
}

