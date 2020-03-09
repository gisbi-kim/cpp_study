/*
  tested on https://wandbox.org/
*/

#include <iostream>
#include <vector>

using std::cout;
using std::endl;

class Point
{
    int x_;
    int y_;
    
public:
    Point ( int _a, int _b )
    {
        this->x_ = _a;
        this->y_ = _b;
        cout << "Point (int, int)" << endl;
    } // ctor
    
    Point ( std::initializer_list<int> _s )
    {
        auto it = _s.begin();
        double residuals_sum {0};
        
        this->x_ = *it; ++it;
        this->y_ = *it; ++it;
        
        while ( it != _s.end() )
        {
            residuals_sum = residuals_sum + *it;
            ++it;
        }
        cout << "Point (initialized_list): residual sum is " << residuals_sum << endl;   
    } // ctor
    
    void printMembers( void )
    {
        cout << "x: " << this->x_ << endl;
        cout << "y: " << this->y_ << endl << endl;
    }
};

int main ( int argc, char* argv[] )
{
    Point p1 ( 1, 1 ); p1.printMembers();
    Point p2 { 1, 2 }; p2.printMembers();
    Point p3 { 6, 4, 3, 4 }; p3.printMembers();
    
    return 0;
}
