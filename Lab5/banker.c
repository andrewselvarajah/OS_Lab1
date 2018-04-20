/*
 * Banker's Algorithm for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>
#include "banker.h"

// Put any other macros or constants here using #define


// May be any values >= 0
#define NUM_CUSTOMERS 5
#define NUM_RESOURCES 3


// Put global environment variables here
int *temp;

// Available amount of each resource
int available[NUM_RESOURCES];

// Maximum demand of each customer
int maximum[NUM_CUSTOMERS][NUM_RESOURCES];

// Amount currently allocated to each customer
int allocation[NUM_CUSTOMERS][NUM_RESOURCES];

// Remaining need of each customer
int need[NUM_CUSTOMERS][NUM_RESOURCES];


// Define functions declared in banker.h here
 bool request_res(int n_customer, int request[])
 {
      
 }

// Release resources, returns true if successful
 bool release_res(int n_customer, int release[])
 {
//      ...
 }


int main(int argc, char *argv[])
{
    // ==================== YOUR CODE HERE ==================== //

    // Read in arguments from CLI, NUM_RESOURCES is the number of arguments 
    if(argc == 3){
        for (int i = 1; i < argc; ++i){
            available[i-1] = argv[i];
        }
    }
    
    // Allocate the available resources

    // Initialize the pthreads, locks, mutexes, etc.
    pthread_mutex_t mutex;
    sem_t mutex;
    sem_init(&sem,0,1);
    pthread_mutex_init(&mutex,NULL);
    pthread_t threads[NUM_RESOURCES];

    // Run the threads and continually loop
     for (child = 0; child < NUM_RESOURCES; ++child)
    {
        pthread_create(&threads[child], NULL, worker, &b);
    }

    // The threads will request and then release random numbers of resources

    // If your program hangs you may have a deadlock, otherwise you *may* have
    // implemented the banker's algorithm correctly
    
    // If you are having issues try and limit the number of threads (NUM_CUSTOMERS)
    // to just 2 and focus on getting the multithreading working for just two threads

    return EXIT_SUCCESS;
}
