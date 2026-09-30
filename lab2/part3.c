// Name: Awni AlQuraini
// Date: 09/30/2026
// Title: Lab 2 - Step 5
// Description: The C file that showcases forking and its functionality now with a custom delay set by the user for 4 processes (1 parent + 3 child processes)
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h> 
#include <errno.h>

int main(int argc, char *argv[]){
	if(argc != 5){
		printf("Usage: %s <delay time 1>  <delay time 2> <delay time 3> <delay time 4>\n", argv[0]);
		exit(0);
	}


	pid_t pid;
	int d1 = atoi(argv[1]); //delay in microseconds to showcase cpu scheduling
	int d2 = atoi(argv[2]);
	int d3 = atoi(argv[3]);
	int d4 = atoi(argv[4]);

	for(int i = 1; i < 4; ++i){
		pid = fork();
		if(pid < 0){
			fprintf(stderr, "fork failed, error %d\n", errno);
			exit(1);
		}
		if(pid == 0){
			switch(i){
				case 1:
					for(int j = 0; j < 10; ++j){
						printf("\tI am child 1 and this is my %dth iteration!\n", j); 
						usleep(d2);
					}
					exit(0);
				case 2:
					for(int j = 0; j < 10; ++j){
						printf("\t\tI am child 2 and this is my %dth iteration!\n", j);
						usleep(d3);
					}
					exit(0);
				case 3:
					for(int j = 0; j < 10; ++j){
						printf("\t\t\tI am child 3 and this is my %dth iteration!\n", j);
						usleep(d4);
					}
					exit(0);
			}
		}
	}
	
	if(pid){ // parent process as pid is > 0
		for(int i = 0; i < 10; ++i){
			printf("I am the parent process displaying iteration: %d\n", i);
			usleep(d1);
		}
	}
	wait(0);
	exit(0);
}
