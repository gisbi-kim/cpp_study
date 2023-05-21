/*
 tested at: https://www.onlinegdb.com/online_c++_compiler
  select cpp20 before running 
*/

#include <iostream>
#include <concepts>

template <typename T>
concept Drawable = requires(const T& t) {
    { t.draw() } -> std::same_as<void>;
    { t.calcArea() } -> std::convertible_to<double>;
};

template <Drawable D>
void drawShape(const D& drawable) {
    drawable.draw();
    std::cout << "Area: " << drawable.calcArea() << std::endl;
}

class Circle {
public:
    double radius;

    Circle(double r) : radius(r) {}

    void draw() const {
        std::cout << "Drawing a circle." << std::endl;
    }

    double calcArea() const {
        return 3.14159 * radius * radius;
    }
};

class Rectangular {
public:
    double width;
    double height;

    Rectangular(double w, double h) : width(w), height(h) {}

    void draw() const {
        std::cout << "Drawing a rectangular." << std::endl;
    }

    double calcArea() const {
        return width * height;
    }
};

int main() {
    Circle circle(5.0);
    drawShape(circle);  // Circle에 대한 호출

    Rectangular rectangular(4.0, 6.0);
    drawShape(rectangular);  // Rectangular에 대한 호출

    return 0;
}
