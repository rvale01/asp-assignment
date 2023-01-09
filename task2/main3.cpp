#include <iostream>
#include <thread>
#include <stdlib.h>
#include "fiber.hpp"
#include "scheduler.hpp"

//set s to be scheduler
Scheduler s;

void func1(){
    std::cout << "fiber 1" << std::endl;
    auto dp = s.get_current()->get_data();
    std::cout << "fiber 1:" << *(int*)dp << std::endl;
    *(int*)dp += 1;
    s.fiber_exit();
}

void func2(){
    std::cout << "fiber 2" << std::endl;
    auto dp = s.get_current()->get_data();
    std::cout << "fiber 2:" << *(int*)dp << std::endl;
    s.fiber_exit();
}

int main (){
    int d = 10;
    int* dp = &d;

    Fiber f1(func1, dp);
    Fiber f2(func2, dp);

    s.spawn(&f1);
    s.spawn(&f2);

    s.do_it();
    return 0;
}
