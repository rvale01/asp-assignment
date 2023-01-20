#include <iostream>
#include <thread>
#include <stdlib.h>
#include "fiber.hpp"
#include "scheduler.hpp"

// set s to be scheduler ( a global variable, so it can be used in the
// different functions to stop the fiber from running)
Scheduler s;

void func1(){
    std::cout << "f1 function" << std::endl;
    s.fiber_exit();
} 

void func2(){
    std::cout << "f2" << std::endl;
    s.fiber_exit();
}

int main(){

    //creating an object of type Fiber f1 with func1
    Fiber f1(func1);
    
    //creating an object of type Fiber f2 with func2 
    Fiber f2(func2);

    //call s method spawn with address of f1 (it will add f1 to the queue)
    s.spawn(&f1);

    //call s method spawn with address of f2 (it will add f2 to the queue)
    s.spawn(&f2);

    // it will start the loop and run all the Fibers in the queue
    s.do_it(); 
    return 0;
}

// int main(){
//     creating an object of type Fiber f1 with func1
//     Fiber f1(func1);
    
//     creating an object of type Fiber f2 with func2 
//     Fiber f2(func2);

//     Fiber f3(func1);
//     Fiber f4(func2);

//     call s method spawn with address of f1 (it will add f1 to the queue)
//     s.spawn(&f1);

//     call s method spawn with address of f2 (it will add f2 to the queue)
//     s.spawn(&f2);

//     s.spawn(&f3);
//     s.spawn(&f4);

//     it will start the loop and run all the Fibers in the queue
//     s.do_it(); 
//     return 0;
// }
