//
//  main.c
//  CS 211 - Fall 14
//  Reed Rosenberg
//

#include <stdio.h>
#include <stdlib.h>     // as suggested in 17.8 - Pseudo Terminals

int main(int argc, const char * argv[])
{
        // 1. Print the command prompt.
        printf("myshell-> ");
        
        // 2. Read the command line (e.g, “ls -a -l”).
        
        
        // 3. Parse the command line into tokens consisting of the executable
        //      file name (“ls”) and its arguments (“-a” and “-l”).
        // 4. Fork a child process, which executes the command.
        // 5. Wait for the child to terminate.
        return 0;
}

