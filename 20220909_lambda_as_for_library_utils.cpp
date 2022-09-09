// $ g++ prog.cc -Wall -Wextra -std=gnu++2a

#include <iostream>
#include <utility>
#include <algorithm>
#include <list>
#include <vector>

using std::cout;
using std::endl;

namespace utils {

auto print = []<typename Vector>(const Vector& vec) -> void {
    cout << "The vector has elements: ";
    for(auto& elm: vec) {
        cout << elm << " ";
    }
    cout << endl;
};

}

int main() 
{
    std::vector<int> list = {2, 1, 0, -4, 3, 100, 2, 3};
    utils::print(list);
    
    std::sort(list.begin(), list.end());
    utils::print(list);
    
}
