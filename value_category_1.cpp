/* result 
  gen obj1
  MyClass default constructor

  gen obj2
  MyClass copy constructor

  gen obj3
  MyClass default constructor

  gen obj4
  MyClass move constructor

  func lvalue test starts
  Inside func_lvalue()
  Elapsed time for func_lvalue(): 1.584e-06s

  func rvalue test starts
  MyClass default constructor
  Inside func_rvalue()
  MyClass destructor
  Elapsed time for func_rvalue(): 4.084e-06s

  func xvalue test starts
  Inside get_xvalue()
  MyClass default constructor
  Elapsed time for get_xvalue(): 2.708e-06s

  ltime : rtime cost ratio is 1 : 2.57828

  some destructors
  MyClass destructor
  MyClass destructor
  MyClass destructor
  MyClass destructor
  MyClass destructor
*/ 

#include <iostream>
#include <utility>
#include <chrono>

class MyClass
{
public:
    MyClass() { std::cout << "MyClass default constructor\n"; }
    MyClass(const MyClass &) { std::cout << "MyClass copy constructor\n"; }
    MyClass(MyClass &&) { std::cout << "MyClass move constructor\n"; }
    ~MyClass() { std::cout << "MyClass destructor\n"; }
};

void func_lvalue(MyClass &my_obj)
{
    std::cout << "Inside func_lvalue()\n";
}

void func_rvalue(MyClass &&my_obj)
{
    std::cout << "Inside func_rvalue()\n";
}

MyClass get_xvalue()
{
    std::cout << "Inside get_xvalue()\n";
    return MyClass();
}

int main()
{
    std::cout << "\ngen obj1" << std::endl;
    MyClass obj1;

    std::cout << "\ngen obj2" << std::endl;
    MyClass obj2 = obj1; // copy constructor, obj1 is an lvalue

    std::cout << "\ngen obj3" << std::endl;
    MyClass obj3 = MyClass(); // default constructor, temporary object is an rvalue

    std::cout << "\ngen obj4" << std::endl;
    MyClass obj4 = std::move(obj1); // move constructor, obj1 is an xvalue

    std::cout << "\nfunc lvalue test starts" << std::endl;
    auto start = std::chrono::high_resolution_clock::now(); // 진입 전 시간 측정
    func_lvalue(obj1);                                      // obj1 is an lvalue
    auto end = std::chrono::high_resolution_clock::now();   // 진입 후 시간 측정
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Elapsed time for func_lvalue(): " << elapsed_seconds.count() << "s\n";
    double ltime = elapsed_seconds.count();

    std::cout << "\nfunc rvalue test starts" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    func_rvalue(MyClass()); // temporary object is an rvalue
    end = std::chrono::high_resolution_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Elapsed time for func_rvalue(): " << elapsed_seconds.count() << "s\n";
    double rtime = elapsed_seconds.count();

    std::cout << "\nfunc xvalue test starts" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    MyClass obj5 = get_xvalue(); // move constructor, returned object is an xvalue
    end = std::chrono::high_resolution_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Elapsed time for get_xvalue(): " << elapsed_seconds.count() << "s\n";
    double xtime = elapsed_seconds.count();

    std::cout << "\nltime : rtime cost ratio is " << 1 << " : " << rtime / ltime << "\n";

    std::cout << "\nsome destructors" << std::endl;
    return 0;
}
