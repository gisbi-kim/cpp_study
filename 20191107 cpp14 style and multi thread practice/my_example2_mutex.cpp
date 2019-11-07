/*
 * cpp style practice 
*/

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

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
    
    std::mutex mtx;
    auto printThreadInfo = [&mtx](){
        mtx.lock();
        cout << "Thread ID: " << std::this_thread::get_id() << endl;
        mtx.unlock();
    };
    
    for (int thread_idx = 0; thread_idx < num_thread; ++thread_idx)
    {
        // method 1 
        // std::thread _thread = std::thread(printThreadInfo); 
        // threads.push_back(std::move(_thread)); // must use move

        // method 2: same as method 1 
        threads.push_back(std::thread(printThreadInfo));
    }

    for (auto& _thread: threads)
    {
        _thread.join();
    }    
    
    return 0;
}

/* the result example 
Hello World

Thread ID: 122031658571520
Thread ID: 122031632279296
Thread ID: 122031649580800
Thread ID: 122031623440128
Thread ID: 122031640712960

now the result's order is cleaner. 
*/
