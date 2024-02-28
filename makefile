# Sample lab 3 Makefile for SP 2024
# Your name goes here or you get a zero.

CFLAGS= -std=c99 -pedantic -Wformat -Wreturn-type 
all:  tags headers lab3


headers: *.c tags
	headers.sh

tags: *.c
	ctags -R .


# this is our master compiler rule to generate .o files.
# It needs all 4 warnings

%.o:%.c *.h
	gcc $(CFLAGS) -g -c $< -o $@


lab3: lab3.o callbacks.o memory.o bits.o input.o physics.o sim.o output.o n2.o
	gcc -g -o $@ $^  -L. -lbtp -lncurses -lm -llinkedlist


# Prototypes go here


# Zip target goes here.  
# If it doesn't self test lab3, your lab is late.


