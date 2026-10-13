// Name: Awni AlQuraini
// Date: 10/14/2026
// Title: Lab 4 - Part 2
// Description: Program showcasing how to address race conditions by passing values instead of a reference (+ a little bit of casting)
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *go(void *);
#define NTHREADS 10
pthread_t threads[NTHREADS];

int main() {
    int i; 
    for (i = 0; i < NTHREADS; i++)  
        pthread_create(&threads[i], NULL, go, (void *) i);
    for (i = 0; i < NTHREADS; i++) {
        printf("Thread %d returned\n", i);
        pthread_join(threads[i],NULL);
    }
    printf("Main thread done.\n");
    return 0;
}

void *go(void *arg) {
    printf("Hello from thread %d with iteration %d\n",  (int)(unsigned long) pthread_self(), (int)arg);
    pthread_exit(0);
}