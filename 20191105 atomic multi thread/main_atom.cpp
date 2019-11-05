/*
 * tested on https://www.onlinegdb.com/online_c++_compiler
*/

#include <iostream>
#include <vector>
#include <iostream>
#include <string>
#include <atomic>
#include <thread>
#include <functional>

using std::cout;
using std::endl;
using std::string;
using std::vector;

using atomint = std::atomic<int>;
using vecatomi = std::vector<atomint>;
using veci = std::vector<int>;

template<typename T>
void disp(const T& message)
{
    cout << message << endl;
}

template<typename T>
void incr(T& counter, int num_inc)
{
    veci v(num_inc);   
    for(auto& vi: v)
    {
        ++counter;
    } 
}

template<typename T>
struct Cincr
{
    int num_inc;

    Cincr(int _num_inc)
    : num_inc(_num_inc)
    {
    }
    
    void operator()(T& counter)
    {
        veci v(num_inc);   
        for(auto& vi: v)
        {
            ++counter;
        } 
    }
};

#define ATOMIC_INT 1

int main(void)
{
    //
    disp("The program starts...\n");

    #if ATOMIC_INT
    atomint counter{0};
    #else
    int counter{0};
    #endif
    
    //
    int num_try{8};
    for (int try_idx =0; try_idx < num_try; ++try_idx)
    {
        counter = 0; // reset
        
        int num_threads{10};
        vector<std::thread> threads;
        for (int thread_idx =0; thread_idx < num_threads; ++thread_idx)
        {
            #if ATOMIC_INT
            // threads.push_back(std::thread{incr<atomint>, std::ref(counter), 10000});
            threads.push_back(std::thread{Cincr<atomint>(10000), std::ref(counter)}); // functor version
            #else
            //threads.push_back(std::thread{incr<int>, std::ref(counter), 10000});
            threads.push_back(std::thread{Cincr<int>(10000), std::ref(counter)}); // functor version
            #endif
        }
        
        for (auto& thr: threads)
        {
            thr.join();
        }
        
        //
        cout << counter << endl;
    }

    return 0;
}



