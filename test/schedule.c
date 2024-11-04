#include <stdio.h>
// #include <pico/stdlib.h> TODO: Not sure where the hell this thing is.
#include <stdint.h>
#include <unity.h>
#include "unity_config.h"



/*
    No work to do in setup
*/
void setUp(void) {}

/*
    Just print a message for the teardown
    TODO: the solution prints status.
*/
void tearDown(void) {
    printf("Tearing down!");
}



// _________________________________________________ Activity 0 ___________________________________________________

/*
    Task 1: TODO: Create 2 preemtable threads and a supervisor to manage them.
    Task 2: TODO: Create a semaphore between them using "xSemaphoreCreateBoolean"
    Task 3: TODO: Set one thread to a higher priority than the other and set it to delay start.
        I think the instructions meant to say "make sure it delays after start so the lower-priority thread starts first."
    Task 4: TODO: Have the lower priority thread aquire the semaphore first.
    Task 5: TODO: Predict the behavior of the system
        The lower priority thread will block the higher priority thread.


    Task x: TODO: create a helper function to setup and teardown the threads.
*/
void PreemtableThread1() {

}

xSemaphoreCreateBoolean semaphore_between_them;

void PreemtableThread2() {
    
}

void SupervisorToThem() {

}







void HelperToSetupAndTeardownThreads(

) {

}


// _________________________________________________ Activity 1 ___________________________________________________

/*
    Do the same thing in Activity 0 but instead of xSemaphoreCreateBoolean use xSemaphoreCreateMutex
*/



// _________________________________________________ Activity 2 ___________________________________________________

/*
    In this activity, we create two competing threads and write the following tests for them
    
    Type 1: Same priority threads:
        1. TODO: both run busy_busy
        2. TODO: both run busy_yield
        3. TODO: one runs one, the other runs the other
    Type 2: Different priority threads:
        1. TODO: both run busy_busy
            a: TODO: higher priority starts first
            b: TODO: lower priority starts second
        2. TODO: both run busy_yield
*/
void busy_busy(void) {
    for(int i = 0; ; i++);
}
void busy_yield(void) {
    for(int i = 0; ; i++)
        taskYIELD();
}