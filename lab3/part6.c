// Name: Awni AlQuraini
// Date: 10/7/2026
// Title: Lab 3 - Part 6
// Description: Implements the producer-consumer message communication using shared memory.
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdbool.h>

struct data {
    bool read;
    int num;
};

int main(int argc,char *argv[]){
    key_t key = 67;
    int id = shmget(key, sizeof(struct data), IPC_CREAT | 0666); 
    volatile struct data *ctrl;
    int i;
    if (fork()==0){
        ctrl = shmat(id, 0, 0);
        ctrl->read = true;
        for(i=1;i<11;++i){
            while(!ctrl->read){
                usleep(500000);
            }
            printf("Sent %d...\n", i); 
            ctrl->read = false;
            ctrl->num = i; 
        }
        shmdt((void *)ctrl);
        exit(0);
    }
    else if(fork()==0){
        ctrl = shmat(id, 0, 0);
        for(i = 0; i < 10; ++i){
            while(ctrl->read){
                usleep(500000);
            }
            printf("Recieved %d...\n", ctrl->num);
            ctrl->read = true;
        }
        shmdt((void *)ctrl);
        exit(0);
    }
    else{
        wait(0);
        wait(0);
        shmctl(id, IPC_RMID, NULL);
    }
    return 0;
}