# Makefile for myshell program (Reed Rosenberg)
# invoked with "make -f myshell"

CC = gcc
CCFLAGS = -Wall -g

myshell: myshell.o forkfuncs.o
    $(CC) $(CFLAGS) –o myshell myshell.o forkfuncs.o

myshell.o: myshell.c forkfuncs.h
    $(CC) $(CFLAGS) –c myshell.c

forkfuncs.o: forkfuncs.c forkfuncs.h
    $(CC) $(CFLAGS) –c forkfuncs.c

# Remove all .o files
# invoked with "clean" as target ("make clean")
clean:
    rm –f *.o