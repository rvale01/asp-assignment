#include "../context/context.hpp"
#include <iostream>
#include <thread>

class Fiber {
    private:
        Context context_;
        char * stack_bottom_;
        char * stack_top_;
        void * data_;

    public:
        Fiber(void (*func)(), void * data_par = nullptr){
            //char data[4096];
            stack_bottom_ = new char[4096];
            stack_top_ = stack_bottom_ + 4096;
            stack_top_ = (char*)((uintptr_t)(stack_bottom_) & -16L);
            stack_top_ = stack_top_ - 128;
            context_.rip = (void*)func;
            context_.rsp = stack_top_;
            data_ = data_par;
        }

        // Nothing happens here
        ~Fiber(){
        
        }

        Context* get_context_() { 
            return &context_;
        }

        void * get_data(){
            return data_;
        }
};