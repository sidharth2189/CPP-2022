#include "queue.h"

int main()
{
    // Create a queue
    Qvs<int> q;

    // Add elements to queue
    q.push(1);
    q.push(2);
    q.push(3);

    // print queue
    q.print_q();
    
    // Remove an first item from queue
    q.pop();

    // print queue
    q.print_q();
}