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

Thread ID: Thread ID: 129516665267968
129516655974144
Thread ID: 129516628899584
Thread ID: Thread ID: 129516647577344
129516638271232

-> need mutex!!
-> go to example2
*/
