#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>

#include "tictoc.h"

using std::cout;
using std::endl;

using milisec = std::chrono::milliseconds;

namespace std{
    using mLG = std::lock_guard<std::mutex>;
    using tmLG = std::lock_guard<std::timed_mutex>;
}

std::mutex m_adder;
std::mutex m_cout;
std::timed_mutex tm_adder;

milisec sleep_interval( 1 );

void worker(int& counter, int _num_repeats = 10000) 
{
    std::thread::id this_id = std::this_thread::get_id();

    // std::tmLG lg(tm_adder);

    // std::this_thread::sleep_for( sleep_interval );

    int i = 0;
    while( i < 10 )
    {
        if( tm_adder.try_lock_for( sleep_interval ) )
        // if( m_adder.try_lock() )
        {
            cout << "[" << this_id << " - " << i << "] num repeat is: " << _num_repeats << endl;

            for (int i = 0; i < _num_repeats; i++) {
                counter += 1;
            }

            tm_adder.unlock();
        }
        else
        {
            std::mLG cout_lg(m_cout);
            cout << "[" << this_id << " - " << i << "] try again... " << endl;
        }
        
        i++;
    }
}


int main() {

    TicToc tic(true);

    int counter = 0;

    std::vector<std::thread> workers;
    for (int i = 0; i < 4; i++) {
        workers.push_back( std::thread(worker, std::ref(counter), 450000) );
    }

    for (int i = 0; i < 4; i++) {
        workers[i].join();
    }

    std::cout << "Counter : " << counter << std::endl;

    tic.toc("time");
}
