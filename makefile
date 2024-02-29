# Lab4 makefile
# Edited by: Elijah Paulman

CFLAGS= -std=c99 -pedantic -Wformat -Wreturn-type 
all:  tags headers lab4


headers: *.c tags
	headers.sh

tags: *.c
	ctags -R .


# this is our master compiler rule to generate .o files.
# It needs all 4 warnings

%.o:%.c *.h
	gcc $(CFLAGS) -g -c $< -o $@


lab4: lab4.o callbacks.o memory.o bits.o input.o physics.o sim.o output.o n2.o
	gcc -g -o $@ $^  -L. -lbtp -lncurses -lm -llinkedlist


# Prototypes go here
p1: p1.o 
	gcc -g -o $@ $^ -L. -lm -lbtp -lncurses

p2: p2.o 
	gcc -g -o $@ $^ -L. -lm -lbtp -lncurses

p3: p3.o 
	gcc -g -o $@ $^ -L. -lm -lbtp -lncurses

p4: p4.o bits.o
	gcc -g -o p4 p4.o bits.o -L. -lm -lbtp -lncurses

p4.o: p4.c
	gcc -std=c99 -pedantic -Wformat -Wreturn-type -g -c p4.c -o p4.o


# Zip target goes here.  
# If it doesn't self test lab4, your lab is late.
lab4.zip: makefile *.c *.h README_LAB4 n2.o libbtp.a liblinkedlist.a
	zip $@ $^
# self test lab4
	rm -rf install
# create install folder
	mkdir install
# unzip lab4.zip into install folder
	unzip lab4.zip -d install
# make everything being graded
	make -C install -r lab4
# remove install folder
	rm -rf install

