#include <iostream>
#include <cassert>
#include <thread>
#include <string>
#include <memory>
#include <utility>
#include <mutex>

using std::cout;
using std::endl;

std::mutex cout_mutex; 

void outerFunc1( void )
{
    while(1)
        cout << 1 << endl;
}

class MyClass
{
    
public:
    using Ptr = std::shared_ptr<MyClass>;    
    
    void dispNum( void ) { cout << name_ << " starts from: " << start_num_ << endl; } 
    
    void displayAndIncreaseNum( void )
    {
        while(1)
        {
            if( curr_num_ < end_num_ )
            {
                cout_mutex_.lock();
                    cout << name_ << ": " << curr_num_ << endl; 
                    curr_num_ = curr_num_ + 1; 
                cout_mutex_.unlock();
            }
            else
            {
                break;
            }
        }
    }

    MyClass() = default;
    
    MyClass( std::string _name, std::pair<int, int> _range )
        : name_(_name), start_num_(_range.first), end_num_(_range.second),
          curr_num_(start_num_),
          cout_mutex_(cout_mutex)
    {   
    }

    ~MyClass()
    {
    }
    
private:  
    std::string name_ { "NoName" };
        
    int start_num_; 
    int end_num_;
    int curr_num_;
   
    std::mutex& cout_mutex_;

};


int main(int, char *[])
{
    MyClass mc1("mc1", std::make_pair(1, 10000));
    std::thread mc1_thread( &MyClass::displayAndIncreaseNum, mc1 );
    
    MyClass mc2("mc2", std::make_pair(5000, 60000));
    std::thread mc2_thread( &MyClass::displayAndIncreaseNum, mc2 );
    
    MyClass::Ptr mc3 = std::make_shared<MyClass>("mc3", std::make_pair(-10000, 0));
    std::thread mc3_thread( &MyClass::displayAndIncreaseNum, *mc3 );

    mc1_thread.join();
    mc2_thread.join();
    mc3_thread.join();

    return 0;
}
