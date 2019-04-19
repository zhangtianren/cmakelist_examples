#include "cppthread_header.h"

#include<iostream>
using namespace std;

#include <mutex>
#include <thread>


/*
线程之间的锁有：互斥锁、条件锁、自旋锁、读写锁、递归锁
1 互斥锁（Mutex）
mutex: 提供了核心函数 lock() 和 unlock()，以及非阻塞方法的try_lock()方法，一旦互斥量不可用，该方法会立即返回。

互斥锁用于控制多个线程对他们之间共享资源互斥访问的一个信号量。也就是说是为了避免多个线程在某一时刻同时操作一个共享资源.
在某一时刻，只有一个线程可以获取互斥锁，在释放互斥锁之前其他线程都不能获取该互斥锁。如果其他线程想要获取这个互斥锁，那么这个线程只能以阻塞方式进行等待

2 recursive_mutex 递归 Mutex
std::recursive_mutex 允许同一个线程对互斥量多次上锁（即递归上锁），来获得对互斥量对象的多层所有权，
std::recursive_mutex 释放互斥量时需要调用与该锁层次深度相同次数的 unlock()，可理解为 lock() 次数和 unlock() 次数相同

3 timed_mutex 定时 Mutex 
std::time_mutex 比 std::mutex 多了两个成员函数，try_lock_for()，try_lock_until()。
try_lock_for 函数接受一个时间范围，表示在这一段时间范围之内线程如果没有获得锁则被阻塞住
如果在此期间其他线程释放了锁，则该线程可以获得对互斥量的锁，如果超时（即在指定时间内还是没有获得锁），则返回 false。
try_lock_until 函数则接受一个时间点作为参数，在指定时间点未到来之前线程如果没有获得锁则被阻塞住，
如果在此期间其他线程释放了锁，则该线程可以获得对互斥量的锁，如果超时（即在指定时间内还是没有获得锁），则返回 false。

4 recursive_timed_mutex 定时递归 Mutex

5 std::shared_mutex 共享锁
shared_mutex 比一般的 mutex 多了函数 lock_shared() / unlock_shared()，允许多个（读者）线程同时加锁、解锁，而 shared_lock 则相当于共享版的 lock_guard。
对 shared_mutex 使用 lock_guard 或 unique_lock 就达到了写者独占的目的。

方便线程上锁
std::lock_guard 
std::unique_lock

例如
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