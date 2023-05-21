/*
 tested at: https://www.onlinegdb.com/online_c++_compiler
  select cpp20 before running 
*/

#include <iostream>
#include <concepts>

template <typename T>
concept Drawable = requires(const T& t) {
    { t.draw() } -> std::same_as<void>;
};

class Circle {
public:
    void draw() const {
        std::cout << "Drawing a circle." << std::endl;
    }
};

class Rectangular {
public:
    void draw() const {
        std::cout << "Drawing a rectangular." << std::endl;
    }
};

template <Drawable D>
void drawShape(const D& drawable) {
    drawable.draw();
}

int main() {
    Circle circle;
    drawShape(circle);  // Circle에 대한 호출
    
    Rectangular rectangular;
    drawShape(rectangular);  // Rectangular에 대한 호출
    
    return 0;
}
