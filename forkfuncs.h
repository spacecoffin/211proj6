//
//  forkfuncs.h
//  Assignment 6 - CS 211-Fall 14
//  Reed Rosenberg
//  Interface for fork functions for use in myshell.c.
//

#ifndef FORKFUNCS_H
#define FORKFUNCS_H

// Forks a child process which will execute the commands entered into the command prompt and stored with its arguments in the global argument vector "argvec[]"

void forkchild();

//--------------------------------------------------------------------

// The function called from within forkchild() to execute the command given to the child.
void execchild(void);

//--------------------------------------------------------------------

// Invokes the wait() function on the parent process from within forkchild().
void parent(pid_t pid);

#endif