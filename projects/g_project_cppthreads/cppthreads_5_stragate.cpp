#include "cppthread_header.h"
#include<iostream>
using namespace std;

#include <thread>
#include <mutex>
#include <condition_variable>
/*
多线程设计模式中，许多常见的经典模式
1 生产者消费者模式
2 读写者模式
*/


/*
生产者消费者模式
1 多个生产者线程产出数据（缓冲区）
2 多个消费者线程消费数据
3 缓冲区满则生产者等待，缓冲区空则消费者等待

互斥信号量+条件等待
*/

#include <queue>

#define COUNT_CUSTOMER 2
#define COUNT_CONSUMER 2

int curr_customer = COUNT_CUSTOMER;
int curr_consumer = COUNT_CONSUMER;
const int max_size = 100;
std::mutex mtx_que;
std::queue<int> que;
std::condition_variable condition_empty;
std::condition_variable condition_full;

void threadfunc_consumer()
{
	while (true)
	{
		int data;
		{
			std::unique_lock <std::mutex> lck(mtx_que);
			if (que.size() == 0)
			{
				printf("consumer %08d waited  empty...\n", std::this_thread::get_id());
				condition_empty.wait(lck);
				continue;
			}

			data = que.front();
			que.pop();
		}
		std::this_thread::sleep_for(std::chrono::seconds(2));
		printf("consumer %08d cost data %d \n", std::this_thread::get_id(), data);
		condition_full.notify_all();
	}
}

void threadfunc_customer(int data)
{
	while (true)
	{
		{
			std::unique_lock<std::mutex> lck(mtx_que);
			if (que.size() >= max_size)
			{
				printf("customer %08d waited  full...\n", std::this_thread::get_id());
				condition_full.wait(lck);
				continue;
			}
			que.push(data);
			condition_empty.notify_all();
		}
		std::this_thread::sleep_for(std::chrono::seconds(2));
		printf("customer %08d newd data %d \n", std::this_thread::get_id(), data);
	}
}

void add_customer()
{
	curr_customer++;
	std::thread t = std::thread(threadfunc_customer, curr_customer);
	t.detach();
}

void add_consumer()
{
	curr_consumer++;
	std::thread t = std::thread(threadfunc_consumer);
	t.detach();
}

void test_customer_consumer()
{
	std::thread customers[COUNT_CUSTOMER];
	std::thread consumers[COUNT_CONSUMER];

	for(int i=0;i< COUNT_CUSTOMER;i++)
	{
		customers[i] = std::thread(threadfunc_customer, i);
	}

	for (int i = 0; i< COUNT_CONSUMER; i++)
	{
		consumers[i] = std::thread(threadfunc_consumer);
	}
	

	char c = 'p';
	while (c != 'q')
	{
		std::cin >> c;
		if (c == 'm')
		{
			add_customer();
		}
		else if (c == 'n')
		{
			add_consumer();
		}
		else if (c == 'p')
		{
			printf("============> print current ++ %d -- %d queue %d\n", curr_customer, curr_consumer, que.size());
		}
	}

	for (auto & th : customers)
		th.join();

	for (auto & th : consumers)
		th.join();
}


std::mutex mtx_read;
std::mutex mtx_write;
int readers = 0;
int writers = 0;
condition_variable condition_canread;
condition_variable condition_canwrite;

// 请求读，若有人在写则都失败，直接返回。否则读成功，读者数+1
bool add_reader()
{
	if (mtx_write.try_lock())
	{
		if (writers > 0)
		{
			mtx_write.unlock();
			return false;
		}
		std::unique_lock<std::mutex> lck(mtx_read);
		readers++;

		mtx_write.unlock();
		return true;
	}
	return false;
}
// 请求读, 若有人在写则读阻塞，等待写者完成。否则读成功，读者数+1
void add_reader_blocked()
{
	std::unique_lock<std::mutex> lck(mtx_write);

	while (true) 
	{
		if (writers > 0)
			condition_canread.wait(lck);

	}

	std::unique_lock<std::mutex> lck(mtx_read);
	readers++;


}
// 读完成，读者数-1
void remove_reader()
{
	std::unique_lock<std::mutex> lck(mtx_read);
	if (readers > 0)
	{
		readers--;
		if (readers == 0)
		{
			condition_canwrite.notify_one();
		}
	}
}

// 请求写，若有其他人在写，后者有人在读则失败，直接返回。否则写成功，写者数+1
bool add_writer()
{

}
// 请求写，若有其他人在写，后者有人在读则阻塞等待，等待其他读者或者写者完成。否则写成功，写者数+1
void add_writer_blocked()
{

}
//写完成，写者数-1
void remove_writer()
{

}


void test_read_write()
{
	std::string strin;
	char inputbuff[20];
	while (strin != "exit")
	{
		std::cin >> inputbuff;
		strin = std::string(inputbuff);
		if (strin == "read")
		{
			if (add_reader())
			{
				printf("reader ++");
			}
		}
		else if (strin == "read-")
		{
			add_consumer();
		}
		else if (strin == "write+")
		{

		}
		else if (strin == "write-")
		{

		}
		else if (strin == "print")
		{
			printf("============> print current readers %d writers %d\n", curr_customer, curr_consumer);
		}
	}
}