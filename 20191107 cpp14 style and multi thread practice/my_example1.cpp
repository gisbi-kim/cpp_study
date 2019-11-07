/*
 * cpp style practice 
*/

#include <iostream>
#include <vector>
#include <thread>

using std::cout;
using std::endl;
using std::vector;

#define lc cout << endl

auto main() -> int
{
    cout<<"Hello World" << endl;
    lc;

    int num_thread = 5;
    vector<std::thread> threads;
    threads.reserve(num_thread);
    
    auto printThreadInfo = [](){cout << "Thread ID: " << std::this_thread::get_id() << endl;};
    
    for (int thread_idx = 0; thread_idx < num_thread; ++thread_idx)
    {
        std::thread _thread = std::thread(printThreadInfo); 
        threads.push_back(std::move(_thread)); // must use move
    }

    for (auto& _thread: threads)
    {
        _thread.join();
    }    
    
    return 0;
}

/* the result example 
Hello World

Thread ID: 119389716649728
Thread ID: 119389699188480
Thread ID: 119389690541824
Thread ID: 119389682136832
Thread ID: 119389707986688

*/
