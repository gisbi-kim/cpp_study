// tested on https://wandbox.org/

#include <iostream>
#include <cstdlib>
#include <filesystem>

using std::cout;
using std::endl;
namespace fs = std::filesystem;

int main()
{
    std::cout << "Hello, Wandbox!" << std::endl;
    
//    std::filesystem::path p1(L"/usr");
    fs::path p1(L"/usr");
    cout << p1 << endl;
    cout << p1.c_str() << endl;
    
    decltype(p1) p1_2 = p1;
    cout << p1_2 << endl;

    auto p1_3 = p1;
    cout << p1_3 << endl;
    
    fs::space_info s1 = space(p1);
    cout << s1.capacity << endl;
    cout << s1.free << endl;
    
    for(auto& _p: fs::directory_iterator(p1))
    {
        cout << _p.path() << '\n';
    }
    

}
