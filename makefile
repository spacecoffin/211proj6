# Makefile for myshell program (Reed Rosenberg)
myshell: myshell.o forkfuncs.o
    gcc –Wall –g –o myshell myshell.o forkfuncs.o

myshell.o: myshell.c forkfuncs.h
    gcc –Wall –g –c myshell.c

forkfuncs.o: forkfuncs.c forkfuncs.h
    gcc –Wall –g –c forkfuncs.c