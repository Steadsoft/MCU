// BasicTimerUtilityStuff.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define ON 1
#define OFF 0
#define TASKS 3

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
    int led;            // the LED ID 
    int next_state;     // on or off
    ActionFunc action;  // what to do when we expire

} Task, * Task_ptr;

void expiration_handler(int);
void system_interrupt();
void initialize_task(Task_ptr, State, int, int, int, ActionFunc);
void set_led(int, int);

static Task tasks[TASKS];   // three task instances, not yet initialized

int main()
{
    // Initialize all the tasks, none are 'running' just yet
    // we bgin by creating all tasks in stopped state and also specify 
    // the state the LED is to go after the first expiry.

    initialize_task(&tasks[0], STOPPED, 100, 1, OFF, expiration_handler); 
    initialize_task(&tasks[1], STOPPED, 200, 2, OFF, expiration_handler); 
    initialize_task(&tasks[2], STOPPED, 300, 3, OFF, expiration_handler);  

    set_led(1, ON);
    set_led(2, ON);
    set_led(3, ON);

    // OK, after this step the system interrupt handler will 
    // process these tasks.

    tasks[0].state = RUNNING;
    tasks[1].state = RUNNING;
    tasks[2].state = RUNNING;

    // do whatever else is needed, eg. get system 10 mS timer running etc.
}

void expiration_handler(int task_id)
{
    // change LED state
    set_led(tasks[task_id].led, tasks[task_id].next_state);
    // set the state that we'll set it to next to simply be the opposite 
    tasks[task_id].next_state = !tasks[task_id].next_state;
    // since this timer/task was stopped we start it afresh.
    tasks[task_id].state = RUNNING; // restar this task
}

void initialize_task(Task_ptr task_ptr, State initial, int duration, int led, int led_status, ActionFunc action)
{
    task_ptr->state = initial;
    task_ptr->duration = duration;
    task_ptr->value = 0;
    task_ptr->led = led;
    task_ptr->next_state = led_status;
    task_ptr->action = action;
}

// This is called by the system, timer interrupt etc, assume every 10 mS
void system_interrupt()
{

    for (int I = 0; I < TASKS; I++)
    {
        if (tasks[I].state == RUNNING)
        {
            tasks[I].value += 10;

            if (tasks[I].value >= tasks[I].duration)
            {
                tasks[I].value = 0;
                tasks[I].action(I); // this should be a fast executing bit of code, nothing costly...
                tasks[I].state = STOPPED;
            }
        }
    }
}

void set_led(int LED, int state)
{
    // do whatever to set LED on or off
}