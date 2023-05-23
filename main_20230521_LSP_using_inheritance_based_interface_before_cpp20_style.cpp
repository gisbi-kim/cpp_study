/*
 tested at: https://www.onlinegdb.com/online_c++_compiler
  select cpp14 before running 
*/
#include <vector>
#include <memory>
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
    // single test 
    {
        Circle circle;
        drawShape(circle);  // Circle에 대한 호출
        
        Rectangular rectangular;
        drawShape(rectangular);  // Rectangular에 대한 호출
    }    
    std::cout << std::endl;
    
    // batch test 
    {
        std::vector<std::unique_ptr<Drawable>> drawable_objects;
        
        drawable_objects.emplace_back(std::make_unique<Circle>());
        drawable_objects.emplace_back(std::make_unique<Rectangular>());
        drawable_objects.emplace_back(std::make_unique<Circle>());
        drawable_objects.emplace_back(std::make_unique<Rectangular>());
        drawable_objects.emplace_back(std::make_unique<Rectangular>());
        
        for(const auto& drawable_obj: drawable_objects) {    
            drawShape(*drawable_obj); 
        }
    }
    std::cout << std::endl;

    return 0;
}
