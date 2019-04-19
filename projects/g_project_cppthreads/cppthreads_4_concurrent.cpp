#include "cppthread_header.h"
#include<iostream>


using namespace std;
#include <condition_variable>
#include <thread>             
#include <mutex> 
/*
��������

*/


std::mutex mtx_condition; // ȫ�ֻ�����.
std::condition_variable cv; // ȫ����������.
bool ready = false; // ȫ�ֱ�־λ.

void do_print_id(int id)
{
	std::unique_lock <std::mutex> lck(mtx_condition);
	while (!ready) // �����־λ��Ϊ true, ��ȴ�...
		cv.wait(lck); // ��ǰ�̱߳�����, ��ȫ�ֱ�־λ��Ϊ true ֮��,
						// �̱߳�����, ��������ִ�д�ӡ�̱߳��id.
	std::cout << "thread " << id << '\n';
}

void go()
{
	std::unique_lock <std::mutex> lck(mtx_condition);
	ready = true; // ����ȫ�ֱ�־λΪ true.
	cv.notify_all(); // ���������߳�.
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

