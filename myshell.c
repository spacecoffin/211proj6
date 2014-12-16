//
//  myshell.c
//  Assignment 6 - CS 211-Fall 14
//  Reed Rosenberg
//  Implements a simple shell.
//

#include <stdio.h>
#include <string.h>

/* Global variables */
char *line;			// ptr to string of chars that will store read cmd line.
size_t length = 0;
char *argvec[];			// argvec is a 1D array of pointers to strings


/* Function prototypes */
void printprompt();
int readline();
int parseline(char *argvec[]);

int main(int argc, char **argv) {
	while (1) {
		// argvec declared/initialized here???
		printprompt();
		if (readline()) continue;
		parseline(argvec);
		
		
	}
	return 0;
}

void printprompt() {
	printf("myshell-> ");		// 1. Print the command prompt.
	return;
}

int readline() {
	switch (getline(&line, &length, stdin)) {
		case -1:		// geline read no bytes (error)
			return 1;
		default:		// success, getline returns location
			return 0;	// of string to 1st argument
	}
}

int parseline() {
	char *linecp, *token;
	
	if ((linecp = strdup(line)) != NULL) {
		for (
	}
	
}