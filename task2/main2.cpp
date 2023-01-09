#include <iostream>
#include <thread>
#include <stdlib.h>
#include "fiber.hpp"
#include "scheduler.hpp"

//set s to be scheduler
Scheduler s;

// func func1:
//     output "fi
//     call fiber_exit
void func1(){
    std::cout << "f1" << std::endl;
    s.fiber_exit();
}


// func func2:
//     output "fiber 2"
//     call fiber_exit   


void func2(){
    std::cout << "f2" << std::endl;
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

// TODO: other test cases