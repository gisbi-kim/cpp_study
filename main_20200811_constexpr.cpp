#include <iostream>
#include <numeric>
#include <vector>

constexpr int n = 0;
constexpr int n2 {0};

std::vector<int> getVectorInitialized0toN( int _numel )
{

  std::vector< int > ivec( _numel );
  std::iota(ivec.begin(), ivec.end(), 0); // ivec will become: [0..99]
  return ivec;
}


template<typename T>
constexpr T square( T x )
{
  return x * x;
}

using Int64 = unsigned long long;
using VecI = std::vector<int>;
using std::cout;
using std::endl;

int main() {
  std::cout << "Hello World!\n";
  cout << n2 << endl;

  int num_elmenet = 100000;
  VecI vec = getVectorInitialized0toN( num_elmenet );
  for( auto & _i: vec)
  {
    cout << "i: " << _i 
         << ", i*i: " << square<Int64>( _i ) << endl;
    // VecI vec = getVectorInitialized0toN(3);

  }
}
