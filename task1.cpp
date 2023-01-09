#include <iostream>
#include <thread>
#include <stdlib.h>
#include "context/context.hpp"

Context at_end;

void goo(){
    std::cout << "You called goo" << std::endl;
    exit(EXIT_FAILURE);
}

void foo(){
    std::cout << "You called foo" << std::endl;
    set_context(&at_end);
}

int main(){
    char data[4096];

    char * sp = data + 4096;
    sp = (char*)((uintptr_t)(sp) & -16L);
    sp = sp - 128;

    struct Context c;
    c.rip = (void *)foo;
    c.rsp = sp;

    struct Context gooc;
    gooc.rip = (void *)goo;
    gooc.rsp = sp;
    
    at_end = gooc;

    set_context(&c);
    
    return 0;
}