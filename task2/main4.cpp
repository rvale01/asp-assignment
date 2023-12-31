#include <iostream>
#include <thread>
#include <stdlib.h>
#include "fiber.hpp"
#include "scheduler.hpp"

//set s to be scheduler
Scheduler s;

// first function, here the yield is called, therefore the first
// and second print will be shown in two different moments
void func1(){
    // this print will be shown before yield is called
    std::cout << "f1 before" << std::endl;
    s.yield();
    // this print will be shown after yield is called, therefore after all the 
    // other Fibers in the queue have been run
    std::cout << "f1 after" << std::endl;
    s.fiber_exit();
}

// simple function with just a print statement
void func2(){
    std::cout << "f2" << std::endl;

    // exiting the fiber
    s.fiber_exit();
}

int main(){
    //set f1 to be fiber with func1
    Fiber f1(func1);
    
    //set f2 to be fiber with func2 
    Fiber f2(func2);

    //call s method spawn with address of f1
    s.spawn(&f1);

    //call s method spawn with address of f2    
    s.spawn(&f2);

    s.do_it(); 
    return 0;
}