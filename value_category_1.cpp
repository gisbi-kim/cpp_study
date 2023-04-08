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

  func rvalue test starts
  MyClass default constructor
  Inside func_rvalue()
  MyClass destructor

  func xvalue test starts
  Inside get_xvalue()
  MyClass default constructor

  some destructors
  MyClass destructor
  MyClass destructor
  MyClass destructor
  MyClass destructor
  MyClass destructor
*/

#include <iostream>
#include <utility>

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
    func_lvalue(obj1); // obj1 is an lvalue

    std::cout << "\nfunc rvalue test starts" << std::endl;
    func_rvalue(MyClass()); // temporary object is an rvalue

    std::cout << "\nfunc xvalue test starts" << std::endl;
    MyClass obj5 = get_xvalue(); // move constructor, returned object is an xvalue

    std::cout << "\nsome destructors" << std::endl;
    return 0;
}
