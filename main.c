//
//  main.c
//  CS 211 - Fall 14
//  Reed Rosenberg
//

#include <stdio.h>
#include <stdlib.h>     // as suggested in 17.8 - Pseudo Terminals
#include <string.h>
#include <unistd.h>     // per Creating a Process slide from Lec 11

int cmdtok(void);       // placeholder for parsed command line tokens

int main(void)
{
        int rv;                         // return value
        char *line = NULL;  		// line buffer argument to getline()
        size_t length = 0;  		// buffer size argument to getline()
        char *token;			// token returned by strtok()
        char *delim = " .,;:!\"?\n";	// delimiter characters for strtok()
        
        while (1) {
                // 1. Print the command prompt.
                printf("myshell-> ");
                // fflush(NULL);        // per shellParse example
                
                // 2. Read the command line (e.g, “ls -a -l”).
                /* if (!fgets(line, 1024, stdin)) {
                        return 0;
                } */
                
                
                if (getline(&line, &length, stdin) == -1)
                        break;
                
                // 3. Parse the command line into tokens consisting of the
                // executable file name (“ls”) and its arguments (“-a” & “-l”).
                token = strtok(line, delim);
                while (token != NULL) {
                        rv = cmdtok();
                        if (!rv) {
                                return 1;
                        }
                        token = strtok(line, delim);
                }
                
        }
        free(line);
        
        
        
        
        
        

        // 4. Fork a child process, which executes the command.
        // 5. Wait for the child to terminate.
        return 0;
}

