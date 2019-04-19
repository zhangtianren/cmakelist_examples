
#include "cppthread_header.h"
#include <thread>

int main(void)
{
	//test_newthread();
	//test_threadpool();
	test_customer_consumer();

	std::this_thread::sleep_for(std::chrono::seconds(100));
 	int a = 0;
}