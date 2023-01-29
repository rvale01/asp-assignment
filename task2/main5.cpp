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
    // getting the data from the current Fiber
    auto dp = s.get_current()->get_data();

    // this print will be shown before yield is called
    std::cout << "f1 before: " <<  *(int*)dp << std::endl;
    s.yield();

    // increasing the value of the integer by 1
    *(int*)dp += 1;

    // this print will be shown after yield is called, therefore after all the 
    // other Fibers in the queue have been run
    std::cout << "f1 after: " << *(int*)dp << std::endl;
    s.fiber_exit();
}

// simple function with just a print statement
void func2(){
    // Getting the data from the current Fiber
    auto dp = s.get_current()->get_data();
    // printing the data
    std::cout << "fiber 2: " << *(int*)dp << std::endl;

    // exiting the fiber
    s.fiber_exit();
}

int main(){
    // creating an integer
    int d = 10;
    int* dp = &d; // creating a pointer to the previous integer

    //set f1 to be fiber with func1
    Fiber f1(func1, dp);
    
    //set f2 to be fiber with func2 
    Fiber f2(func2, dp);

    //call s method spawn with address of f1
    s.spawn(&f1);

    //call s method spawn with address of f2    
    s.spawn(&f2);

    s.do_it(); 
    return 0;
}