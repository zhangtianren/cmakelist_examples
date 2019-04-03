#include "cpp11_header.h"

#include<iostream>
using namespace std;

#include <list>
#include <thread>
#include <atomic>



/*
�ӹ����Ͽ����򵥵�˵��ԭ���������Ͳ��ᷢ�����ݾ�������ֱ�����ڶ��߳��ж����������û����������ӻ�����Դ�������͡�
��ʵ���ϣ��������Ϊ��Щԭ�������ڲ��Լ���������
*/
std::atomic_bool bIsReady = false;
std::atomic_int iCount = 50;
void threadfun1()
{
	if (!bIsReady) {
		bIsReady = true;
		std::this_thread::yield(); // ???
	}
	while (iCount > 0)
	{
		printf("iCount:%d\r\n", iCount--);
	}
}

void test_atomic()
{
	std::cout << "test_atomic" << std::endl;
	std::list<std::thread> lstThread;
	for (int i = 0; i < 10; ++i)
	{
		lstThread.push_back(std::thread(threadfun1));
	}
	for (auto& th : lstThread)
	{
		th.join();
	}

}
/*
ʹ����������ԭ�ӷ���
*/
#include <mutex>
std::mutex lockCount;
int g_iCount = 50;
void threadfun2()
{
	do {
		lockCount.lock();
		if (g_iCount <= 0)
		{
			lockCount.unlock();
			break;
		}
		printf("g_iCount:%d\r\n", g_iCount--);
		lockCount.unlock();
	} while (true);
}


void test_unatomic()
{
	std::cout << "test_unatomic" << std::endl;
	std::list<std::thread> lstThread_mux;
	for (int i = 0; i < 10; ++i)
	{
		lstThread_mux.push_back(std::thread(threadfun2));
	}
	for (auto& th : lstThread_mux)
	{
		th.join();
	}
}



/*
C++11�е�std::condition_variable����
Linux��ʹ��pthread_cond_wait��pthread_cond_signalһ�����������߳����ߣ�ֱ������

��������ͨ��C++11����������
http://www.cplusplus.com/reference/condition_variable/condition_variable/%20condition_variable
*/
#include <condition_variable>
std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void print_id(int id) {
    std::unique_lock<std::mutex> lck(mtx);
    while (!ready) cv.wait(lck);
    // ...
	std::cout << "thread " << id << '\n';
}

void go() {
    std::unique_lock<std::mutex> lck(mtx);
    ready = true;
    cv.notify_all();
}
void test_threadsync()
{
	std::cout << "test_threadsync" << std::endl;
	std::thread threads[10];
	// spawn 10 threads:
	for (int i = 0; i<10; ++i)
		threads[i] = std::thread(print_id, i);

	std::cout << "10 threads ready to race...\n";
	go();                       // go!

	for (auto& th : threads) th.join();
}