#include "JKThread.h"

#include <thread>
#include <mutex>
#include <stdio.h>


void func()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(10000));

	printf("thread1");

}


void JKThread::testThread()
{
	std::thread t(func);
	t.detach();
	
	int data[3];
	for (int i : data)
	{
		printf("d");
	}


	printf("thread2");
}

volatile double counter(0);
std::mutex mtx;
std::timed_mutex time_mtx;

void attempt_increase()
{
// 	for (int i = 0; i< 10000; ++i)
// 	{
// 		if(mtx.try_lock())
// 		{
// 			//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
// 
// 			printf("%i \t\t",std::this_thread::get_id());
// 
// 			++counter;
// 			printf("%d\n", counter);
// 			mtx.unlock();
// 		}
// 	}
	while(time_mtx.try_lock_for(std::chrono::milliseconds(200)))
	{
		printf("- \t\t %f \n",std::this_thread::get_id());
	}

	++counter;
	printf("%f\n", counter);
	time_mtx.unlock();
}


void JKThread::testMutex()
{
	std::thread threads[10];
	for(int i = 0; i< 10; ++i)
	{
		threads[i] = std::thread(attempt_increase);
	}
// 	for (auto& th : threads)
// 	{
// 		printf("%d\n", th.get_id());
// 		th.detach();
// 	}

	printf("%f", counter);

}
