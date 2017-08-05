#pragma once

#include "JKCommon/JKCommon.h"
#include "JKCommon/JKBase.h"
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>

BEGIN_JK_NAMESPACE


class JK_API JKThreadPool : public JKBase
{
public:
    JKThreadPool(size_t count = std::thread::hardware_concurrency());
	~JKThreadPool();

	template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args)-> std::future<typename std::result_of<F(Args...)>::type>;

private:
    std::vector< std::thread > vecThreads;

    std::queue<std::function<void()>> queueTasks;
    
    // synchronization
    std::mutex queueMutex;
    std::condition_variable conditionVar;
    bool stop;
};


template<class F, class... Args>
auto JKThreadPool::enqueue(F&& f, Args&&... args)-> std::future<typename std::result_of<F(Args...)>::type>
{
	using return_type = typename std::result_of<F(Args...)>::type;

	auto task = std::make_shared<std::packaged_task<return_type()>>(
		std::bind(std::forward<F>(f), std::forward<Args>(args)...)
		);

	std::future<return_type> res = task->get_future();
	{
		std::unique_lock<std::mutex> lock(queueMutex);

		// don't allow enqueueing after stopping the pool
		if (stop)
			throw std::runtime_error("enqueue on stopped ThreadPool");

		queueTasks.emplace([task]() { (*task)(); });
	}
	conditionVar.notify_one();
	return res;
}

END_JK_NAMESPACE

