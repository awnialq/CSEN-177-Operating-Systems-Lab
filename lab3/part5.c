// Name: Awni AlQuraini
// Date: 10/7/2026
// Title: Lab 3 - Part 5
// Description: Implements the producer-consumer message communication using pipes.
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
int main(int argc,char *argv[]){
    int fds[2];
    int count;
    int i;
    pipe(fds);
    if (fork()==0){
        printf("Producer sending messages to the consumer...\n",argc);
        close(fds[0]);
        for(i=1;i<11;i++){
            write(fds[1], &i, sizeof(i));
            printf("Sent %d...\n", i);
        }
        close(fds[1]);
        exit(0);
    }
    else if(fork()==0){
        printf("\nConsumer recieving the messages... \n");
        close(fds[1]);
        int num;
        while((count=read(fds[0],&num,sizeof(num)))>0){
            printf("Consumer recieved %d...\n", num);
        }
        close(fds[0]);
        exit(0);
    }
    else{
        close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0);
    }
    return 0;
}