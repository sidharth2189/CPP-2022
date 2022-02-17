template <typename T>
void Qvs<T>::push(T const& a) // Add an element at the end
{
    // mtx.lock();   // uncomment if datastructure is not thread safe
    queue_.emplace_back(a);
    // mtx.unlock(); // uncomment if datastructure is not thread safe
}

template <typename T>
void Qvs<T>::pop() // remove first element
{
    // mtx.lock();   // uncomment if datastructure is not thread safe
    queue_.erase(queue_.begin());
    // mtx.unlock(); // uncomment if datastructure is not thread safe
}

template <typename T>
T Qvs<T>::front() // Return first element
{
    // mtx.lock();   // uncomment if datastructure is not thread safe
    return queue_.begin();
    // mtx.unlock(); // uncomment if datastructure is not thread safe
}

template <typename T>
void Qvs<T>::print_q() // Print queue
{
    for (T itr: queue_) {std::cout << itr << std::endl;}
    std::cout << "-----end-----" << std::endl;
}