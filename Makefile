# Taken and modified from
# http://www.linuxdevcenter.com/pub/a/linux/2002/01/31/make_intro.html?page=2
#about compilation & linking:
#http://knzsoft.ru/cpp-bgr-ls1/
#also
#http://stackoverflow.com/questions/13664693/makefile-compiling-and-linking
#about gcc oprions
#https://www.safaribooksonline.com/library/view/programming-embedded-systems/0596009836/ch04.html

#PHONY: execute so named receipt, not a file
#.PHONY: list vector

#.PHONY: all

# Defining the C Compiler etc
CC=gcc
CFLAGS=-g -Wall -std=gnu99 -DNDEBUG
OBJS=list.o vector.o
PROG=finprog

all: $(PROG)
	echo all: make complete

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

sort.o: sort.c list.o vector.o
list.o: list.c API.h
vector.o: vector.c API.h

# Defining the object files:
#objects = main.o example.o

# The default rule - compiling our main program:
#all:	prog_o
#		echo all: make complete
#all:
#	$(CC) $(CFLAGS) prog.c -o file1

# Linking our program file
#prog_o: $(PROG)
	# If we get here, all the dependencies are now built.
	# Link it:
#	$(CC) -o $@ $+

# Tell make how to build .o files from .c files:
#%.o:%.c
#	$(CC) -c $+

# Compiling source files
#main.o: main.c main.h
#		cc -c main.c

#Now make sure that make rebuilds files if included headers change:
#main.o: main.h defs.h
#example.o: example.h defs.h
