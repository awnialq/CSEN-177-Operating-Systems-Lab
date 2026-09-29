// Name: Awni AlQuraini
// Date: 09/30/2026
// Title: Lab 2 - Step 3
// Description: The C file that showcases forking and its functionality now with a custom delay set by the user.
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h> 
#include <errno.h>

int main(int argc, char *argv[]){
	if(argc != 2){
		printf("Usage: %s <delay time in microseconds> \n", argv[0]);
		exit(0);
	}

	pid_t pid;
	int n = atoi(argv[1]); //delay in microseconds to showcase cpu scheduling
	printf("\n Before forking... \n");
	pid = fork();
	
	if(pid < 0){
		fprintf(stderr, "can't fork, error %d\n", errno);
		exit(0);
	}
	if(pid){ // parent process as pid is > 0
		for(int i = 0; i < 10; ++i){
			printf("\t\t\tI am the parent process displaying iteration: %d\n", i);
			usleep(n);
		}
	}
	else{
		for(int i = 0; i < 10; ++i){
			printf("I am the child process displaying iteration: %d\n", i);
			usleep(n);
		}
	}
	return 0;
}
