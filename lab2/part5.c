// Name: Awni AlQuraini
// Date: 09/30/2026
// Title: Lab 2 - Step 7
// Description: The C file that showcases forking how to use the execlp function to run a different program by forking and then ensuring that you do not have any zombie processes that are created by using wait.
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h> 
#include <errno.h>

int main(){
	pid_t pid;
	int n = 3000; //delay in microseconds to showcase cpu scheduling
	printf("Before forking... \n");
	pid = fork();
	
	if(pid < 0){
		fprintf(stderr, "can't fork, error %d\n", errno);
		exit(0);
	}
	if(pid){ // parent process as pid is > 0
		wait(NULL);
		printf("Child Complete!");
		exit(0);
	}
	else{
		execlp("/bin/ls", "ls", NULL);
	}
	return 0;
}
