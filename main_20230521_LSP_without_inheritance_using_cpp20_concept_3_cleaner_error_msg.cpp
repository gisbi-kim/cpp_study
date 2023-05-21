/*
 tested at: https://www.onlinegdb.com/online_c++_compiler
  select cpp20 before running 
*/

/* this below code should occurs error msg like this 

    main.cpp: In function ‘int main()’:
    main.cpp:64:14: error: no matching function for call to ‘drawShape(Triangle&)’
       64 |     drawShape(triangle);
          |     ~~~~~~~~~^~~~~~~~~~
    main.cpp:11:6: note: candidate: ‘template  requires  Drawable void drawShape(const D&)’
       11 | void drawShape(const D& drawable) {
          |      ^~~~~~~~~
    main.cpp:11:6: note:   template argument deduction/substitution failed:
    main.cpp:11:6: note: constraints not satisfied
    main.cpp: In substitution of ‘template<class D>  requires  Drawable<D> void drawShape(const D&) [with D = Triangle]’:
    main.cpp:64:14:   required from here
    main.cpp:5:9:   required for the satisfaction of ‘Drawable’ [with D = Triangle]
    main.cpp:5:20:   in requirements with ‘const T& t’ [with T = Triangle]
    main.cpp:7:17: note: the required expression ‘t.calcArea()’ is invalid
        7 |     { t.calcArea() } -> std::convertible_to<double>;
          |       ~~~~~~~~~~^~
    cc1plus: note: set ‘-fconcepts-diagnostics-depth=’ to at least 2 for more detail
    
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

class Triangle {
public:

    void draw() const {
        std::cout << "Drawing a triangle." << std::endl;
    }

};

int main() {
    Circle circle(5.0);
    drawShape(circle);  // Circle에 대한 호출

    Rectangular rectangular(4.0, 6.0);
    drawShape(rectangular);  // Rectangular에 대한 호출

    Triangle triangle;
    drawShape(triangle); 
    
    return 0;
}
