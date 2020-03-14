// This file is a "Hello, world!" in C++ language by GCC for wandbox.
#include <iostream>
#include <cstdlib>
using std::cout;
using std::endl;

template<typename T1>
class MyBaseClass
{
public:
    MyBaseClass ();
    MyBaseClass (T1 _x, T1 _y);    
    virtual ~MyBaseClass () = default;
     
    void printXY () {std::cout << "x: " << x_ << ", " << "y: " << y_ << std::endl;}

private:
    T1 x_;
    T1 y_;
};

template<typename T1>
MyBaseClass<T1>::MyBaseClass(T1 _x, T1 _y)
: x_(_x), y_(_y)
{
}

template<typename T1>
MyBaseClass<T1>::MyBaseClass()
: MyBaseClass(T1(100.7), T1(100.7))
{
}
    
/*
template<typename T1>
class MyChildClass: public MyBaseClass<T1, 2>
{
public:

private:
    T1 z_;
};
*/


int main()
{
    std::cout << "Hello, Wandbox!" << std::endl;

    MyBaseClass<float> base00;
    base00.printXY();

    MyBaseClass<int> base01;
    base01.printXY();

    double xx {3.443463463};
    double yy {1.4243473734342};
    MyBaseClass<double> base1(xx, yy);
    base1.printXY();

}
