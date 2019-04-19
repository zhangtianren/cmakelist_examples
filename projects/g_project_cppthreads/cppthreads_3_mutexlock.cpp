#include "cppthread_header.h"

#include<iostream>
using namespace std;

#include <mutex>
#include <thread>


/*
�߳�֮������У���������������������������д�����ݹ���
1 ��������Mutex��
mutex: �ṩ�˺��ĺ��� lock() �� unlock()���Լ�������������try_lock()������һ�������������ã��÷������������ء�

���������ڿ��ƶ���̶߳�����֮�乲����Դ������ʵ�һ���ź�����Ҳ����˵��Ϊ�˱������߳���ĳһʱ��ͬʱ����һ��������Դ.
��ĳһʱ�̣�ֻ��һ���߳̿��Ի�ȡ�����������ͷŻ�����֮ǰ�����̶߳����ܻ�ȡ�û���������������߳���Ҫ��ȡ�������������ô����߳�ֻ����������ʽ���еȴ�

2 recursive_mutex �ݹ� Mutex
std::recursive_mutex ����ͬһ���̶߳Ի�����������������ݹ�������������öԻ���������Ķ������Ȩ��
std::recursive_mutex �ͷŻ�����ʱ��Ҫ�����������������ͬ������ unlock()�������Ϊ lock() ������ unlock() ������ͬ

3 timed_mutex ��ʱ Mutex 
std::time_mutex �� std::mutex ����������Ա������try_lock_for()��try_lock_until()��
try_lock_for ��������һ��ʱ�䷶Χ����ʾ����һ��ʱ�䷶Χ֮���߳����û�л����������ס
����ڴ��ڼ������߳��ͷ�����������߳̿��Ի�öԻ����������������ʱ������ָ��ʱ���ڻ���û�л���������򷵻� false��
try_lock_until ���������һ��ʱ�����Ϊ��������ָ��ʱ���δ����֮ǰ�߳����û�л����������ס��
����ڴ��ڼ������߳��ͷ�����������߳̿��Ի�öԻ����������������ʱ������ָ��ʱ���ڻ���û�л���������򷵻� false��

4 recursive_timed_mutex ��ʱ�ݹ� Mutex

5 std::shared_mutex ������
shared_mutex ��һ��� mutex ���˺��� lock_shared() / unlock_shared()�������������ߣ��߳�ͬʱ�������������� shared_lock ���൱�ڹ����� lock_guard��
�� shared_mutex ʹ�� lock_guard �� unique_lock �ʹﵽ��д�߶�ռ��Ŀ�ġ�

�����߳�����
std::lock_guard 
std::unique_lock

����
// critical section (exclusive access to std::cout signaled by lifetime of lck):
std::unique_lock<std::mutex> lck (mtx);
// using a local lock_guard to lock mtx guarantees unlocking on destruction :
std::lock_guard<std::mutex> lck (mtx);
*/

volatile int counter(0);		// non-atomic counter
std::mutex mtx;					// locks access to counter

void attempt_10k_increases() {
	for (int i = 0; i<10000; ++i) {
		if (mtx.try_lock()) {   // only increase if currently not locked:
			++counter;
			mtx.unlock();
		}
	}
}
void test_mutex()
{
	std::thread threads[10];
	for (int i = 0; i<10; ++i)
		threads[i] = std::thread(attempt_10k_increases);

	for (auto& th : threads) th.join();
	std::cout << counter << " successful increases of the counter.\n";

}



std::timed_mutex time_mtx;

void fireworks() {
	// waiting to get a lock: each thread prints "-" every 200ms:
	while (!time_mtx.try_lock_for(std::chrono::milliseconds(200))) {
		std::cout << "-";
	}
	// got a lock! - wait for 1s, then this thread prints "*"
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	std::cout << "*\n";
	time_mtx.unlock();
}

void test_timemutex()
{
	std::thread threads[10];
	// spawn 10 threads:
	for (int i = 0; i<10; ++i)
		threads[i] = std::thread(fireworks);

	for (auto& th : threads) th.join();
}