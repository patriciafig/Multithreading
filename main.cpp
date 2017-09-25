/*
 * Patricia Figueroa
 * CSCI 3453 Operating System Concepts
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
#include <fstream>

using namespace std;

struct thread_data {
    int  thread_id;
    int row_no;
    int rb;
    int ca;
    int cb;
    int **matA;
    int **matB;
    int **matC;
};

void *multiply(void *threadarg) {
    struct thread_data *my_data;
    my_data = (struct thread_data *) threadarg;

    int **matA = my_data->matA;
    int **matB = my_data->matB;
    int **matC = my_data->matC;
    int rowNo = my_data->row_no;

    int rb = my_data->rb;
    int cb = my_data->cb;
    int ca = my_data->ca;

    for(int j=0; j<cb; j++){
        int temp = 0;
        for(int k=0; k<ca; k++){
            temp += matA[rowNo][k]*matB[k][j];
        }
        matC[rowNo][j] = temp;
    }

    pthread_exit(NULL);
}

int main () {

    int num_threads;
    //Initialize file stream
    ifstream myfile("matrix.txt");
    // Variables to store size of matrix A
    int ra, ca;
    // Variables to store size of Matrix B
    int rb, cb;
    //Check if the file is open
    if(myfile.is_open()){
        //Read parameters of matrix A
        int **matrix_a=nullptr;
        int **matrix_b=nullptr;
        try{
            myfile >> ra;
            if(myfile.fail()){
                throw runtime_error("");
            }

            myfile >> ca;
            if(myfile.fail()){
                throw runtime_error("");
            }
            //Initialize matrix A
            matrix_a = new int*[ra];
            //Read matrix A
            for(int i=0; i<ra; i++){
                matrix_a[i] = new int[ca];
                for(int j=0; j<ca; j++){
                    myfile >> matrix_a[i][j];
                    if(myfile.fail()){
                        throw runtime_error("");
                    }
                }
            }
            //Read parameters of matrix B
            myfile >> rb;
            myfile >> cb;
            //Initialize matrix A
            matrix_b = new int*[rb];
            //Read matrix B
            for(int i=0; i<rb; i++){
                matrix_b[i] = new int[cb];
                for(int j=0; j<cb; j++){
                    myfile >> matrix_b[i][j];
                    if(myfile.fail()){
                        throw runtime_error("");
                    }
                }
            }
        }catch(const runtime_error& e) {
            printf("Invalid input format. Input contains a non-integer value");
            return -1;
        }

        //Print matrix A
        cout<<"Matrix A: "<<endl;
        for(int i=0; i<ra; i++){
            for(int j=0; j<ca; j++){
                cout<<matrix_a[i][j]<<" ";
            }
            cout<<endl;
        }
        //Print matrix B
        cout<<"Matrix B: "<<endl;
        for(int i=0; i<rb; i++){
            for(int j=0; j<cb; j++){
                cout << matrix_b[i][j] << " ";
            }
            cout << endl;
        }
        //If the number of columns in Matrix A are not equal to number of rows in Matrix B,
        //the matrices are not multiplicable.
        if(ca != rb){
            cout << "Sorry! The matrices cannot be multiplied, please check dimensions."<<endl;
            return 0;
        }
        //The numbers of rows in matrix c will be equal to number of rows in matrix A
        int start_t = clock();
        //The number of rows in matrix C = number of rows in matrix A. (By property of matrix multiplication)
        int rc = ra;
        //The number of columns in matrix C = number of rows in matrix B. (By property of matrix multiplication)
        int cc = cb;
        //Each row should be computed using 1 thread. Hence the number of threads = number of rows in matrix C
        num_threads = rc;
        //Initializing an array of threads
        pthread_t *threads = new pthread_t[num_threads];
        pthread_attr_t attr;
        void *status;
        // Initialize and set thread joinable
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
        //Initializing matrix C
        int **matrix_c = new int*[rc];
        //Initializing each row of matrix C
        for(int i=0; i<rc; i++){
            matrix_c[i] = new int[cc];
        }

        struct thread_data td[num_threads];
        int ec;
        int i;

        //Creating threads
        for( i = 0; i < num_threads; i++ ) {
            //For each thread, we pass parameters which include the row number
            //and pointers to all the matrices

            //Initializing the parameters to pass to the thread
            td[i].thread_id = i;
            td[i].row_no = i;
            td[i].ca = ca;
            td[i].matA = matrix_a;
            td[i].matB = matrix_b;
            td[i].matC = matrix_c;
            td[i].rb = rb;
            td[i].cb = cb;

            //Creating the thread
            ec = pthread_create(&threads[i], NULL, multiply, (void *)&td[i]);
            cout <<"Created worker thread for row " << i << endl;

            if (ec) {
                cout << "Error:unable to create thread," << ec << endl;
                exit(-1);
            }
        }
        // free attribute and wait for the other threads
        pthread_attr_destroy(&attr);
        //Joining the threads so that the parent thread (main function) doesn't end until the child threads are complete
        for( i = 0; i < num_threads; i++ ) {
            ec = pthread_join(threads[i], &status);
            if (ec) {
                cout << "Error:unable to join," << ec << endl;
                exit(-1);
            }
        }
        int stop_t = clock();

        printf("Matrix C: A x B: ");
        for(int i=0; i<rc; i++){
            for(int j=0; j<cc; j++){
                printf("%d\t",matrix_c[i][j]);
            }
            printf("\n");
        }
        double dt = (stop_t-start_t)/double(CLOCKS_PER_SEC)*1000;
        cout << "Total execution time using "<<num_threads+1<<" threads is "<<dt<<" ms"<<endl;

    }
        //Print an error if file couldn't be opened.
    else{
        printf("Couldn't read file/File not found. Exiting....");
    }

}
