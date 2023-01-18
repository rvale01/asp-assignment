#include <iostream>
#include <thread>
#include <deque>

class Scheduler {
    private:
        std::deque<Fiber*> fibers_; // queue of pointers of fiber 
        Context context_; // context
        Fiber * current_; // the current active fiber

    public:

    Scheduler(){
        std::deque<Fiber*> fibers_;
    }

    // Deconstructor: nothing happens here
    ~Scheduler(){
    }

    // function spawn which adds fibers to the queue
    void spawn(Fiber * f){
        // push f to back of the queue
        fibers_.push_back(f);
    }

    // function which runs the all the values in the 
    void do_it(){
        // getting the current context
        get_context(&context_);
        
        // if fibers_ is not empty:
        if(!fibers_.empty()){
            //set current_ by poping from of fibers
            current_ = fibers_.front();
            fibers_.pop_front();

            //set c by calling the method get_context from current_
            Context * c = current_->get_context();

            //call set_context with c
            set_context(c);
        }
    }

    void fiber_exit(){
        // jump back to the scheduler 'loop'
        set_context(&context_);
    }

    // methos which returns the current context
    Fiber * get_current(){
        return current_;
    }

    // function which runs the yield:
    // yeilding means stopping the current fiber, pushing it at the back of the queue and,
    // when it's its turn again, it will resume where it was left off.
    void yield () {
        if(!fibers_.empty()){
            // getting the context from the current fiber and saving it
            auto old_context = current_->get_context();
            
            // moving the current fiber to the back of the queue
            fibers_.push_back(current_);
            current_ = fibers_.front();
            fibers_.pop_front();

            // swapping the context we saved (the one we stopped) with the new context
            swap_context(old_context, current_->get_context());
        }
    }
};