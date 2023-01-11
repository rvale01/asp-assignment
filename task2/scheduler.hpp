#include <iostream>
#include <thread>
#include <deque>

class Scheduler {
    private:
        std::deque<Fiber*> fibers_;
        Context context_;
        Fiber * current_;

    public:
    Scheduler(){
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
            //set current_ by poping from of fibers
            current_ = fibers_.front();
            fibers_.pop_front();

            //set c calling method function get_context from current_
            Context * c = current_->get_context();
            //call set_context with c

            // std::cout << "hello 3 - " << c << "\n";
            set_context(current_->get_context());
        }
    }

    void fiber_exit(){
        set_context(&context_);
    }

    Fiber * get_current(){
        return current_;
    }

    void yield () {
        fibers_.push_back(current_);

        set_context(fibers_.front()->get_context());
    }
};