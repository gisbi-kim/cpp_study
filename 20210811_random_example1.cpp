#include <iostream>
#include <algorithm>
#include <utility>
#include <random>
#include <array>

using std::cout;
using std::endl;

template <typename T>
class UniformDistribution {
public: 
    UniformDistribution(const std::pair<T, T>& _range) { 
        // 시드값을 얻기 위한 random_device 생성.
        std::random_device rd;

        // random_device 를 통해 난수 생성 엔진을 초기화 한다.
        std::mt19937 gen(rd());
        generator_ = std::move(gen);

        // 0 부터 99 까지 균등하게 나타나는 난수열을 생성하기 위해 균등 분포 정의.
        std::uniform_int_distribution<T> dis(_range.first, _range.second);
        distribution_ = std::move(dis);
    }

    T getRandVal( void ) {
        return distribution_(generator_);
    }    

private: 
    std::mt19937 generator_; 
    std::uniform_int_distribution<T> distribution_;
};


int main() {
    std::cout << "Hello World!\n";

    std::pair<int, int> range {0, 100};
    UniformDistribution uniformDistribution (range);

    constexpr int myArrSize = 10; // OK, 10은 확실히 컴파일 시점 상수
    // const int arraySize2 = 10; // OK, 10은 확실히 컴파일 시점 상수
    std::array<double, myArrSize> myArr; // OK, arraySize2는 constexpr 객체
    myArr.fill(5.);
    for(auto& _elm: myArr) {
        _elm = uniformDistribution.getRandVal();
        cout << _elm << ", ";
    }
    cout << endl;

    int try_idx {1};
    while(true) {
        cout << "try " << try_idx << "." << endl; 
        auto it = std::find(myArr.cbegin(), myArr.cend(), 
            uniformDistribution.getRandVal());
        if( it == myArr.cend() ) { // no found 
            try_idx++;
            continue;
        } else {
            cout << "found the number!: " << *it << endl;
            break; 
        }
    }

    return 0; 
}
