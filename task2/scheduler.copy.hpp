#include <iostream>
#include <thread>
#include <deque>

class Scheduler {
    private:
        std::deque<Fiber*> fibers_;
        Context context_;
        Fiber * current_;

    public:
    Scheduler(int* data_param = nullptr){
    }

    ~Scheduler(){
    }

    void spawn(Fiber * f){
        // push f to back of fibers_
        fibers_.push_back(f);
    }

    void do_it(){
        get_context(&context_);
        
        // if fibers_ is not empty:
        if(!fibers_.empty()){
            //set f by poping from of fibers
            current_ = fibers_.front();
            fibers_.pop_front();

            //set c calling method function get_context from f
            auto c = current_->get_context_();
            //call set_context with c
            set_context(c);
        }
    }

    void fiber_exit(){
        set_context(&context_);
    }

    Fiber get_current(){
        return *current_;
    }
};