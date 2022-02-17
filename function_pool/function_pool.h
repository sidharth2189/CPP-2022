#ifndef _FUNCTION_POOL_H
#define _FUNCTION_POOL_H

#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>


class FunctionPool
{
	public:
	FunctionPool();
	~FunctionPool() = default;
	void push(std::function<void()> func);
	void pop();
	void run();
	void done();
			
	private:
	std::queue<std::function<void()>> m_function_pool;
	bool isDone;
	bool isFunctionAvailable;
	std::condition_variable m_condition;
	std::mutex m_lock;
	
};	

#endif
