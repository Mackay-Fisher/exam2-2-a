#include "main.h"

int main()
{
    int i, nthreads = NUM_THREADS;
    double pi = 0.0, sum[NUM_THREADS][PAD];
    double start1, end1, start2, end2;

    step = 1.0 / (double)num_steps;

    start1 = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count();
    // ##### START OF SECTION 1 #####
    // create a vector of n threads
    vector<thread*> threads;
    // create n threads
    for (i = 0; i < nthreads; i++)
    {
        // create a thread to run the function single_sum_thread
        // pass in the thread id, number of threads, and the sum array
        // push the thread into the vector
        threads.push_back(new thread(single_sum_thread, i, nthreads, sum));
    }
    // join the threads with the main thread
    for (int i = 0; i < nthreads; i++)
    {
        threads[i]->join();
    }
    for(int i=0; i<nthreads;i++){
        delete threads[i];
    }
    threads.clear();
    // ##### END OF SECTION 1 #####
    end1 = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count();

    start2 = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count();
    // ##### START OF SECTION 2 #####
    // parallelize the following code, reference main.h for the function prototype
    // comment out this block of code when you are done with the parallelization 
    // (only need sleep 1 in the thread function)
    //because now each vaklue will acess teh sums i value at taht pouint and add it to the pi value as opposed ot goingg the rough eahc index of teh array.
    for (i = 0; i < nthreads; i++) {
        //passed value in by refrence so that I can chaneg it each time the peice runs on teh new step value
        threads.push_back( new thread(pi_sum_thread, i, sum,step,std::ref(pi)));
    }
    // join the threads with the main thread
    for (int i = 0; i < nthreads; i++)
    {
        threads[i]->join();
    }
    for(int i=0; i<nthreads;i++){
        delete threads[i];
    }
    threads.clear();

    // ##### END OF SECTION 2 #####
    end2 = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count();
    

    printf("Number of threads: %i\nCache padding for coherency: %i bytes\n---\n", nthreads, PAD * 8);
    printf("Pi approximation: %f\nTime to complete part 1: %f seconds\nTime to complete part 2: %f seconds\n", pi, (end1 - start1) * 1e-9, (end2 - start2) * 1e-9);
    return 0;
}
