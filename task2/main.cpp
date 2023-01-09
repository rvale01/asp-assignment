#include <iostream>
#include <thread>
#include <stdlib.h>
#include "fiber.hpp"

Context * at_end;

void goo(){
    std::cout << "You called goo" << std::endl;
    exit(EXIT_FAILURE);
}

void foo(){
    std::cout << "You called foo" << std::endl;
    set_context(at_end);
}

int main(){
    Fiber f1(foo);

    Fiber f2(goo);

    at_end = f2.get_context_();

    //auto context_temp = f1.get_context_();
    set_context(f1.get_context_());
    
    return 0;
}