#include <iostream>
#include <thread>
#include <stdlib.h>
#include "fiber.hpp"

// THIS IS A REWORK OF TASK 1
// IT HAS THE SAME LOGIC, BUT IT USES THE CLASSES CREATED (e.g. FIBER CLASS AND SCHEDULER CLASS)

// Context which is globally saved, so it can be accessed anywhere in this file
Context * at_end;

// goo function which is called after foo
void goo(){
    std::cout << "You called goo" << std::endl;
    exit(EXIT_FAILURE);
}

// foo function, called first
void foo(){
    std::cout << "You called foo" << std::endl;
    set_context(at_end); // it will set the current context to at_end
}

int main(){
    // creating an object of type Fiber and passing the function foo as parameter
    Fiber f1(foo);

    // creating an object of type Fiber and passing the function goo as parameter
    Fiber f2(goo);

    // saving the context of the fiber which will be executed as second here
    at_end = f2.get_context();

    // setting the context of the fiber which will be executed first
    set_context(f1.get_context());
    
    return 0;
}