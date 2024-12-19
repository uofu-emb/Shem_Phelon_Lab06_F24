#include <stdio.h>
#include <stdlib.h> // TODO: I copied this folder from the directory: ./lib/pico-sdk/src/common/pico_stdlib_headers/include/pico/stdlib.h
#include <stdint.h>
#include <unity.h>
#include "unity_config.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"


/*
    prepare for each activity
*/
void setUp(void) {
    
    // xSemaphoreCreateBoolean semaphore_between_them; This isn't even a real command like the instructions said.
    volatile SemaphoreHandle_t semaphore_between_them = xSemaphoreCreateBinary();

    if( semaphore_between_them != NULL )
        printf("Semaphore was not created\n");

    xSemaphoreGive(semaphore_between_them);

    volatile TaskHandle_t PreemtableThread1;
    volatile TaskHandle_t PreemtableThread2;
    volatile TaskHandle_t SupervisorToThem;
}

/*
    Clean up in between each activity.
*/
void tearDown(void) {
    printf("Tearing down!");
    vTaskDelete(PreemtableThread1);
    vTaskDelete(PreemtableThread2);
    vTaskDelete(SupervisorToThem);
    vSemaphoreDelete(semaphore_between_them);
    
}


// ____________________________________________ Select which test to run ___________________________
int main (void)
{
    stdio_init_all();
    xTaskCreate(test_preemtion, "Activity_0",configMINIMAL_STACK_SIZE,
                NULL, 10, &testRunnerTask);

    vTaskStartScheduler();
    return 0;
}


// _________________________________________________ Activity 0 ___________________________________________________

/*
    Task 1: Create 2 preemtable threads and a supervisor to manage them.
    Task 2: Create a semaphore between them using "xSemaphoreCreateBoolean"
    Task 3:  Set one thread to a higher priority than the other and set it to delay start.
        I think the instructions meant to say "make sure it delays after start so the lower-priority thread starts first."
    Task 4: Have the lower priority thread aquire the semaphore first.
    Task 5: Predict the behavior of the system
        The lower priority thread will block the higher priority thread. That's my prediction.


    Task x: TODO: create a helper function to setup and teardown the threads.
*/
void Activity_0(void) {
    
    xTaskCreate(PreemtableThread1, "premp1",
                configMINIMAL_STACK_SIZE, &semaphore_between_them, 1, &PreemtableThread1);
    xTaskCreate(PreemtableThread2, "premp2",
                configMINIMAL_STACK_SIZE, &semaphore_between_them, 2, &PreemtableThread2);
    xTaskCreate(SupervisorToThem, "Supervisor",
                configMINIMAL_STACK_SIZE, NULL, 0, &SupervisorToThem);

    // Delay in the higher priority task so the lower priority one will be pre-empted
    vTaskDelay(100);

    TEST_ASSERT_EQUAL(0, uxSemaphoreGetCount(semaphore_between_them));


    
}



// TODO: Helper



// _________________________________________________ Activity 1 ___________________________________________________

/*
    Do the same thing in Activity 0 but instead of xSemaphoreCreateBoolean use xSemaphoreCreateMutex
*/
void Activity_1(void) {

    // I'm not sure what the point of the setup() and teardown() functions are if these functions can't even see their variables.
    xTaskCreate(PreemtableThread1, "premp1",
                configMINIMAL_STACK_SIZE, &semaphore_between_them, 1, &PreemtableThread1);
    xTaskCreate(PreemtableThread2, "premp2",
                configMINIMAL_STACK_SIZE, &semaphore_between_them, 2, &PreemtableThread2);
    xTaskCreate(SupervisorToThem, "Supervisor",
                configMINIMAL_STACK_SIZE, NULL, 0, &SupervisorToThem);

    vTaskDelay(100);

    TEST_ASSERT_EQUAL(0, uxSemaphoreGetCount(semaphore_between_them));

    vTaskDelete(PreemtableThread1);
    vTaskDelete(PreemtableThread2);
    vTaskDelete(SupervisorToThem);
    vSemaphoreDelete(semaphore_between_them);
}


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