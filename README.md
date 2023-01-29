<h1>Repo</h1>
This repo contains the code required for the assignment of advance system programming. The repo is divided into two folders.
The first folder (task1) contains all the code required for task 1. The task 2 folder contains all the files which are used for task 2 and task 3.

<h3>Task 1</h3>
Task 1 has just one file which contains all the code for the task. This file has three functions, one of which is the main one.

It also has a context, which is saved globally, so it can be accessed by the main function and by the two functions.

The main function a Context. I set to <code>rip</code> of the context the pointer of the function foo. 
Then, I set to <code>rsp</code> the pointer of the top of the stack.

Then, I set the rip of the global context (<code>at_end</code>) to the function goo, and to <code>rsp</code> the pointer of the top of the stack. 

Then I set the running context to c (the local context), which has a pointer to the function foo.

This will run the function foo, in the foo function, the context running is changed by setting the context to <code>at_end</code>. This has a pointer to the function goo. Therefore, the function goo is ran. 
Once the goo function finishes, the function exit is called and the program ends.

<h3>Task 2</h3>

The first part of the task includes a rework of task 1 with the use of a class. This part can be found in the file <code>main.cpp</code> which uses <code>fiber.hpp</code>

<h4>Fiber.hpp</h4>
This contains the Fiber class which was coded by using the class diagram and the pseudo code from the assignment specs. 
The class has 4 attributes:
- a context;
- a pointer to the bottom of the stack;
- a pointer to the top of the stack;
- and data (which is used later on in task 2) which can be any kind of data shared among different Fibers.

The class has a constructor. This accepts as parameters a function and any kind of data. Data is an optional parameter. 
When the constructor is called, a stack is created. Then we set the pointer of the function of the context. Same thing for the pointer to the top of the stack.

Also, I save the data passed.

The class has two getters: one returns a pointer to the context and the other returns a pointer to the data.

<h4> main.cpp </h4>
This is very similar to the task 1. It has the same logic, the only difference in on line 26 of the file <code>main.cpp</code>: basically the Fiber class is used and two objecs of type Fiber are created (f1 and f2)

<h4> scheduler.hpp </h4>
The second part of task 2 includes a Scheduler with the function do_it. The scheduler has three attributes:
- a queue of pointer of fibers;
- a context
- the current active fiber

There are five methods in this class:
- spawn: it accepts as parameter a pointer to a fiber and it adds fibers to the queue
- do_it: it runs all the values in the queue;
- fiber_exit: it jumps back to the scheduler loop;
- get_current: which returns the current context.
- yield: function used in task 3. This function stops the current fiber, pushing it at the back of the queue and, when it's its turn again, it will resume where it was left off.

<h4>main2.cpp</h4>
This is an extension of the file <code>main.cpp</code>. It has the same logic, except it uses the Scheduler class. For example, instead of setting the context using <code>set_context</code>, it uses the method spawn, by passing the pointer to the fiber and then it calls the do_it function. The two functions (func1 and func2) call the fiber_exit of the Scheduler at the end (unlike before the set_context was called or the exit function).


<h4>main3.cpp</h4>
This is the last part of task 2, where the data of the Fiber is used. This is similar to the previous examples. In the main function, an integer is created and passed to the inistances of the Fiber.

In func1, I get the data from the current Fiber, print it, add 1, then it exits.

In func2, I get the data from the current Fiber, print it, then it exits.

When func1 is called, the integer printed is 10. Then when func2 is called, the integer printed is 11.
This is because it is a pointer to the integer. 

<h3>Task 3</h3>
This task asked to add a yield function to the scheduler. This was used in the <code>main4.cpp</code> file.

This file contains a similar code to the one used in the previous task. The only difference is that <code>func1</code> calls the <code>yield</code> function. 
The flow of the code is:
- in main two instances of the Fiber class are created, one passing func1 and the other passing func2.

- both these two instances are passed as pointers to the spawn function, therefore adding them to the queue

- the do_it function is called

- when the do_it function is called, the func1 is ran first. The first print statement is printed, then the yield method is called, which stops the func1 from running, it moves the Fiber to the end of the queue and then the Fiber with func2 is swapped with the Fiber which was running.

- func2 is ran and the print statement is shown. Then, since there Fiber f1 is the last one left in the queue, func1 is ran again from the point were it was left (therefore just the second print stament is shown).

An extension of this code is seen in <code>main5.cpp</code> file, where the code is very similar to the one present in <code>main4.cpp</code> , with the exception of passing a data when creating the instance of the Fiber class.

<h3>How to run the code</h3>
These are the commands to use in order to run any of the files
<code>clang++ -std=c++11 -o task1 index.cpp ../context.o</code>

<code> task1 </code>

Instead of task1, use the name you want the file to be saved as.
Instead of index.cpp, use the name of the file you want to run.

<h3> Video </h3>
![Alt text](https://gitlab.uwe.ac.uk/v2-ronchi/asp-assignment/-/raw/main/video_valentina_ronchi.mov "Task 4")
