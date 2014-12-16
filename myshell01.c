//
//  myshell.c
//  CS 211 - Fall 14
//  Reed Rosenberg
//

#include <stdio.h>
#include <stdlib.h>     // as suggested in 17.8 - Pseudo Terminals
#include <string.h>
#include <unistd.h>     // per Creating a Process slide from Lec 11

int cmdtok(void);       // placeholder for parsed command line tokens
// static char line[1024]; // for shellParse method of read using fgets
void empty(char *argvec[], int n);

int main(void)
{
        int rv;                         // return value
        char *line = NULL;  		// line buffer argument to getline()
        size_t length = 0;  		// buffer size argument to getline()
        char *token;			// token returned by strtok()
        char *delim = " .,;:!\"?\n";	// delimiter characters for strtok()
        
        int table_size;		// table size, a command-line argument
	int n;			// current number of strings in table
        /* String table is a 1D array of pointers to strings */
        char *argvec[table_size];
	/* Initialize current number of strings in table to 0 */
	n = 0;
        
        while (1) {
                // 1. Print the command prompt.
                printf("myshell-> ");
                // fflush(NULL);        // per shellParse example
                
                // 2. Read the command line (e.g, “ls -a -l”).
                
                /*
                 * The user should be able to exit your shell program by either
                 * typing “exit” or “logout”.
                 */
                
                /* if (!fgets(line, 1024, stdin)) {
                        return 0;
                } */
                
                /* Parse lines of input text; extract and insert words into string table */
                if (getline(&line, &length, stdin) == -1)       // read next line
                        break;                                  // exit loop when no more
                
                // 3. Parse the command line into tokens consisting of the
                // executable file name (“ls”) and its arguments (“-a” & “-l”).
                
                /*
                 * When parsing the command line, store the tokens in an
                 * argument vector, say argvec[], which is an array of pointers
                 * to strings.
                 */
                
                token = strtok(line, delim);	// extract next token from line
                while (token != NULL) {
                        rv = cmdtok();
                        if (!rv) {
                                return 1;
                        }
                        token = strtok(line, delim);
                }
                // Make sure to terminate the array of pointers by a NULL ptr!
                
        }
        free(line);		// free line buffer
	empty(argvec, n);	// empty table
        

        // 4. Fork a child process, which executes the command.
        /*
         * After parsing the command, fork a child process that will then 
         * perform an execvp() to execute the command.
         * Pass the argument vector that you built as an argument to function
         * execvp().
         */
        
        // 5. Wait for the child to terminate.
        return 0;
}

/* Empty table by freeing all strings */
void empty(char *argvec[], int n)
{
	int i;
	
	for (i = 0; i < n; i++) {
		if (argvec[i] != NULL) {
			free(argvec[i]);
			argvec[i] = NULL;
		}
	}
	return;
}
