/*
  tested at https://wandbox.org/
*/

#include <iostream>
#include <cassert>
#include <memory>

using std::cout;
using std::endl;

class MyClass
{
    
public:
    using Ptr = std::shared_ptr<MyClass>;    
//    typedef std::shared_ptr<MyClass> Ptr;

    MyClass() = default;
    MyClass( int _num ): num_(_num)
    {}
    
    void dispNum( void ) { cout << num_ << endl; } 
    
    
private:  
    int num_ = 1; 
    
    
};

int main(int, char *[])
{
    MyClass mc1(2);
    mc1.dispNum();

    MyClass mc2;
    mc2.dispNum();

    MyClass::Ptr mc3 = std::make_shared<MyClass>( 3 );
    mc3->dispNum();
    
    return 0;
}
