/*
 tested at: https://www.onlinegdb.com/online_c++_compiler
  select cpp14 before running 
*/

#include <iostream>

class Drawable {
public:
    virtual void draw() const = 0;
};

class Circle : public Drawable {
public:
    void draw() const override {
        std::cout << "Drawing a circle." << std::endl;
    }
};

class Rectangular : public Drawable {
public:
    void draw() const override {
        std::cout << "Drawing a rectangular." << std::endl;
    }
};

void drawShape(const Drawable& drawable) {
    drawable.draw();
}

int main() {
    Circle circle;
    drawShape(circle);  // Circle에 대한 호출
    
    Rectangular rectangular;
    drawShape(rectangular);  // Rectangular에 대한 호출
    
    return 0;
}
