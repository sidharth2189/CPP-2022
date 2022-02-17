#include <vector>
#include <mutex>
#include <iostream>

template <typename T>
class Qvs
{
    std::vector<T> queue_;

    // uncomment if datastructure is not thread safe
    // std::mutex mtx;
public:
    Qvs() = default;
    void push(T const&);
    void pop();
    T front();
    void print_q();
    ~Qvs() = default;
};

#include "queue.cpp"