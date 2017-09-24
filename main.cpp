/*
 *
 * Lab Assignment 1
 *
 * Write a C++ program to implement multithreaded matrix multiplication using Pthreads.
 * #include <pthread.h>  library
 * pthread_create (thread, attr, start_routine, arg)
 *
 */

#include <iostream>
#include <cstdlib>
#include <pthread.h>


using namespace std;

#define NUM_THREADS 4    // define number of threads


void* print_message(void *threadid)   // takes one parameter

{
    long tid;
    tid = long (threadid);  //set a thread id
   
    cout << "Threading! THREAD ID: " << tid << endl;
    pthread_exit(NULL);
}

int main() {


    pthread_t threads [NUM_THREADS];   // call pthread
    int rc;
    int i;

    for (i = 0; i< NUM_THREADS; i++) {
        cout << " main () : creating thread," << i << endl;
        rc = pthread_create(&threads[i], NULL, &print_message, (void *)i);    // creates a new thread

        if (rc) {
            cout<< "Error! Unable to create thread, " << rc << endl;
            exit(-1);

        }
    }

    pthread_exit(NULL);    // end program function
}
