
#include "function_pool.h"
#include <iostream>


FunctionPool::FunctionPool():
isDone(false)	
{
}

void FunctionPool::push(std::function<void()> func)
{
	m_lock.lock();		
	m_function_pool.push(func);
	m_lock.unlock();		
}

void FunctionPool::done()
{
	isDone = true;
}
	
void FunctionPool::run()
{
	while(true)
	{
		m_lock.lock();
		if(m_function_pool.empty() && isDone)
		{
			std::cout << "Thread exiting" <<std::endl;
			m_lock.unlock();
			return;
		}
		if(!m_function_pool.empty())
		{
			std::function<void()> func = m_function_pool.front();
			m_function_pool.pop();
			func();
		}
		m_lock.unlock();
	}
}


