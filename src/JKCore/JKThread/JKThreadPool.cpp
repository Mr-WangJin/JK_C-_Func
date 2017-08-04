#include "JKThreadPool.h"

USING_JK_NAMESPACE


// the constructor just launches some amount of workers
JKThreadPool::JKThreadPool(size_t count)
	: stop(false)
{
	for (size_t i = 0; i < count; ++i)
		vecThreads.emplace_back([this]{
		for (;;)
		{
			std::function<void()> task;
			{
				std::unique_lock<std::mutex> lock(this->queueMutex);
				this->conditionVar.wait(lock, [this] { return this->stop || !this->queueTasks.empty();});
				if (this->stop && this->queueTasks.empty())
					return;
				task = std::move(this->queueTasks.front());
				this->queueTasks.pop();
			}

			task();
		}
	});
}

// the destructor joins all threads
JKThreadPool::~JKThreadPool()
{
	{
		std::unique_lock<std::mutex> lock(queueMutex);
		stop = true;
	}
	conditionVar.notify_all();
	for (std::thread &worker : vecThreads)
		worker.join();
}