//
//  forkfuncs.c
//  Assignment 6 - CS 211-Fall 14
//  Reed Rosenberg
//  Implementation of fork functions for use in myshell.c.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "forkfuncs.h"

void forkchild() {
	pid_t pid;	/* process ID */
	
	switch (pid = fork()) {
		case 0:		/* child process */
			execchild();
			break;
			
		default:	/* parent process */
			parent(pid);
			printf("Parent process exits\n");
			break;
		case -1:	/* something went wrong */
			perror("fork failed");
			exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
	
}

void execchild(void) {
	printf("I am the child process with pid %d, my parent's pid is %d\n", getpid(), getppid());
	printf("Child process runs \"%s\"\n", argvec[0]);
	execvp(argvec[0], argvec);
	perror("execvp failed");	/* if we get here, execvp failed */
	exit(EXIT_FAILURE);
}

void parent(pid_t child_pid) {
	pid_t got_pid;
	int status;
	
	printf("I am the parent process with pid %d, waiting for child process with pid %d\n", getpid(), child_pid);
	while ((got_pid = wait(&status))) {   /* go to sleep until something happens */
		/* wait() woke up process */
		if (got_pid == child_pid)
			break;	/* this is what we were looking for */
		if (got_pid == -1) {
			/* wait() returned for some other reason other than a child terminating */
			perror("wait returned for some other reason");
			return;
		}
	}
	if (WIFEXITED(status))	/* child process exited normally */
		printf("Child process exited with value %d\n", WEXITSTATUS(status));
	
}