// Name: Awni AlQuraini
// Date: 10/21/2026
// Title: Lab 5 - Part 3
// Description: Program implementing the producer-consumer bounded buffer synchornization problem using semaphores
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h> 
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

sem_t *mutex;
sem_t *empty;
sem_t *full;

int main() {
    signal(SIGINT,cleanup);
    sem_unlink("mutex");
    sem_unlink("empty");
    sem_unlink("full");
    mutex = sem_open("mutex", O_CREAT, 0644, 1);
    empty = sem_open("empty", O_CREAT, 0644, BUFSIZE);
    full = sem_open("full", O_CREAT, 0644, 0);
    pthread_create(&threads[0], NULL, produce, NULL);
    pthread_create(&threads[1], NULL, consume, NULL);
    pthread_join(threads[0],NULL);
    pthread_join(threads[1],NULL);
    sem_unlink("mutex");
    sem_unlink("empty");
    sem_unlink("full");
    return 0;
}

void *produce(void *arg) {
    int i = 1;
    while(1){
        if(i != 0) { sleep(1); }
        printf("Producer attempting to produce... (if hangs buffer is full)\n");
        sem_wait(empty);
        sem_wait(mutex);
        printf("Producer producing value: %d\n", i);
        buf[in++ % BUFSIZE] = i++;
        sem_post(mutex);
        sem_post(full);
    }
    pthread_exit(0);
}

void *consume(void *arg) {
    while(1){
        sleep(3);
        printf("Consumer attempting to consume... (if hangs buffer is empty)\n");
        sem_wait(full);
        sem_wait(mutex);
        printf("Consume consumed value: %d\n", buf[out++ % BUFSIZE]);
        sem_post(mutex);
        sem_post(empty);
    }
    pthread_exit(0);
}

void cleanup(int sigtype){
    sem_unlink("mutex");
    sem_unlink("empty");
    sem_unlink("full");
    printf("\n Terminating\n");
    exit(0);
}