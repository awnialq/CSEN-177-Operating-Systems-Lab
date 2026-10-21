// Name: Awni AlQuraini
// Date: 10/21/2026
// Title: Lab 5 - Part 4
// Description: Program implementing the producer-consumer bounded buffer synchornization problem using lock mutexes and condition variables
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>


#define NTHREADS 2
#define BUFSIZE 10

void *produce(void *arg);
void *consume(void *arg);
void cleanup(int sigtype);

pthread_t threads[NTHREADS];

int buf[BUFSIZE];

int in, out = 0;

pthread_mutex_t lock;
pthread_cond_t full;
pthread_cond_t empty;

int main() {
    signal(SIGINT,cleanup);
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&full, NULL);
    pthread_cond_init(&empty, NULL);
    pthread_create(&threads[0], NULL, produce, NULL);
    pthread_create(&threads[1], NULL, consume, NULL);
    pthread_join(threads[0],NULL);
    pthread_join(threads[1],NULL);
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&full);
    pthread_cond_destroy(&empty);
    return 0;
}

void *produce(void *arg) {
    int i = 1;
    while(1){
        if(i != 0) { sleep(1); }
        printf("Producer attempting to produce... (if hangs/nothing produced buffer is full)\n");
        pthread_mutex_lock(&lock);
        while((in - out) == BUFSIZE){
            pthread_cond_wait(&empty, &lock);
        }
        printf("Producer producing value: %d\n", i);
        buf[in++ % BUFSIZE] = i++;
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(0);
}

void *consume(void *arg) {
    while(1){
        sleep(3);
        printf("Consumer attempting to consume... (if hangs/nothing consumed buffer is empty)\n");
        pthread_mutex_lock(&lock);
        while(in == out){
            pthread_cond_wait(&full, &lock);
        }
        printf("Consume consumed value: %d\n", buf[out++ % BUFSIZE]);
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(0);
}

void cleanup(int sigtype){
    printf("\n Terminating\n");
    exit(0);
}