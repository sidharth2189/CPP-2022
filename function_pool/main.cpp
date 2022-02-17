#include "function_pool.h"
#include <thread>
#include <iostream>
#include <vector>

void print()
{
	static  int counter = 0;
	std::cout << "Hello World : " << counter++ << std::endl;
}

int main()
{
	// Create an object of class functionpool
	FunctionPool f;

	// Create a vector of threads
	std::vector<std::thread> thread_pool;

	// Check number of threads supported by hardware
	unsigned int n = std::thread::hardware_concurrency();
	std::cout << "Hardware concurrency : " << n << std::endl;


	for(int i = 0; i< n; i++)
	{
		thread_pool.emplace_back(std::thread(&FunctionPool::run, &f));
	}
		
	for(int i = 0 ; i < 100 ; i++)
	{
		f.push(print);
	}
	
	f.done();
	
	for(int i = 0; i < 5; i++)
	{
		if(thread_pool.at(i).joinable())
		{
			thread_pool.at(i).join();
		}
	}
}

