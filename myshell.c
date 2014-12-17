//
//  myshell.c
//  Assignment 6 - CS 211-Fall 14
//  Reed Rosenberg
//  Implements a simple shell.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "forkfuncs.h"

/* Global variables */
char *line;			// ptr to string of chars that will store read cmd line.
size_t length = 0;
char *argvec[];			// argvec is a 1D array of pointers to strings

/* Function prototypes */
void printprompt();
int readline();
int parseline();

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
