#include <iostream>
#include <thread>
#include <stdlib.h>
#include "fiber.hpp"
#include "scheduler.hpp"

// TASK 2 PART WITH DATA
// set s to be scheduler ( a global variable, so it can be used in the
// different functions to stop the fiber from running and to get the data)
Scheduler s;

void func1(){
    // getting the data from the current Fiber
    auto dp = s.get_current()->get_data();
    // printing the data
    std::cout << "fiber 1: " << *(int*)dp << std::endl;
    // increasing the value of the integer by 1
    *(int*)dp += 1;
    // stopping this Fiber
    s.fiber_exit();
}

void func2(){
    // Getting the data from the current Fiber
    auto dp = s.get_current()->get_data();
    // printing the data
    std::cout << "fiber 2: " << *(int*)dp << std::endl;
    // stopping this Fiber
    s.fiber_exit();
}

int main (){
    // creating an integer
    int d = 10;
    int* dp = &d; // creating a pointer to the previous integer

    // creating two fibers with different functions, but passing the same pointer to the integer
    Fiber f1(func1, dp);
    Fiber f2(func2, dp);

    // adding to the queue the first Fiber
    s.spawn(&f1);
    // adding to the queue the second Fiber
    s.spawn(&f2);

    // starting the loop and running all the Fibers
    s.do_it();
    return 0;
}
