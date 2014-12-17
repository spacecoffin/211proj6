//
//  myshell.c
//  Assignment 6 - CS 211-Fall 14
//  Reed Rosenberg
//  Implements a simple shell.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/* Global variables */
char *line;			// ptr to string of chars that will store read cmd line.
size_t length = 0;
char *argvec[];			// argvec is a 1D array of pointers to strings


/* Function prototypes */
void printprompt();
int readline();
int parseline();
void forkchild();
void execchild(void);
void parent(pid_t pid);

int main(int argc, char **argv) {
	while (1) {
		// argvec declared/initialized here???
		printprompt();
		if (readline()) {
			printf("Error reading from cmd line\n");
			continue;
		}
		//printf("You typed: %s", line);
		if (parseline()) {
			break;
		}
		forkchild();
		
		
	}
	return 0;
}

void printprompt() {
	printf("myshell-> ");		// 1. Print the command prompt.
	return;
}

int readline() {
	int bytesread = getline(&line, &length, stdin);	//test
	
	switch (bytesread) {
		case -1:		// geline read no bytes (error)
			return 1;
		default:		// success, getline returns location
			//printf("Bytes read: %i\n", bytesread);
			//printf("1st char: %c\n", line[0]);
			return 0;	// of string to 1st argument
	}
}

int parseline() {
	char *linecp, *token;
	char *delim = " \n";
	int i = 0;		// value for incrementing for pointing to argvec
	char *exitcmd = "exit";
	char *logoutcmd = "logout";
	
	if ((linecp = strdup(line)) != NULL) {
		token = strtok(linecp, delim);	// extract next token from line
		if ((strcmp(token, exitcmd) == 0) || (strcmp(token, logoutcmd) == 0)) {
			printf("User exited\n");
			return 1;
		}
		while (token != NULL) {
			argvec[i] = token;
			printf("Token %i: \"%s\"\n", i, token);
			i++;
			token = strtok(NULL, delim);	// extract next token
		}
		//argvec[i] = NULL;
		return 0;
	} else {
		return 1;
	}
}

void forkchild() {
	pid_t pid;	/* process ID */
	
	switch (pid = fork()) {
		case 0:		/* child process */
			printf("I am the child process with pid %d\n", getpid());
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
