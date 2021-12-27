// BasicTimerUtilityStuff.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

typedef enum state_st
{
    STOPPED,
    RUNNING,
    PAUSED
} State;

typedef void (*ActionFunc)(Task_ptr);

typedef struct task_st
{
    State state;        // state of task
    int duration;       // timer duration
    int value;          // current counted value
    int payload;        // the LED ID 
    ActionFunc action;  // what to do when we expire

} Task, * Task_ptr;

void handler(Task_ptr);
void interrupt();
void init_task(Task_ptr,int,int,ActionFunc);

static Task tasks[6];   // six task instances, not yet initialized

int main()
{

    tasks[0].state = STOPPED;


}

void handler(Task_ptr task)
{

    return;
}

void init_task(Task_ptr task_ptr, int duration, int payload, ActionFunc action)
{
    task_ptr->state = STOPPED;
    task_ptr->duration = duration;
    task_ptr->value = 0;
    task_ptr->payload = payload;
    task_ptr->action = action;

}

// This is called by the system, timer interrupt etc
void interrupt()
{


}