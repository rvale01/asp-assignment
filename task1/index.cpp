#include <iostream>
#include <thread>
#include <stdlib.h>
#include "../context/context.hpp"

// Context which is globally saved, so it can be accessed anywhere in this file
Context at_end;

// goo function which is called after foo
void goo(){
    std::cout << "You called goo" << std::endl;
    exit(EXIT_FAILURE); // calling function exit
}

// foo function, called first
void foo(){
    std::cout << "You called foo" << std::endl;
    set_context(&at_end); // it will set the current context to at_end
}


int main(){
    // allocate space for stack
    char data[4096];
    // stacks grow downwards
    char * sp = data + 4096;
    sp = (char*)((uintptr_t)(sp) & -16L);
    sp = sp - 128;

    // empty context
    Context c;
    // setting the pointer to the function foo of Context c
    c.rip = (void *)foo;
    // setting the pointer to the top of the stack of Context c
    c.rsp = sp;

    // setting the pointer to the function foo of Context at_end
    at_end.rip = (void *)goo;
    // setting the pointer to the top of the stack of Context at_end
    at_end.rsp = sp;
    
    // setting the current context to c
    set_context(&c);
    
    return 0;
}