#include <iostream>
#include <string>
#include <vector>
#include <memory>

struct Animal {
    std::string name;
    virtual void make_sound() const = 0;
};

struct Dog : Animal {
    void make_sound() const override {
        std::cout << name << " says woof!\n";
    }
};

struct Cat : Animal {
    void make_sound() const override {
        std::cout << name << " says meow!\n";
    }
};

int main() {
    std::vector<std::unique_ptr<Animal>> animals;

    std::unique_ptr<Dog> dog = std::make_unique<Dog>();
    dog->name = "Rover";
    animals.push_back(std::move(dog));

    std::unique_ptr<Cat> cat = std::make_unique<Cat>();
    cat->name = "Fluffy";
    animals.push_back(std::move(cat));

    for (const auto& animal : animals) {
        animal->make_sound();
    }

    return 0;
}
