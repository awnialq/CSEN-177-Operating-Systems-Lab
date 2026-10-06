// Name: Awni AlQuraini
// Date: 10/7/2026
// Title: Lab 3 - Part 1
// Description: A file showing the functionality of pipe through two child processes with a parent managing their interaction.
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
//main
int main() {
	int fds[2];
	pipe(fds);
	/*child 1 redirects stdin to downstream of pipe */
	if (fork() == 0) {
		dup2(fds[0], 0);
		close(fds[1]);
		execlp("more", "more", 0);
	}
	/*child 2 redirects stdout to upstream of pipe */
	else if (fork() == 0) {
		dup2(fds[1], 1);
		close(fds[0]);
		execlp("ls", "ls", "-l", 0);
	}
	else { /*parent closes both ends and wait for children*/
		close(fds[0]);
		close(fds[1]);
		wait(0);
		wait(0);
	}
	return 0;
}
