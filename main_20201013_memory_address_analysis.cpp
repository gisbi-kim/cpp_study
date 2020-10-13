
/*
2020. 10. 13 

Lessons
- Lesson 1: 유니폼 초기화(uniform initialization)는 기본적으로 형 변환을 제한하는 특성이 있다.
- Lesson 2: initializer_list 는 {} 를 이용해서 생성자를 호출할 때, 인자로 받는 생성자가 존재한다면 인자가 전달된다.
- Lesson 3: uniform initialization은 생성자들 중에 std::initializer_list의 형태의 인자를 가진 생성자가 존재한다면 적절한 생성자가 있음에도 불구하고 모두 무시하려고 한다.
*/

/* 
Summary:
    Widget w1; //기본 생성자 호출
    Widget w2(); //함수! 호출 x
    Widget w3{}; //기본 생성자 호출
    Widget w4({});//std::initializer_list 이용해 호출
    Widget w5{ {} };//std::initializer_list 이용해 호출
    Widget w6 = {}; // 기본 생성자 호출
    Widget w7 = { {} }; //std::initializer_list 이용해 호출
*/

//#include "Widget.h"
#include <iostream>

using std::cout;
using std::endl;

class Widget
{
public:

    Widget(void) = default;

    template <typename bType>
    Widget(int i, bType b) 
    {
        // assertion: type restriction (c++11)
        static_assert(std::is_same<bType, double>::value
                    || std::is_same<bType, float>::value);

        cout << "i: " << i << ", "
             << "b: " << b << endl; 
    };

    void printStatus(void) const 
    {
        cout << "status: " << status << endl;
    }

    Widget& operator()(int n) 
    { 
        cout << "hi you called the () operator" << endl;
        return *this;
    }


private:
    int status {3};
};

#include <memory>

int main() {
    Widget w1 {10, 5.023}; 
    Widget w2 (10, 5.023); 

    Widget w3; 
    Widget& w33 = w3; 
    Widget& w333 = w3(1); 
    Widget w3333 = w3(1); 

    cout << (long)&w1 << endl; 
    cout << (long)&w2 << endl; 

    cout << (long)&w3 << endl; 
    cout << (long)&w33 << endl; 
    cout << (long)&w333 << endl; 
    cout << (long)&w3333 << endl;

    //
    // auto w3Ptr = std::make_unique<Widget>(); 
    auto w3Ptr = std::make_shared<Widget>(); 
    w3Ptr->printStatus();

    Widget w3PtrGot = *w3Ptr;
    Widget& w33_from_unique = w3PtrGot(4); // NOTE: std::shared_ptr is smart pointer which behaves like raw pointers, you can't call operator() on the pointer directly.

    cout << (long)&w3Ptr << endl; // smart pointer 의 주소 (at stack)
    cout << (long)w3Ptr.get() << endl; // smart pointer 가 가리키는 실제 데이터의 주소 (at heap)
    cout << (long)&w3PtrGot << endl;
    cout << (long)&w33_from_unique << endl;
    /* 결과 
    140720928513248
    36479632 // heap 이라 주소의 숫자가 작은 것을 알 수 있다. 
    140720928513232
    140720928513232    
    */

    return 0;  
}
