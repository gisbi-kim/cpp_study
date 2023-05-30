/* tested at https://wandbox.org/ 
  with c++2b compiler
*/ 

#include <iostream>
#include <concepts>

// Define a concept for things that can quack
template <typename T>
concept Quacks = requires(T a) {
    { a.quack() } -> std::same_as<void>;
};

// Implementations
struct Duck {
    void quack() { std::cout << "Quack!\n"; }
};

struct Dog {
    void bark() { std::cout << "Woof!\n"; }
};

// Function that requires a Quacks
void make_sound(Quacks /* <= here is the beutiful moment. 
                          we can define a template function without 
                          the template keyword and the intention of 
                          the object is more vivid */ auto& animal) {
    animal.quack();
}

int main() {
    Duck duck;
    // Dog dog;
    make_sound(duck);  // Outputs: "Quack!"
  // make_sound(dog);  // Error! Dog does not satisfy Quacks
  /* if uncomment the above line, we will encounter 
     more vivid error message to undertand, e.g.,
    
    prog.cc: In function 'int main()':
    prog.cc:28:16: error: 'dog' was not declared in this scope; did you mean 'Dog'?
     28 |     make_sound(dog);  // Error! Dog does not satisfy Quacks
        |                ^~~
        |                Dog

*/
}
