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

        // previous 
        /*
        mtx.lock();
        cout << "Thread ID: " << std::this_thread::get_id() << endl;
        mtx.unlock();
        이 코드는 unlock 이전에 예외가 발생하면 뮤텍스가 언락되지 않게 된다는 단점이 있다. 
        대신, 락가드를 이용하면 코드블락을 빠져나갈때 자동으로 잠금이 해제된다. (스마트 포인터처럼)
        */

        // modified 
        std::lock_guard<std::mutex> guard(mtx);
        cout << "Thread ID: " << std::this_thread::get_id() << endl;

        /* Further:
        동일한 mutex 를 재귀적으로 사용해야 할 때는 recursive_mutex 를 이용하자. 
        */
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
