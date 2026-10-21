// Name: Awni AlQuraini
// Date: 10/21/2026
// Title: Lab 5 - Part 2
// Description: Thread synchronization using pthread_mutex_locks
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h> 
#include <unistd.h>
#include <signal.h>


#define NTHREADS 10

void *go(void *arg);
void cleanup(int sigtype);

pthread_t threads[NTHREADS];
pthread_mutex_t mutex;

int main() {
    signal(SIGINT,cleanup);
    pthread_mutex_init(&mutex, NULL);
    int i;
    for (i = 0; i < NTHREADS; i++)  
        pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
    for (i = 0; i < NTHREADS; i++) 
        pthread_join(threads[i],NULL);
    pthread_mutex_destroy(&mutex);
    return 0;
}

void *go(void *arg) {
    printf("Thread %d is now attempting ....\n",  (int)(size_t)arg);
    pthread_mutex_lock(&mutex);
    sleep(1);
    printf("Thread %d is running in its Critical Section........\n",  (int)(size_t)arg);
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}

void cleanup(int sigtype){
    pthread_mutex_destroy(&mutex);
    printf("\n Terminating\n");
    exit(0);
}
