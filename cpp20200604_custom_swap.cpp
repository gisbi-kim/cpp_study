// swap algorithm example (C++11)
#include <iostream>     // std::cout
#include <utility>      // std::swap
#include <vector>
#include <algorithm>
#include <string>

using std::vector;
using std::cout;
using std::endl;


namespace Myutil
{
  template <class T> 
  void swap (T& _a, T& _b)
  {
    T c(_a);
    _a = _b;
    _b = c;
  }

  template <class T> 
  void dispVec (vector<T>& _vec, std::string _init_msg = "") 
  { 
    cout << _init_msg;
    std::for_each(
        std::begin(_vec), 
        std::end(_vec), 
        [] ( T& elm ) { cout << elm << " "; }
      ); cout << endl;
  };

}


int main () {

  int x=10, y=20;                  // x:10 y:20
  std::cout << x << ", " << y << std::endl;

  Myutil::swap(x,y);                  // x:20 y:10
  std::cout << x << ", " << y << std::endl;

  vector<float> vec1 {1.8, 2.4, 3.53, 2.35, 3.2};   
  vector<float> vec2 {10, 20, 30, 40.3};
  Myutil::dispVec( vec1 , "vec1: ");
  Myutil::dispVec( vec2 , "vec2: ");

  // std::swap(vec1, vec2);              // foo: 10 20 30 40   bar: ?  ?  ?  ?
  Myutil::swap(vec1, vec2);              // foo: 10 20 30 40   bar: ?  ?  ?  ?
  Myutil::dispVec( vec1 , "vec1: ");
  Myutil::dispVec( vec2 , "vec2: ");
    
  cout << endl;
  return 0;
}
