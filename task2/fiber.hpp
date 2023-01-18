#include "../context/context.hpp"
#include <iostream>
#include <thread>

class Fiber {
    private:
        Context context_; // context
        char * stack_bottom_; // pointer to the bottom of the stack
        char * stack_top_; // pointer to the top of the stack
        void * data_; // data which can be passed and saved to the Fiber when it's created

    public:
        // Constructor of the class Fiber. It takes as parameters a function (which is used with the context)
        // and data (it's an optional parameter)
        Fiber(void (*func)(), void * data_par = nullptr){
            // a stack is created 
            stack_bottom_ = new char[4096]; // this is the pointer to the bottom of the stack
            stack_top_ = stack_bottom_ + 4096;
            stack_top_ = (char*)((uintptr_t)(stack_top_) & -16L);
            stack_top_ = stack_top_ - 128; // this is the pointer to the top of the stack
            
            // setting the pointer of the function of the context
            context_.rip = (void*)func; 
            // setting the pointer of the top of the stack 
            context_.rsp = stack_top_; 

            // saving the data
            data_ = data_par;
        }

        // Deconstructor: nothing happens here
        ~Fiber(){
        
        }

        // function which returns the address of context of the fiber
        Context* get_context() { 
            return &context_;
        }

        // function which returns the data
        void * get_data(){
            return data_;
        }
};